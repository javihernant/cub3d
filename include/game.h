#ifndef GAME_H
# define GAME_H

# include "mlxutils.h"

//Game init
int		read_map(t_wmap *wmap);
void	init_motion(t_motion *motion);
int		game_init(t_game *game, char *title);

//Raycasting and movement
void	draw_rays(t_mlxconf *conf, t_wmap *wmap, t_motion *mn);
void	draw_map(t_mlxconf *conf, t_wmap *wmap, t_motion *mn);
void	ray_constants(t_motion *motion);
void	draw_3d(t_mlximg *world, t_motion *mn);
void	obstacle_dist(t_motion *mn, int **wmap);
void	rotate_dir(double rotspeed, t_motion *mn);
void	mod_pos(clock_t *end, t_keys *keys, t_motion *mn, t_wmap *wmap);

#endif
