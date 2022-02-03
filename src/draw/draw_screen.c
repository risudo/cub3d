/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:37 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:37 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "draw.h"
#include "game.h"

int	draw_screen(t_game *game)
{
	t_ray		ray;
	t_texture	texture;
	int			x;

	x = 0;
	while (x < game->screen_width)
	{
		init_ray(game, &ray, x);
		dda(game, &ray);
		set_wall(game, &ray, &texture);
		calc_wall_height(game, &ray);
		calc_coordinates_of_wall(game, &ray, &texture);
		draw_line(game, &ray, &texture, x);
		++x;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	return (0);
}
