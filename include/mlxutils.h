#ifndef MLXUTILS_H
#define MLXUTILS_H

# define WIDTH 640
#define HEIGHT 480
# include "mlx.h"

typedef struct s_mlxconf {
	void	*mlx;
	void	*win;
	void	*img;
	char	*buff;
	int		bpp;
	int		line_length;
	int		endian;
}	t_mlxconf;

int	ft_mlx_init(t_mlxconf *mlx, char *title);


#endif
