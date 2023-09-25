#include "mlxutils.h"
#include <stdlib.h>
#include "libft.h"

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

int	read_map(t_wmap *wmap)
{
	//TODO
	wmap->wmap = malloc(sizeof(int*)*MAP_H);
	for (int i = 0; i < MAP_H; i++)
	{
		wmap->wmap[i] = malloc(sizeof(int)*MAP_W);
		for (int j = 0; j<MAP_W; j++)
		{
			wmap->wmap[i][j] = worldMap[i][j];
		}
	}
	wmap->w = MAP_W;
	wmap->h = MAP_H;
	return (0);
}

void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
}

void	init_motion(t_motion *motion)
{
	motion->posx = 2; //TODO: choose a pos that is empty
	motion->posy = 2;
	motion->stepx = 0;
	motion->stepy = 0;
	motion->planex = 1;
	motion->planey = 0;
	motion->dirx = 0;
	motion->diry = -1;
	ray_constants(motion);
}

int	ft_init_img(t_mlximg *mlximg, void *mlx, int w, int h)
{
	mlximg->img = mlx_new_image(mlx, w, h);
	if (!mlximg->img)
		return (1);
	mlximg->buff = mlx_get_data_addr(mlximg->img, &mlximg->bpp,
			&mlximg->line_length, &mlximg->endian);
	if (!mlximg->buff)
		return (1);
	mlximg->w = w;
	mlximg->h = h;
	return (0);
}

int	ft_mlx_init(t_mlxconf *conf, char *title)
{
	conf->mlx = mlx_init();
	if (!conf->mlx)
		return (1);
	conf->win = mlx_new_window(conf->mlx, WIDTH, HEIGHT,
			title);
	if (!conf->win)
		return (1);
	if (ft_init_img(&conf->minimap, conf->mlx, MINIM_W, MINIM_H) != 0)
		return (1);
	if (ft_init_img(&conf->world, conf->mlx, WIDTH, HEIGHT) != 0)
		return (1);
	return (0);
}

int	game_init(t_game *game, char *title)
{
	if (read_map(&game->wmap) != 0)
		ft_error("Error reading map from the file provided");
	game->clock = 0;
	init_keys(&game->keys);
	init_motion(&game->motion);
	if (ft_mlx_init(&game->mlxconf, title) != 0)
		ft_error("Error reading map from the file provided");
	return (0);
}

void	ft_set_color(char *dst, int color, int endian)
{
	if (endian == 1)
	{
		dst[0] = (color >> 24);
		dst[1] = (color >> 16) & 0xFF;
		dst[2] = (color >> 8) & 0xFF;
		dst[3] = (color) & 0xFF;
	}
	else if (endian == 0)
	{
		dst[0] = (color) & 0xFF;
		dst[1] = (color >> 8) & 0xFF;
		dst[2] = (color >> 16) & 0xFF;
		dst[3] = (color >> 24);
	}
}

void	ft_pixel_put(int x, int y, int color, t_mlximg *conf)
{
	char	*dst;

	if (x < 0 || x >= conf->w || y < 0 || y >= conf->h)
		return ;
	dst = conf->buff + (y * conf->line_length + x * (conf->bpp / 8));
	ft_set_color(dst, color, conf->endian);
}

void	ft_set_bg(t_mlxconf *conf)
{
	int		i;
	int		j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			ft_pixel_put(j, i, 0xffffff, &conf->world);
			j++;
		}
		i++;
	}
}

void	ft_update_img(t_mlxconf *conf)
{
	mlx_put_image_to_window(conf->mlx, conf->win,
		conf->world.img, 0, 0);
	mlx_put_image_to_window(conf->mlx, conf->win,
		conf->minimap.img, 0, 0);
}
