#ifndef MLXUTILS_H
#define MLXUTILS_H

# define WIDTH 640
# define HEIGHT 480
#define MINIM_W  (WIDTH / 5)
#define MINIM_H  (HEIGHT / 5)
#define MAP_W 24
#define MAP_H 24

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
	//TODO:Textures
}	t_wmap;


typedef struct s_game {
	t_mlxconf	mlxconf;
	t_keys		keys;
	t_motion	motion;
	t_wmap		wmap;
	clock_t		clock;
}	t_game;

int	init_gamedata(t_game *game, char *title);
void	ft_set_bg(t_mlxconf *conf);
void	ft_update_img(t_mlxconf *conf);
void	ft_pixel_put(int x, int y, int color, t_mlximg *conf);
void	ft_update_img(t_mlxconf *conf);
void	ft_draw_line(int x1, int y1, int x2, int y2, int color, t_mlximg *mlximg);
void	init_keys(t_keys *keys);
int		game_init(t_game *game, char *title);
void	ray_constants(t_motion *motion);


#endif
