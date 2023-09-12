#ifndef MLXUTILS_H
#define MLXUTILS_H

# define WIDTH 640
#define HEIGHT 480
# include "mlx.h"

# include <X11/X.h>
# include <X11/keysym.h>


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
void	ft_set_bg(t_mlxconf *conf);
void	ft_update_img(t_mlxconf *conf);
void	ft_pixel_put(int x, int y, int color, t_mlxconf *conf);
void	ft_update_img(t_mlxconf *conf);



#endif
