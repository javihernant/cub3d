#include "mlxutils.h"

void	init_mlxconf(t_mlxconf *conf)
{
	conf->buff = 0;
	conf->img = 0;
	conf->mlx = 0;
	conf->win = 0;
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
