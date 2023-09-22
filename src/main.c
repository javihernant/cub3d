#include "mlxutils.h"
#include "libft.h"
#include <time.h>
#include <math.h>




int worldMap[MAP_H][MAP_W]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double posx = 5.5;
double posy = 5.5;

clock_t start = 0;
clock_t end = 0;

int	pressed = 0;
double	stepx = 0;
double stepy = 0;
double planex = 1;
double planey = 0;
double dirx = 0;
double diry = -1;
t_keys keys;
double obsdist[WIDTH];
double rays[WIDTH];
char	side[WIDTH];

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

void	draw_map(t_mlxconf *conf)
{
	int pixx = posx * (double)MINIM_W / MAP_W;
	int pixy = posy * (double)MINIM_H / MAP_H;

	int y = 0;
	while (y < MINIM_H)
	{
		int x = 0;
		while (x < MINIM_W)
		{
			int i = y * MAP_H / MINIM_H;
			int j = x * MAP_W / MINIM_W;
			int val = worldMap[i][j];
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
			ft_pixel_put(x,y,color,&conf->map);
			x++;
		}
		y++;
	}
}

void rotate_dir(double rotspeed)
{
	double olddirx = dirx;
	dirx = dirx * cos(rotspeed) - diry * sin(rotspeed);
	diry = olddirx * sin(rotspeed) + diry * cos(rotspeed);

	double oldplanex = planex;
	planex = planex * cos(rotspeed) - planey * sin(rotspeed);
	planey = oldplanex * sin(rotspeed) + planey * cos(rotspeed);
}

void	mod_pos(t_keys *keys)
{
	start = end;
	end = clock();
	double fps = (double) (end - start) / CLOCKS_PER_SEC;

	double spmov = fps * 3;

	double stepx;
	double stepy;

	if (keys->w)
	{
		stepx = dirx;
		stepy = diry;
	}
	if (keys->s)
	{
		stepx = -dirx;
		stepy = -diry;
	}
	if (keys->a)
	{
		stepx = dirx * cos(-1.5707) - diry * sin(-1.5707);
		stepy = dirx * sin(-1.5707) + diry * cos(-1.5707);

	}
	if (keys->d)
	{
		stepx = dirx * cos(1.5707) - diry * sin(1.5707);
		stepy = dirx * sin(1.5707) + diry * cos(1.5707);
	}
	double newx = posx + stepx * spmov;
	double newy = posy + stepy * spmov;
	if (newx >= 0 && newx < MAP_W && newy >= 0 && newy < MAP_H)
	{

		if (worldMap[(int)newy][(int)newx] == 0)
		{
			posx = newx;
			posy = newy;
		}
	}

	//Rotations
	double rotspeed = fps * 5;
	if (keys->left)
	{
		rotspeed = -rotspeed;
		rotate_dir(rotspeed);

	}
	if (keys->right)
	{
		rotate_dir(rotspeed);
	}

}

void	obstacle_dist()
{

	int	x = 0;
	while (x < WIDTH)
	{
		double ratiox =  (dirx + rays[x]*planex) == 0 ? 999999 : 1/fabs(dirx + rays[x]*planex); //TODO: if div is 0
		double ratioy = (diry + rays[x]*planey) == 0 ? 999999 : 1/fabs(diry + rays[x]*planey);
		double distx;
		double disty;
		double sx;
		double	sy;
		if (dirx + rays[x]*planex < 0)
		{
			distx = (posx - floor(posx)) * ratiox;
			sx = -1;
		}
		else
		{
			distx = (ceil(posx) - posx) * ratiox;
			sx = 1;
		}
		if (diry + rays[x]*planey < 0)
		{
			disty = (posy - floor(posy)) * ratioy;
			sy = -1;
		}
		else
		{
			disty = (ceil(posy) - posy) * ratioy;
			sy = 1;
		}
		int hit = 0;
		double obsx = (int) posx;
		double obsy = (int) posy;

		while(!hit)
		{
			if (distx < disty)
			{
				obsx += sx;
				distx += ratiox;
				side[x] = 0;
			}
			else
			{
				obsy += sy;
				disty += ratioy;
				side[x] = 1;
			}
			if (worldMap[(int)obsy][(int)obsx] != 0)
			{
				if (side[x] == 0)
				{
					obsdist[x] = distx - ratiox;

				}
				else
				{
					obsdist[x] = disty - ratioy;

				}
				break;
			}
		}

		x++;
	}
}

void draw_rays(t_mlxconf *conf)
{
		int pixx0 = posx * (double)MINIM_W/ MAP_W;
		int pixy0 = posy * (double)MINIM_H/ MAP_H;
		int	x = 0;
		while (x < WIDTH)
		{
			double obsx = posx + (dirx + planex*rays[x]) * obsdist[x];
			double obsy = posy + (diry + planey*rays[x]) * obsdist[x];
			int pixx1 = obsx * (double)MINIM_W / MAP_W;
			int pixy1 = obsy * (double)MINIM_H / MAP_H;
			ft_draw_line(pixx0, pixy0, pixx1, pixy1, 0x00ff00, &conf->map);
			x++;
		}
}

void	draw_3d(t_mlxconf *conf)
{
	int	x = 0;
	double line_height;
	while (x < WIDTH)
	{
		line_height = HEIGHT/obsdist[x];
		int start = HEIGHT/2 -line_height/2;
		int end = HEIGHT/2 + line_height/2;
		int color = 0x00ff00;
		if (side[x] == 0)
		{
			color = (color & 0xf0f0f0f0) >> 1;
		}
		ft_draw_line(x, start, x, end, color, &conf->world);
		x++;
	}
}

int game_loop(t_mlxconf *conf)
{
	draw_map(conf);
	obstacle_dist();
	draw_rays(conf);
	ft_set_bg(conf);
	draw_3d(conf);
	ft_update_img(conf);
	mod_pos(&keys);


	return 1;
}

void ray_constants()
{
	int	x = 0;
	while (x < WIDTH)
	{
		double camx = 2 * (double) x / WIDTH - 1;
		double ray = camx * 1;
		rays[x] = ray;
		x++;
	}
}

int main(void)
{
	t_mlxconf	conf;

	init_keys(&keys);
	if (ft_mlx_init(&conf, "Cub3D 42") != 0)
		ft_error("Error initializing mlx");
	// ft_set_bg(&conf);
	// ft_update_img(&conf);
	ray_constants();
	mlx_hook(conf.win, KeyPress, KeyPressMask, key_press, &keys);
	mlx_hook(conf.win, KeyRelease, KeyReleaseMask, key_release, &keys);
	// mlx_key_hook(conf.win, handle_key, 0);
	mlx_loop_hook(conf.mlx, game_loop, &conf);
	mlx_loop(conf.mlx);
	return (0);
}
