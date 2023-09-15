#include "mlxutils.h"
#include "libft.h"
#include <time.h>

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

double posx = 5;
double posy = 5;

clock_t start = 0;
clock_t end = 0;

int	pressed = 0;
int	stepx = 0;
int stepy = 0;
int obs_x = -1;
int	obs_y = -1;

int	handle_key(int keycode, void *sth)
{
	(void) sth;
	if (keycode == XK_a)
	{
		printf("a\n");
		stepx = -1;
		stepy = 0;
		pressed = 1;
	}
	else if (keycode == XK_w)
	{
		printf("w\n");
		stepy = -1;
		stepx = 0;
		pressed = 1;
	}
	else if (keycode == XK_s)
	{
		stepx = 0;
		stepy = 1;
		pressed = 1;
	}
	else if (keycode == XK_d)
	{
		printf("d\n");
		stepx = 1;
		stepy = 0;
		pressed = 1;

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
	if (pressed)
	{
		double newX = posx + (double) stepx * spmov;
		double newY = posy + (double) stepy * spmov;
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
	// printf("%f\n", spmov);
}

void	print_rays(t_mlxconf *conf)
{

	int	x = 0;
	int pixx0 = posx * (double)WIDTH/MAP_W;
	int pixy0 = posy * (double)HEIGHT/MAP_H;
	while (x < WIDTH)
	{
		double camx = 2 * (double) x / WIDTH - 1;
		double ray = camx * 0.10;
		int pixx1 = (posx + MAP_W * ray) * WIDTH / MAP_W;
		if (pixx1 < 0)
			pixx1 = 0;
		if (pixx1 > WIDTH)
			pixx1 = WIDTH - 1;
		int pixy1 = 0;
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
