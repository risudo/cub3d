#include "game.h"
#include "mlx.h"
#include "utils.h"
#include <stdlib.h>

static void	destroy_images(t_game *game)
{
	mlx_destroy_image(game->mlx, game->north_wall.img);
	mlx_destroy_image(game->mlx, game->south_wall.img);
	mlx_destroy_image(game->mlx, game->west_wall.img);
	mlx_destroy_image(game->mlx, game->east_wall.img);
	mlx_destroy_image(game->mlx, game->screen.img);
}

int	destroy_and_exit(void *arg)
{
	t_game	*game;

	game = (t_game *)arg;
	mlx_destroy_window(game->mlx, game->win);
	destroy_images(game);
	clear_string_array(game->map);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}
