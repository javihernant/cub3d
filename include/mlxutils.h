#ifndef MLXUTILS_H
#define MLXUTILS_H

# define WIDTH 640
# define HEIGHT 480
#define MINIM_W  WIDTH / 5;
#define MINIM_H  HEIGHT / 5;
#define MAP_W 24
#define MAP_H 24

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

typedef struct s_keys {
	char	w;
	char	a;
	char	s;
	char	d;
	char	left;
	char	right;
}	t_keys;

int	ft_mlx_init(t_mlxconf *mlx, char *title);
void	ft_set_bg(t_mlxconf *conf);
void	ft_update_img(t_mlxconf *conf);
void	ft_pixel_put(int x, int y, int color, t_mlxconf *conf);
void	ft_update_img(t_mlxconf *conf);
void	ft_draw_line(int x1, int y1, int x2, int y2, int color, t_mlxconf *conf);
void	init_keys(t_keys *keys);


#endif
