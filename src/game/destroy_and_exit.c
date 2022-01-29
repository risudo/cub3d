#include "game.h"
#include "mlx.h"
#include <stdlib.h>

static void	destroy_textures(t_game *game)
{
	if (game->north_wall.img)
		mlx_destroy_image(game->mlx, game->north_wall.img);
	if (game->south_wall.img)
		mlx_destroy_image(game->mlx, game->south_wall.img);
	if (game->west_wall.img)
		mlx_destroy_image(game->mlx, game->west_wall.img);
	if (game->east_wall.img)
		mlx_destroy_image(game->mlx, game->east_wall.img);
}

int	destroy_and_exit(void *arg)
{
	t_game	*game;

	game = (t_game *)arg;
	mlx_destroy_window(game->mlx, game->win);
	destroy_textures(game);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (0);
}
