/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyokota <nyokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:39 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/05 15:45:13 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "define.h"
#include "draw.h"
#include <math.h>

static void	rotate_player(t_game *game, double radian)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = game->dir_x;
	game->dir_x = game->dir_x * cos(radian) - game->dir_y * sin(radian);
	game->dir_y = oldDirX * sin(radian) + game->dir_y * cos(radian);
	oldPlaneX = game->plane_x;
	game->plane_x = game->plane_x * cos(radian) - game->plane_y * sin(radian);
	game->plane_y = oldPlaneX * sin(radian) + game->plane_y * cos(radian);
}

static void	move_player(t_game *game, double radian)
{
	int	new_pos_x;
	int	new_pos_y;

	rotate_player(game, radian);
	new_pos_x = (int)(game->pos_x + game->dir_x * MOVE_SPEED * 1.1);
	new_pos_y = (int)(game->pos_y - game->dir_y * MOVE_SPEED * 1.1);
	if (game->map[new_pos_y][new_pos_x] == '0')
	{
		game->pos_x += game->dir_x * MOVE_SPEED;
		game->pos_y -= game->dir_y * MOVE_SPEED;
	}
	rotate_player(game, -radian);
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
