#include "mlxutils.h"
#include <stdlib.h>

void	init_mlxconf(t_mlxconf *conf)
{
	conf->buff = 0;
	conf->img = 0;
	conf->mlx = 0;
	conf->win = 0;
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

int	ft_mlx_init(t_mlxconf *conf, char *title)
{
	init_mlxconf(conf);
	conf->mlx = mlx_init();
	if (!conf->mlx)
		return (1);
	conf->win = mlx_new_window(conf->mlx, WIDTH, HEIGHT,
			title);
	if (!conf->win)
		return (1);
	conf->img = mlx_new_image(conf->mlx, WIDTH, HEIGHT);
	if (!conf->img)
		return (1);
	conf->buff = mlx_get_data_addr(conf->img, &conf->bpp,
			&conf->line_length, &conf->endian);
	if (!conf->buff)
		return (1);
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

void	ft_pixel_put(int x, int y, int color, t_mlxconf *conf)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
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
			ft_pixel_put(j, i, 0xffffff, conf);
			j++;
		}
		i++;
	}
}

void	ft_update_img(t_mlxconf *conf)
{
	// int y = 0;
	// while (y < HEIGHT)
	// {
	// 	int x = 0;
	// 	while (x < WIDTH)
	// 	{
	// 		((conf->imgbuff))[y * conf->line_length + x * (conf->bpp / 8)] = ((conf->buff))[y * conf->line_length + x * (conf->bpp / 8)];
	// 		x++;
	// 	}
	// 	y++;
	// }
	mlx_put_image_to_window(conf->mlx, conf->win,
		conf->img, 0, 0);
}
