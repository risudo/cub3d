#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

static void	destroy_textures(t_game *game)
{
	if (game->texture_n.img)
		mlx_destroy_image(game->mlx, game->texture_n.img);
	if (game->texture_s.img)
		mlx_destroy_image(game->mlx, game->texture_s.img);
	if (game->texture_w.img)
		mlx_destroy_image(game->mlx, game->texture_w.img);
	if (game->texture_e.img)
		mlx_destroy_image(game->mlx, game->texture_e.img);
}

int	destroy_and_exit(void *arg)
{
	t_game	*game;

	game = (t_game *)arg;
	game->mlx;
	mlx_destroy_window(game->mlx, game->win);
	destroy_textures(game);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(1);
	return (0);
}