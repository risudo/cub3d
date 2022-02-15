/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyokota <nyokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:36 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/15 14:28:24 by nyokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "game.h"
#include "define.h"
#include <math.h>

void	draw_line(t_game *game, t_ray *ray, t_texture *texture, int x)
{
	unsigned int	color;
	int				y;

	y = 0;
	while (y < ray->draw_start && y < SCREEN_HEIGHT)
		set_pixel_color(&game->screen, x, y++, game->ceiling_color);
	while (y < ray->draw_end && y < SCREEN_HEIGHT)
	{
		texture->texture_y = \
			fmod(texture->texture_pos, texture->wall->height - 1);
		texture->texture_pos += texture->step;
		color = get_pixel_color(texture->wall, \
				texture->texture_x, texture->texture_y);
		set_pixel_color(&game->screen, x, y++, color);
	}
	while (y < SCREEN_HEIGHT)
		set_pixel_color(&game->screen, x, y++, game->floor_color);
}
