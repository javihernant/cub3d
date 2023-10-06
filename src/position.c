#include "mlxutils.h"

void rotate_dir(double rotspeed, t_motion *mn)
{
	double olddirx = mn->dirx;
	mn->dirx = mn->dirx * cos(rotspeed) - mn->diry * sin(rotspeed);
	mn->diry = olddirx * sin(rotspeed) + mn->diry * cos(rotspeed);

	double oldplanex = mn->planex;
	mn->planex = mn->planex * cos(rotspeed) - mn->planey * sin(rotspeed);
	mn->planey = oldplanex * sin(rotspeed) + mn->planey * cos(rotspeed);
}

void	mod_pos(clock_t *end, t_keys *keys, t_motion *mn, t_wmap *wmap)
{
	clock_t start = *end;
	*end = clock();
	double fps = (double) (*end - start) / CLOCKS_PER_SEC;

	double spmov = fps * 3;

	double stepx;
	double stepy;

	stepx = 0;
	stepy = 0;
	if (keys->w)
	{
		stepx = mn->dirx;
		stepy = mn->diry;
	}
	if (keys->s)
	{
		stepx = -mn->dirx;
		stepy = -mn->diry;
	}
	if (keys->a)
	{
		stepx = mn->dirx * cos(-1.5707) - mn->diry * sin(-1.5707);
		stepy = mn->dirx * sin(-1.5707) + mn->diry * cos(-1.5707);
	}
	if (keys->d)
	{
		stepx = mn->dirx * cos(1.5707) - mn->diry * sin(1.5707);
		stepy = mn->dirx * sin(1.5707) + mn->diry * cos(1.5707);
	}
	double newx = mn->posx + stepx * spmov;
	double newy = mn->posy + stepy * spmov;
	if ((int)newx >= 0 && (int)newx < wmap->w && (int)newy >= 0 && (int)newy < wmap->h)
	{

		if (wmap->wmap[(int)newy][(int)newx] == 0)
		{
			mn->posx = newx;
			mn->posy = newy;
		}
	}

	//Rotations
	double rotspeed = fps * 5;
	if (keys->left)
	{
		rotspeed = -rotspeed;
		rotate_dir(rotspeed, mn);

	}
	if (keys->right)
	{
		rotate_dir(rotspeed, mn);
	}

}
