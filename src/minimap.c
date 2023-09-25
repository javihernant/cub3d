#include "mlxutils.h"

void draw_rays(t_mlxconf *conf, t_wmap *wmap, t_motion *mn)
{
		int pixx0 = mn->posx * (double)conf->minimap.w/ wmap->w;
		int pixy0 = mn->posy * (double)conf->minimap.h/ wmap->h;
		int	x = 0;
		while (x < WIDTH)
		{
			double obsx = mn->posx + (mn->dirx + mn->planex*mn->rays[x]) * mn->obsdist[x];
			double obsy = mn->posy + (mn->diry + mn->planey*mn->rays[x]) * mn->obsdist[x];
			int pixx1 = obsx * (double)conf->minimap.w/ wmap->w;
			int pixy1 = obsy * (double)conf->minimap.h/ wmap->h;
			ft_draw_line(pixx0, pixy0, pixx1, pixy1, 0x00ff00, &conf->minimap);
			x++;
		}
}

void	draw_map(t_mlxconf *conf, t_wmap *wmap, t_motion *mn)
{
	int pixx = mn->posx * (double)conf->minimap.w / wmap->w;
	int pixy = mn->posy * (double)conf->minimap.h / wmap->h;

	int y = 0;
	while (y < conf->minimap.h)
	{
		int x = 0;
		while (x < conf->minimap.w)
		{
			int i = y * (double) wmap->h / conf->minimap.h;
			int j = x * (double) wmap->w / conf->minimap.w;
			int val = wmap->wmap[i][j];
			int color;
			if (val == 0)
				color = 0x0;
			else if (val == 1)
				color = 0xff0000;
			else if (val == 2)
				color = 0x00ff00;
			else if (val == 3)
				color = 0x0000ff;
			else
				color = 0xffffff;
			if (x >= pixx - 2 && x <= pixx + 2 && y >= pixy - 2 && y <= pixy + 2)
			{
				color = 0xff00ff;
			}
			ft_pixel_put(x,y,color,&conf->minimap);
			x++;
		}
		y++;
	}
}
