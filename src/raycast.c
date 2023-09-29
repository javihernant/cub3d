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
		t_mlximg *tex = wm->tex[0];
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

void	obstacle_dist(t_motion *mn, int **wmap)
{
	int	x = 0;
	while (x < WIDTH)
	{

		double ratiox =  (mn->raydirx[x]) == 0 ? 999999 : 1/fabs(mn->raydirx[x]); //TODO: if div is 0
		double ratioy = mn->raydiry[x] == 0 ? 999999 : 1/fabs(mn->raydiry[x]);
		double distx;
		double disty;
		double sx;
		double	sy;
		if (mn->raydirx[x] < 0)
		{
			distx = (mn->posx - floor(mn->posx)) * ratiox;
			sx = -1;
		}
		else
		{
			distx = (ceil(mn->posx) - mn->posx) * ratiox;
			sx = 1;
		}
		if (mn->raydiry[x] < 0)
		{
			disty = (mn->posy - floor(mn->posy)) * ratioy;
			sy = -1;
		}
		else
		{
			disty = (ceil(mn->posy) - mn->posy) * ratioy;
			sy = 1;
		}
		int hit = 0;
		double obsx = (int) mn->posx;
		double obsy = (int) mn->posy;

		while(!hit)
		{
			if (distx < disty)
			{
				obsx += sx;
				distx += ratiox;
				mn->side[x] = 0;
			}
			else
			{
				obsy += sy;
				disty += ratioy;
				mn->side[x] = 1;
			}
			if (wmap[(int)obsy][(int)obsx] != 0)
			{
				if (mn->side[x] == 0)
				{
					mn->obsdist[x] = distx - ratiox;

				}
				else
				{
					mn->obsdist[x] = disty - ratioy;

				}
				break;
			}
		}

		x++;
	}
}
