#include "mlxutils.h"
#include "libft.h"

int	key_press(int keycode, t_keys *keys)
{
	if (keycode == XK_a)
		keys->a = 1;
	else if (keycode == XK_w)
		keys->w = 1;
	else if (keycode == XK_s)
		keys->s = 1;
	else if (keycode == XK_d)
		keys->d = 1;
	else if (keycode == XK_Left)
		keys->left = 1;
	else if (keycode == XK_Right)
		keys->right = 1;
	return 0;
}

int	key_release(int keycode, t_keys *keys)
{
	if (keycode == XK_a)
		keys->a = 0;
	else if (keycode == XK_w)
		keys->w = 0;
	else if (keycode == XK_s)
		keys->s = 0;
	else if (keycode == XK_d)
		keys->d = 0;
	else if (keycode == XK_Left)
		keys->left = 0;
	else if (keycode == XK_Right)
		keys->right = 0;
	return 0;
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

int game_loop(t_game *game)
{
	draw_map(&game->mlxconf, &game->wmap, &game->motion);
	obstacle_dist(&game->motion, game->wmap.wmap);
	draw_rays(&game->mlxconf, &game->wmap, &game->motion);
	ft_set_bg(&game->mlxconf);
	draw_3d(&game->mlxconf.world, &game->motion);
	ft_update_img(&game->mlxconf);
	mod_pos(&game->clock, &game->keys, &game->motion, &game->wmap);
	return (1);
}

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

int main(void)
{
	t_game	game;

	if (game_init(&game, "Cub3D 42") != 0)
		ft_error("Error initializing game");
	mlx_hook(game.mlxconf.win, KeyPress, KeyPressMask, key_press, &game.keys);
	mlx_hook(game.mlxconf.win, KeyRelease, KeyReleaseMask, key_release, &game.keys);
	mlx_loop_hook(game.mlxconf.mlx, game_loop, &game);
	mlx_loop(game.mlxconf.mlx);
	return (0);
}
