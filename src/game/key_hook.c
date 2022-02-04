/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyokota <nyokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:41 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/04 16:01:21 by nyokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "game.h"
#include "define.h"
#include <stdlib.h>
#include <math.h>

/*
#include <stdio.h>
#define CLEAR "\033[1;1H\033[0J"
void	print_player_info(t_game *game)
{
	printf("%s\n", CLEAR);
	printf("pos_x: %lf\n", game->pos_x);
	printf("pos_y: %lf\n", game->pos_y);
	printf("dir_x: %lf\n", game->dir_x);
	printf("dir_y: %lf\n", game->dir_y);
}
*/

static bool	is_move_key(int key_code)
{
	return (key_code == KEY_W || \
		key_code == KEY_A || \
		key_code == KEY_S || \
		key_code == KEY_D);
}

static bool	is_rotate_key(int key_code)
{
	return (key_code == KEY_LEFT || \
		key_code == KEY_RIGHT);
}

int	key_press_hook(int key_code, t_game *game)
{
	if (key_code == KEY_W)
		game->move_dir = 0.0;
	if (key_code == KEY_A)
		game->move_dir = M_PI_2;
	if (key_code == KEY_S)
		game->move_dir = M_PI;
	if (key_code == KEY_D)
		game->move_dir = -M_PI_2;
	if (key_code == KEY_LEFT)
		game->move_dir = ROTATE_SPEED;
	if (key_code == KEY_RIGHT)
		game->move_dir = -ROTATE_SPEED;
	if (key_code == KEY_ESC)
		destroy_and_exit(game);
	if (is_move_key(key_code))
	{
		game->is_moving = true;
		game->is_rotating = false;
	}
	if (is_rotate_key(key_code))
	{
		game->is_moving = false;
		game->is_rotating = true;
	}
	return (0);
}

int	key_release_hook(int key_code, t_game *game)
{
	if (game->is_moving && is_move_key(key_code))
		game->is_moving = false;
	if (game->is_rotating && is_rotate_key(key_code))
		game->is_rotating = false;
	return (0);
}
