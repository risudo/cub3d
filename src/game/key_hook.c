#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

int	key_press_hook(int key_code, t_game *game)
{
	if (key_code == KEY_W)
		game->move_dir = M_PI;
	if (key_code == KEY_A)
		game->move_dir = -M_PI_2;
	if (key_code == KEY_S)
		game->move_dir = 0.0;
	if (key_code == KEY_D)
		game->move_dir = M_PI_2;
	if (key_code == KEY_LEFT)
		game->move_dir = ROTATE_SPEED;
	if (key_code == KEY_RIGHT)
		game->move_dir = -ROTATE_SPEED;
	if (key_code == KEY_ESC)
		destroy_and_exit(game);
	if (key_code == KEY_W || \
		key_code == KEY_A || \
		key_code == KEY_S || \
		key_code == KEY_D)
		game->is_moving = true;
	if (key_code == KEY_LEFT || \
		key_code == KEY_RIGHT)
		game->is_roteting = true;
	return (0);
}

int	key_release_hook(int key_code, t_game *game)
{
	if (game->is_moving)
		game->is_moving = false;
	if (game->is_roteting)
		game->is_roteting = false;
	return (0);
}
