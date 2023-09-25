#include "mlxutils.h"
#include <stdlib.h>
#include "libft.h"

void	init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
}

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

void	ft_set_bg(t_mlximg *img)
{
	int		i;
	int		j;

	i = 0;
	while (i < img->h)
	{
		j = 0;
		while (j < img->w)
		{
			ft_pixel_put(j, i, 0xffffff, img);
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
