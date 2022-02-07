/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:40 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/07 21:33:43 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "mlx.h"
#include "cubfile.h"
#include "utils.h"
#include "define.h"

void	init_game(t_game *game, t_cub_file *cub_file)
{
	game->mlx = mlx_xinit();
	game->win = \
		mlx_xnew_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	game->screen.img = \
		mlx_xnew_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->screen.addr = \
		mlx_get_data_addr(game->screen.img, &game->screen.bits_per_pixel, \
						&game->screen.line_length, &game->screen.endian);
	game->pos_x = cub_file->pos_x;
	game->pos_y = cub_file->pos_y;
	game->dir_x = cub_file->dir_x;
	game->dir_y = cub_file->dir_y;
	game->plane_x = cub_file->plane_x;
	game->plane_y = cub_file->plane_y;
	game->floor_color = cub_file->floor_color;
	game->ceiling_color = cub_file->ceiling_color;
	game->is_moving = false;
	game->is_rotating = false;
	game->move_dir = 0.0;
	game->map = cub_file->map;
}
