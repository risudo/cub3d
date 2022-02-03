#include "game.h"
#include "define.h"
#include "draw.h"
#include <math.h>

static void	rotate_player(t_game *game, double angle)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = game->dir_x;
	game->dir_x = game->dir_x * cos(angle) - game->dir_y * sin(angle);
	game->dir_y = oldDirX * sin(angle) + game->dir_y * cos(angle);
	oldPlaneX = game->plane_x;
	game->plane_x = game->plane_x * cos(angle) - game->plane_y * sin(angle);
	game->plane_y = oldPlaneX * sin(angle) + game->plane_y * cos(angle);
}

static bool	is_floor(int c)
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
	new_posX = (int)(game->pos_x - game->dir_x * MOVE_SPEED * 1.1);
	new_posY = (int)(game->pos_y - game->dir_y * MOVE_SPEED * 1.1);
	if (is_floor(game->map[new_posX][new_posY]))
	{
		game->pos_x -= game->dir_x * MOVE_SPEED;
		game->pos_y -= game->dir_y * MOVE_SPEED;
	}
	rotate_player(game, -angle);
}

static void	update_player(t_game *game)
{
	if (game->is_moving)
		move_player(game, game->move_dir);
	if (game->is_rotating)
		rotate_player(game, game->move_dir);
}

int	game_loop(t_game *game)
{
	update_player(game);
	draw_screen(game);
	return (0);
}
