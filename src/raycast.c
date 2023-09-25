#include "mlxutils.h"

void ray_constants(t_motion *motion)
{
	int	x = 0;
	while (x < WIDTH)
	{
		double camx = 2 * (double) x / WIDTH - 1;
		double ray = camx * 1;
		motion->rays[x] = ray;
		x++;
	}
}

void	draw_3d(t_mlximg *world, t_motion *mn)
{
	int	x = 0;
	double line_height;
	while (x < world->w)
	{
		line_height = world->h/mn->obsdist[x];
		int start = world->h/2 -line_height/2;
		int end = world->h/2 + line_height/2;
		int color = 0x00ff00;
		if (mn->side[x] == 0)
		{
			color = (color & 0xf0f0f0f0) >> 1;
		}
		ft_draw_line(x, start, x, end, color, world);
		x++;
	}
}

void	obstacle_dist(t_motion *mn, int **wmap)
{
	int	x = 0;
	while (x < WIDTH)
	{
		double raydirx = mn->dirx + mn->rays[x]*mn->planex;
		double raydiry = mn->diry + mn->rays[x]*mn->planey;
		double ratiox =  (raydirx) == 0 ? 999999 : 1/fabs(raydirx); //TODO: if div is 0
		double ratioy = raydiry == 0 ? 999999 : 1/fabs(raydiry);
		double distx;
		double disty;
		double sx;
		double	sy;
		if (raydirx < 0)
		{
			distx = (mn->posx - floor(mn->posx)) * ratiox;
			sx = -1;
		}
		else
		{
			distx = (ceil(mn->posx) - mn->posx) * ratiox;
			sx = 1;
		}
		if (raydiry < 0)
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
