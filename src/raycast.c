#include "mlxutils.h"

// void	floor_cast(t_motion *mn, t_mlximg *wd)
// {
// 	int	y = 0;
// 	while (y < wd->h)
// 	{

// 		y++
// 	}
// }

void	floor_cast(t_motion *mn, t_mlximg *wd, t_wmap *wm)
{
	int y = 0;
	while (y < wd->h)
	{
		double raydirx0 = mn->dirx - mn->planex;
		double raydiry0 = mn->diry - mn->planey;
		double raydirx1 = mn->dirx + mn->planex;
		double raydiry1 = mn->diry + mn->planey;


		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		double rowdist = (double)(wd->h/2) / (y - wd->h/2);

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		double stepx = rowdist * (raydirx1 - raydirx0) / wd->w;
		double stepy = rowdist * (raydiry1 - raydiry0) / wd->w;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		double floorx = mn->posx + rowdist * raydirx0;
		double floory = mn->posy + rowdist * raydiry0;
		t_mlximg *tex = wm->tex[1];
		int x = 0;
		while (x < wd->w)
		{
			int tx = (int)((floorx - floor(floorx)) * tex->w) & (tex->w - 1);
			int ty = (int)((floory - floor(floory)) * tex->h) & (tex->h - 1);
			floorx += stepx;
			floory += stepy;
			int color = ((int *)tex->buff)[ty * tex->w + tx];
			ft_pixel_put(x, y, color, wd);
			ft_pixel_put(x, wd->h - 1 - y, color, wd);
			x++;

		}
		y++;
	}
}

void	raydir_calc(t_motion *mn)
{
	int	x = 0;
	while (x < WIDTH)
	{
		mn->raydirx[x] = mn->dirx + mn->planex * mn->rays[x];
		mn->raydiry[x] = mn->diry + mn->planey * mn->rays[x];
		x++;
	}

}

void	draw_3d(t_mlximg *world, t_motion *mn, t_wmap *wm)
{
	(void) wm;
	int	x = 0;
	double line_height;
	while (x < world->w)
	{
		line_height = world->h/mn->obsdist[x];
		int start = world->h/2 -line_height/2;
		int end = world->h/2 + line_height/2;
		double texx;
		int	tex_num = wm->wmap[mn->obsy[x]][mn->obsx[x]] - 1;
		t_mlximg *tex = wm->tex[tex_num];
		if (mn->side[x] == 0)
		{
			texx = mn->posy + mn->raydiry[x]*mn->obsdist[x];

		}
		else
		{

			texx = mn->posx + mn->raydirx[x]*mn->obsdist[x];

		}
		texx = (texx - floor(texx));
		int texxx = texx * (tex->w - 1);
		int y = start;
		// if (y < 0)
		// 	y = 0;
		double txstep = (double) tex->h / line_height;
		// double postexy = (start + line_height - world->h / 2)*txstep;
		double postexy = 0;

		while (y < end)
		{
			int texy = (int) postexy & (tex->h - 1);
			int color = ((int *)(tex->buff))[texy * tex->w + texxx];
			if (mn->side[x] == 0)
			{
				color = (color & 0xf0f0f0f0) >> 1;
			}
			ft_pixel_put(x, y, color, world);
			postexy += txstep;
			y++;
		}
		// ft_draw_line(x, start, x, end, 0xff0000, world);
		x++;
	}
}

/////////////////////////////////////DOOR//////////////////////////////////////////
int	is_door(int x, int y)
{
	int doorx = 6;
	int doory = 6;
	return (x == doorx && y == doory) || (x == 8 && y == 4);

	(void)x;
	(void)y;
	return 0;

}

double	get_max_lim(t_motion *mn, int x)
{

	int	doorx;
	int	doory;

	doorx = mn->obsx[x];
	doory = mn->obsy[x];
	if (mn->side[x] == 0)
		if ((int) mn->posx < doorx)
			return  (doorx + 0.5);
		else
			return (doorx + 1);
	else
		if ((int) mn->posy < doory)
			return  (doory + 0.5);
		else
			return (doory + 1);
}

int	hits_lateral(t_motion *mn, int x, double obsauxx, double obsauxy)
{
	double	max_lim;
	max_lim = get_max_lim(mn, x);

	if (mn->side[x] == 0)
	{
		return (obsauxx > (max_lim - 0.5) && obsauxx < max_lim  && ((int) obsauxy == mn->obsy[x] || (int) obsauxy == (mn->obsy[x] + 1)));
	}
	else
	{
		return (obsauxy > (max_lim - 0.5) && obsauxy < max_lim  && ((int) obsauxx == mn->obsx[x] || (int) obsauxx == (mn->obsx[x] + 1)));
	}
}

void	door_dist_aux(t_motion *mn, int x, double obsx, double obsy)
{
	if (hits_lateral(mn, x, obsx, obsy))
	{
		if (mn->side[x] == 0)
		{
			mn->obsdist[x] = mn->disty[x];
			mn->side[x] = 1;
		}
		else
		{
			mn->obsdist[x] = mn->distx[x];
			mn->side[x] = 0;
		}
	}
	else
	{
		if (mn->side[x] == 0)
			mn->obsdist[x] = mn->distx[x] - mn->ratiox[x]/2;
		else
			mn->obsdist[x] = mn->disty[x] - mn->ratioy[x]/2;
	}
}

void	door_dist(t_motion *mn, int x)
{
	double	obsauxx;
	double	obsauxy;

	if (mn->side[x] == 0)
	{
		obsauxx = mn->posx + mn->raydirx[x] * (mn->disty[x]);
		obsauxy = mn->posy + mn->raydiry[x] * (mn->disty[x]);
	}
	else
	{
		obsauxx = mn->posx + mn->raydirx[x] * (mn->distx[x]);
		obsauxy = mn->posy + mn->raydiry[x] * (mn->distx[x]);
	}
	door_dist_aux(mn, x, obsauxx, obsauxy);
}

/////////////////////////////////////DOOR//////////////////////////////////////////

/////////////////////////////////////obstacle_dist//////////////////////////////////////////

void	init_dist(t_motion *mn, int x, int *sx, int *sy)
{
	mn->ratiox[x] =  (mn->raydirx[x]) == 0 ? 999999 : 1/fabs(mn->raydirx[x]); //TODO: if div is 0
	mn->ratioy[x] = mn->raydiry[x] == 0 ? 999999 : 1/fabs(mn->raydiry[x]);

	if (mn->raydirx[x] < 0)
	{
		mn->distx[x] = (mn->posx - floor(mn->posx)) * mn->ratiox[x];
		*sx = -1;
	}
	else
	{
		mn->distx[x] = (ceil(mn->posx) - mn->posx) * mn->ratiox[x];
		*sx = 1;
	}
	if (mn->raydiry[x] < 0)
	{
		mn->disty[x] = (mn->posy - floor(mn->posy)) * mn->ratioy[x];
		*sy = -1;
	}
	else
	{
		mn->disty[x] = (ceil(mn->posy) - mn->posy) * mn->ratioy[x];
		*sy = 1;
	}
}

void	obstacle_dist(t_motion *mn, int **wmap)
{
	int	x;
	int sx;
	int	sy;


	x = 0;
	while (x < WIDTH)
	{
		init_dist(mn, x, &sx, &sy);
		mn->obsx[x] = (int) mn->posx;
		mn->obsy[x] = (int) mn->posy;
		while(1)
		{
			if (mn->distx[x] < mn->disty[x])
			{
				mn->obsx[x] += sx;
				mn->distx[x] += mn->ratiox[x];
				mn->side[x] = 0;
			}
			else
			{
				mn->obsy[x] += sy;
				mn->disty[x] += mn->ratioy[x];
				mn->side[x] = 1;
			}

			if (wmap[mn->obsy[x]][mn->obsx[x]] != 0)
			{
				if (is_door(mn->obsx[x], mn->obsy[x]))
				{
					door_dist(mn, x);
					// if (mn->side[x] == 0)
					// {
					// 	mn->obsdist[x] = mn->disty[x];
					// 	mn->side[x] = 1;
					// }
					// else
					// {
					// 	mn->obsdist[x] = mn->distx[x];
					// 	mn->side[x] = 0;

					// }

				}
				else
					if (mn->side[x] == 0)
						mn->obsdist[x] = mn->distx[x] - mn->ratiox[x];
					else
						mn->obsdist[x] = mn->disty[x] - mn->ratioy[x];
				break;

			}
		}
		x++;
	}
}
