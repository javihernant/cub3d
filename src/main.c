#include "mlxutils.h"
#include "libft.h"
#include <time.h>
#include <math.h>

#define MAP_W 24
#define MAP_H 24


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
double planex = -1;
double planey = 0;
double dirx = 0;
double diry = -1;

int	handle_key(int keycode, void *sth)
{
	(void) sth;
	if (keycode == XK_a)
	{
		printf("a\n");
		stepx = dirx * cos(-1.5707) - diry * sin(-1.5707);
		stepy = dirx * sin(-1.5707) + diry * cos(-1.5707);

		pressed = 1;
	}
	else if (keycode == XK_w)
	{
		printf("w\n");
		stepx = dirx;
		stepy = diry;
		// stepx = 0;
		pressed = 1;
	}
	else if (keycode == XK_s)
	{
		stepx = -dirx;
		stepy = -diry;
		pressed = 1;
	}
	else if (keycode == XK_d)
	{
		printf("d\n");
		stepx = dirx * cos(1.5707) - diry * sin(1.5707);
		stepy = dirx * sin(1.5707) + diry * cos(1.5707);
		pressed = 1;

	}
	else if (keycode == XK_Left)
	{
		printf("<\n");
		pressed = 2;
	}
	else if (keycode == XK_Right)
	{
		printf(">\n");
		pressed = 3;
	}


	return 0;
}

void	draw_map(t_mlxconf *conf)
{
	int pixx = posx * WIDTH / MAP_W;
	int pixy = posy * HEIGHT / MAP_H;

	int y = 0;
	while (y < HEIGHT)
	{
		int x = 0;
		while (x < WIDTH)
		{
			int i = y * MAP_H / HEIGHT;
			int j = x * MAP_W / WIDTH;
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
			ft_pixel_put(x,y,color,conf);
			x++;
		}
		y++;
	}
}

void	mod_pos()
{
	start = end;
	end = clock();
	double fps = (double) (end - start) / CLOCKS_PER_SEC;

	double spmov = fps * 15;
	if (pressed == 1)
	{
		double newX = posx + stepx * spmov;
		double newY = posy + stepy * spmov;
		// printf("%f , %f\n", newX, newY);
		if (newX >= 0 && newX < MAP_W && newY >= 0 && newY < MAP_H)
		{

			if (worldMap[(int)newY][(int)newX] == 0)
			{
				posx = newX;
				posy = newY;
			}
		}
		pressed = 0;
	}
	double rotspeed = fps * 5;
	if (pressed == 2)
	{
		rotspeed = -rotspeed;
		double olddirx = dirx;
		dirx = dirx * cos(rotspeed) - diry * sin(rotspeed);
		diry = olddirx * sin(rotspeed) + diry * cos(rotspeed);

		double oldplanex = planex;
     	planex = planex * cos(rotspeed) - planey * sin(rotspeed);
      	planey = oldplanex * sin(rotspeed) + planey * cos(rotspeed);
		pressed = 0;
	}
	if (pressed == 3)
	{
		double olddirx = dirx;
		dirx = dirx * cos(rotspeed) - diry * sin(rotspeed);
		diry = olddirx * sin(rotspeed) + diry * cos(rotspeed);

		double oldplanex = planex;
     	planex = planex * cos(rotspeed) - planey * sin(rotspeed);
      	planey = oldplanex * sin(rotspeed) + planey * cos(rotspeed);
		pressed = 0;
	}
	// printf("%f\n", spmov);
}

void	print_rays(t_mlxconf *conf)
{

	int	x = 0;
	int pixx0 = posx * (double)WIDTH/ MAP_W;
	int pixy0 = posy * (double)HEIGHT/ MAP_H;
	// if (1)
	// if (1)
	while (x < WIDTH)
	{
		double camx = 2 * (double) x / WIDTH - 1;
		double ray = camx * 1;

		double ratiox =  (dirx + ray*planex) == 0 ? 999999 : 1/fabs(dirx + ray*planex); //TODO: if div is 0
		double ratioy = (diry + ray*planey) == 0 ? 999999 : 1/fabs(diry + ray*planey);
		double distx;
		double disty;
		// double obsx = posx + dirx;
		// double obsy = posy + diry;
		double sx;
		double	sy;
		if (dirx + ray*planex < 0)
		{
			distx = (posx - floor(posx)) * ratiox;
			sx = -1;
		}
		else
		{
			distx = (ceil(posx) - posx) * ratiox;
			sx = 1;
		}
		if (diry + ray*planey < 0)
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
		int side;
		double obsx = (int) posx;
		double obsy = (int) posy;
		// double raydirx = dirx + planex*ray;
		// double raydiry = diry + planey*ray;
		while(!hit)
		{
			if (distx < disty)
			{
				obsx += sx;
				distx += ratiox;
				side = 0;
			}
			else
			{
				obsy += sy;
				disty += ratioy;
				side = 1;
			}
			if (worldMap[(int)obsy][(int)obsx] != 0)
			{
				if (side == 0)
				{
					obsx = posx + (dirx + planex*ray) * (distx - ratiox);
					obsy = posy + (diry + planey*ray) * (distx - ratiox);
				}
				else
				{
					obsx = posx + (dirx + planex*ray) * (disty - ratioy);
					obsy = posy + (diry + planey*ray) * (disty - ratioy);

				}
				break;
			}

			(void) side;

		}


		int pixx1 = obsx * (double) WIDTH / (double) MAP_W;
		int pixy1 = obsy * (double) HEIGHT / (double) MAP_H;

		if (pixx1 < 0)
			pixx1 = 0;
		if (pixx1 >= WIDTH)
			pixx1 = WIDTH - 1;
		// int pixy1 = 0;
		if (pixy1 < 0)
			pixy1 = 0;
		if (pixy1 >= HEIGHT)
			pixy1 = HEIGHT - 1;
		ft_draw_line(pixx0, pixy0, pixx1, pixy1, 0x00ff00, conf);

		x++;
	}
}

int game_loop(t_mlxconf *conf)
{
	draw_map(conf);
	mod_pos();

	print_rays(conf);
	ft_update_img(conf);

	return 1;
}

int main(void)
{
	t_mlxconf	conf;

	if (ft_mlx_init(&conf, "Cub3D 42") != 0)
		ft_error("Error initializing mlx");
	// ft_set_bg(&conf);
	// ft_update_img(&conf);
	mlx_hook(conf.win, KeyPress, KeyPressMask, handle_key, 0);
	// mlx_key_hook(conf.win, handle_key, 0);
	mlx_loop_hook(conf.mlx, game_loop, &conf);
	mlx_loop(conf.mlx);
	return (0);
}
