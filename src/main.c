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
int	dirx = 0;
int diry = 0;

int	handle_key(int keycode, void *sth)
{
	(void) sth;
	if (keycode == XK_a)
	{
		printf("a\n");
		dirx = -1;
		diry = 0;
	}
	else if (keycode == XK_w)
	{
		printf("w\n");
		diry = -1;
		dirx = 0;
	}
	else if (keycode == XK_s)
	{
		printf("s\n");
		diry = 1;
		dirx = 0;
	}
	else if (keycode == XK_d)
	{
		printf("d\n");
		dirx = 1;
		diry = 0;
	}
	pressed = 1;
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

	ft_update_img(conf);


}

void	mod_pos()
{
	start = end;
	end = clock();
	double fps = (double) (end - start) / CLOCKS_PER_SEC;

	double spmov = fps * 15;
	if (pressed)
	{
		double newX = posx + (double) dirx * spmov;
		double newY = posy + (double) diry * spmov;
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

int game_loop(t_mlxconf *conf)
{
	draw_map(conf);
	mod_pos();
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
