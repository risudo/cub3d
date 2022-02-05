/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_wall_height.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyokota <nyokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:35 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/05 15:27:30 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "define.h"
#include "draw.h"
#include "game.h"

void	calc_wall_height(t_ray *ray)
{
	if (ray->side == X_SIDE)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	if (ray->perp_wall_dist)
		ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	else
		ray->line_height = INF;
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2 + PITCH;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2 + PITCH;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}
