#ifndef MLXUTILS_H
#define MLXUTILS_H

# define WIDTH 640
# define HEIGHT 480
# define MINIM_W  (WIDTH / 5)
# define MINIM_H  (HEIGHT / 5)


# include "mlx.h"

# include <X11/X.h>
# include <X11/keysym.h>
# include <time.h>
# include <math.h>

typedef struct s_mlximg {
	void	*img;
	char	*buff;
	int		w;
	int		h;
	int		bpp;
	int		line_length;
	int		endian;
}	t_mlximg;

typedef struct s_mlxconf {
	void		*mlx;
	void		*win;
	t_mlximg	minimap;
	t_mlximg	world;
}	t_mlxconf;

typedef struct s_motion {
	double	posx;
	double	posy;
	double	stepx;
	double	stepy;
	double	planex;
	double	planey;
	double	dirx;
	double	diry;
	double	obsdist[WIDTH];
	double	rays[WIDTH];
	double raydirx[WIDTH];
	double raydiry[WIDTH];
	char	side[WIDTH];
	int		**wmap;
	int		wmap_w;
	int		wmap_h;
}	t_motion;

typedef struct s_keys {
	char	w;
	char	a;
	char	s;
	char	d;
	char	left;
	char	right;
}	t_keys;


typedef struct s_wmap {
	int	**wmap;
	int	w;
	int	h;
	t_mlximg **tex; //TODO: change to (t_mlximg *)
}	t_wmap;

typedef struct s_sprt {
	double x;
	double y;
	int txnum;
}	t_sprt;

typedef struct s_spsort {
	int	order;
	double dist;
}	t_spsort;

typedef struct s_spdata {
	int	n;
	t_spsort *sort;
	t_sprt	*sprites;
}	t_spdata;


typedef struct s_game {
	t_mlxconf	mlxconf;
	t_keys		keys;
	t_motion	motion;
	t_spdata	sprites;
	t_wmap		wmap;
	clock_t		clock;
}	t_game;

int	ft_mlx_init(t_mlxconf *conf, char *title);
void	ft_set_bg(t_mlximg *img);
void	ft_update_img(t_mlxconf *conf);
void	ft_pixel_put(int x, int y, int color, t_mlximg *conf);
void	ft_update_img(t_mlxconf *conf);
void	ft_draw_line(int x1, int y1, int x2, int y2, int color, t_mlximg *mlximg);
void	init_keys(t_keys *keys);
int		key_release(int keycode, t_keys *keys);
int		key_press(int keycode, t_keys *keys);
void	ray_constants(t_motion *motion);


#endif
