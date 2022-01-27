#include "cub3d.h"

static void	rotate_player(t_game *game, double angle)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = game->dirX;
	game->dirX = game->dirX * cos(angle) - game->dirY * sin(angle);
	game->dirY = oldDirX * sin(angle) + game->dirY * cos(angle);
	oldPlaneX = game->planeX;
	game->planeX = game->planeX * cos(angle) - game->planeY * sin(angle);
	game->planeY = oldPlaneX * sin(angle) + game->planeY * cos(angle);
}

static bool is_floor(int c)
{
	return (c == 'N' || \
			c == 'S' || \
			c == 'W' || \
			c == 'E' || \
			c == '0');
}

static void	move_player(t_game *game, double angle)
{
	int	new_posX;
	int	new_posY;

	rotate_player(game, angle);
	new_posX = (int)(game->posX - game->dirX * MOVE_SPEED);
	new_posY = (int)(game->posY - game->dirY * MOVE_SPEED);
	if (is_floor(game->map[new_posX][new_posY]))
	{
		game->posX -= game->dirX * MOVE_SPEED;
		game->posY -= game->dirY * MOVE_SPEED;
	}
	rotate_player(game, -angle);
}

static void	update_player(t_game *game)
{
	if (game->is_moving)
		move_player(game, game->move_dir);
	else if (game->is_roteting)
		rotate_player(game, game->move_dir);
}

int	game_loop(t_game *game)
{
	update_player(game);
	draw_screen(game);
	return (0);
}
