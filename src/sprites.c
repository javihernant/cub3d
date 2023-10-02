#include "mlxutils.h"
#include <stdlib.h>
#include <stdio.h>


int	cmpft(const void *a, const void *b)
{
	t_spsort *spa = (t_spsort *) a;
	t_spsort *spb = (t_spsort *) b;
	if (spa->dist > spb->dist)
	{
		return (-1);
	}
	else if (spa->dist < spb->dist)
	{
		return (1);
	}
	else
		return (0);
}

void	order_sprites(t_spdata *sp, t_motion *mn)
{
	int	i = 0;
	while (i < sp->n)
	{
		sp->sort[i].order = i;
		sp->sort[i].dist = (mn->posx - sp->sprites[i].x) * (mn->posx - sp->sprites[i].x) + (mn->posy - sp->sprites[i].y) * (mn->posy - sp->sprites[i].y);
		i++;
	}
	qsort(sp->sort, sp->n, sizeof(t_spsort), cmpft);
}

void	cast_sprite(t_sprt *sp, t_motion *mn, t_mlximg *wd, t_mlximg *tex)
{
	double dx = sp->x - mn->posx;
	double dy = sp->y - mn->posy;
	double inv_det = 1.0 / (mn->planex * mn->diry - mn->dirx * mn->planey);
	double transx = inv_det * (mn->diry * dx - mn->dirx * dy);
	double transy = inv_det * (-mn->planey * dx + mn->planex * dy);

	int spr_mid_x = (wd->w / 2) * (1 + transx / transy);
	int spr_w = wd->h / transy;
	spr_w = abs(spr_w);
	int spr_h = spr_w;
	int start_x = spr_mid_x - spr_w / 2;
	if (start_x < 0)
		start_x = 0;
	int	end_x = spr_mid_x + spr_w / 2;
	if (end_x >= wd->w)
		end_x = wd->w - 1;
	int start_y = wd->h/2 - spr_h / 2;
	if (start_y < 0)
		start_y = 0;
	int end_y = wd->h/2 + spr_h / 2;
	if (end_y >= wd->h)
		end_y = wd->h - 1;
	int x = start_x;
	while (x < end_x)
	{
		int tx = (x - (-spr_w / 2 + spr_mid_x)) * tex->w / spr_w;
		int y = start_y;
		if (transy > 0 && transy < mn->obsdist[x])
			while (y < end_y)
			{
				int ty = (y - (wd->h/2 - spr_h / 2)) * tex->w / spr_w;
				int color = ((int *)tex->buff)[ty * tex->w + tx];
				if ((color & 0xffffff) != 0)
					ft_pixel_put(x, y, color, wd);
				y++;
			}
		x++;
	}
}

void	cast_sprites(t_wmap *wm, t_spdata *spdata, t_motion *mn, t_mlximg *wd)
{

	int	idx;
	t_mlximg *tex;

	order_sprites(spdata, mn);
	int i = 0;
	while (i < spdata->n)
	{
		idx = spdata->sort[i].order;
		tex = wm->tex[spdata->sprites[idx].txnum];
		// find_start(&x,&y, &spdata->sprites[i], mn);
		cast_sprite(&spdata->sprites[idx], mn, wd, tex);
		i++;
	}
}
