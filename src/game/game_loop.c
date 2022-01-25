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

static void	move_player(t_game *game, double angle)
{
	const int	new_posX = (int)(game->posX - game->dirX * MOVE_SPEED);
	const int	new_posY = (int)(game->posY - game->dirY * MOVE_SPEED);

	rotate_player(game, angle);
	if (game->map[new_posX][(int)game->posY] == '0')
		game->posX -= game->dirX * MOVE_SPEED;
	if (game->map[(int)game->posX][new_posY] == '0')
		game->posY -= game->dirY * MOVE_SPEED;
	rotate_player(game, -angle);
}

static void	update_player(t_game *game)
{
	if (game->is_moving)
		move_player(game, game->move_dir);
	if (game->is_roteting)
		rotate_player(game, game->move_dir);
}

int	game_loop(t_game *game)
{
	update_player(game);
	draw_screen(game);
	return (0);
}
