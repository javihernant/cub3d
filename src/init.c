#include "mlxutils.h"
#include "libft.h"
# define MAP_W 24
# define MAP_H 24
# define TEX_W 64
# define TEX_H 64

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

int	load_tex(t_mlximg **tex, char *path, void *mlx)
{
	*tex = malloc(sizeof(t_mlximg));
	(*tex)->img = mlx_xpm_file_to_image(mlx, path, &(*tex)->w, &(*tex)->h);
	if ((*tex)->img == 0)
		return (1);
	(*tex)->buff = mlx_get_data_addr((*tex)->img, &(*tex)->bpp, &(*tex)->line_length, &(*tex)->endian);
	return (0);
}
int	load_textures(t_wmap *wm, void *mlx)
{
	int n = 2;
	wm->tex = malloc(sizeof(t_mlximg *) * n);
	if (load_tex(&wm->tex[0], "imgs/eagle.xpm", mlx) != 0)
	{
		return (1);
	}
	if (load_tex(&wm->tex[1], "imgs/wood.xpm", mlx) != 0)
	{
		return (1);
	}
	return (0);

}

void ray_constants(t_motion *mn)
{
	int	x = 0;
	while (x < WIDTH)
	{
		double camx = 2 * (double) x / WIDTH - 1;
		double ray = camx * 0.8;
		mn->rays[x] = ray;
		x++;
	}
}

void	init_motion(t_motion *motion)
{
	motion->posx = 2; //TODO: choose pos according to file. And direction.
	motion->posy = 2;
	motion->stepx = 0;
	motion->stepy = 0;
	motion->planex = 1;
	motion->planey = 0;
	motion->dirx = 0;
	motion->diry = -1;
	ray_constants(motion);
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
	if (load_textures(&game->wmap, game->mlxconf.mlx) != 0)
	{
		ft_error("Error loading textures");
	}
	return (0);
}
