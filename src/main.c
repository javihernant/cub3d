#include "mlxutils.h"
#include "libft.h"

int main(void)
{
	t_mlxconf	conf;

	if (ft_mlx_init(&conf, "Cub3D 42") != 0)
		ft_error("Error initializing mlx");
	mlx_loop(conf.mlx);
	return (0);
}
