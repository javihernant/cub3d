#include "mlxutils.h"
#include "libft.h"
#include "game.h"
int game_loop(t_game *game)
{
	raydir_calc(&game->motion);
	draw_map(&game->mlxconf, &game->wmap, &game->motion);
	obstacle_dist(&game->motion, game->wmap.wmap);
	draw_rays(&game->mlxconf, &game->wmap, &game->motion);
	ft_set_bg(&game->mlxconf.world);
	draw_3d(&game->mlxconf.world, &game->motion, &game->wmap);
	ft_update_img(&game->mlxconf);
	mod_pos(&game->clock, &game->keys, &game->motion, &game->wmap);
	return (1);
}

int main(void)
{
	t_game	game;

	if (game_init(&game, "Cub3D 42") != 0)
		ft_error("Error initializing game");
	mlx_hook(game.mlxconf.win, KeyPress, KeyPressMask, key_press, &game.keys);
	mlx_hook(game.mlxconf.win, KeyRelease, KeyReleaseMask, key_release, &game.keys);
	mlx_loop_hook(game.mlxconf.mlx, game_loop, &game);
	mlx_loop(game.mlxconf.mlx);
	return (0);
}
