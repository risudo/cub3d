/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_coordinates_of_wall.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyokota <nyokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:34 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/04 16:24:03 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "game.h"
#include <math.h>

void	calc_coordinates_of_wall(t_game *game, t_ray *ray, t_texture *texture)
{
	if (ray->side == 0)
		texture->wall_x = game->pos_y - ray->perp_wall_dist * ray->dir_y;
	else
		texture->wall_x = game->pos_x + ray->perp_wall_dist * ray->dir_x;
	texture->wall_x -= floor(texture->wall_x);
	texture->texture_x = \
			(int)(texture->wall_x * (double)(texture->wall->width));
	if (ray->side == 0 && ray->dir_x > 0)
		texture->texture_x = texture->wall->width - texture->texture_x - 1;
	if (ray->side == 1 && ray->dir_y > 0)
		texture->texture_x = texture->wall->width - texture->texture_x - 1;
	texture->step = 1.0 * texture->wall->height / ray->line_height;
	texture->texture_pos = \
				(ray->draw_start - game->pitch - game->screen_height / 2.0 + \
				ray->line_height / 2.0) * \
				texture->step;
}
