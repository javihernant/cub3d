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
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1}, // 5, 6
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,1,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
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

#define NUM_SPRTS 19
t_sprt sprite[NUM_SPRTS] =
{
  {20.5, 11.5, 6}, //green light in front of playerstart
  //green lights in every room
  {18.5,4.5, 9},
  {10.0,4.5, 9},
  {10.0,12.5,9},
  {3.5, 6.5, 9},
  {3.5, 20.5,9},
  {3.5, 14.5,9},
  {14.5,20.5,9},

  //row of pillars in front of wall: fisheye test
  {18.5, 10.5, 8},
  {18.5, 11.5, 8},
  {18.5, 12.5, 8},

  //some barrels around the map
  {21.5, 1.5, 10},
  {15.5, 1.5, 10},
  {16.0, 1.8, 10},
  {16.2, 1.2, 10},
  {3.5,  2.5, 10},
  {9.5, 15.5, 10},
  {10.0, 15.1,10},
  {10.5, 15.8,10},
};


int	init_sprites(t_spdata *data)
{
	int	n = NUM_SPRTS;
	data->n = n;
	data->sprites = malloc(sizeof(t_sprt) * n);
	if (!data->sprites)
		return (1);
	int	i = 0;
	while (i < n)
	{
		data->sprites[i].x = sprite[i].x;
		data->sprites[i].y = sprite[i].y;
		data->sprites[i].txnum = sprite[i].txnum;
		i++;
	}
	data->sort = malloc(sizeof(t_spsort) * n);
	if (!data->sort)
		return (1);
	return (0);
}

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
	int n = 11;
	wm->tex = malloc(sizeof(t_mlximg *) * n);
	if (load_tex(&wm->tex[0], "imgs/eagle.xpm", mlx) != 0)
	{
		return (1);
	}
	if (load_tex(&wm->tex[1], "imgs/wood.xpm", mlx) != 0)
	{
		return (1);
	}
	if (load_tex(&wm->tex[2], "imgs/bluestone.xpm", mlx) != 0)
	{
		return (1);
	}
	if (load_tex(&wm->tex[3], "imgs/colorstone.xpm", mlx) != 0)
	{
		return (1);
	}
	if (load_tex(&wm->tex[4], "imgs/greystone.xpm", mlx) != 0)
	{
		return (1);
	}
	if (load_tex(&wm->tex[5], "imgs/mossy.xpm", mlx) != 0)
	{
		return (1);
	}
	if (load_tex(&wm->tex[6], "imgs/purplestone.xpm", mlx) != 0)
	{
		return (1);
	}
	if (load_tex(&wm->tex[7], "imgs/redbrick.xpm", mlx) != 0)
	{
		return (1);
	}
	if (load_tex(&wm->tex[8], "imgs/pillar.xpm", mlx) != 0)
	{
		return (1);
	}
	if (load_tex(&wm->tex[9], "imgs/greenlight.xpm", mlx) != 0)
	{
		return (1);
	}
	if (load_tex(&wm->tex[10], "imgs/barrel.xpm", mlx) != 0)
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
	if (init_sprites(&game->sprites) != 0)
		ft_error("Error assigning memory to sprites");
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
