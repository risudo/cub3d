#include "define.h"
#include "draw.h"
#include "game.h"

void	calc_wall_height(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	if (ray->perp_wall_dist)
		ray->line_height = (int)(game->screen_height / ray->perp_wall_dist);
	else
		ray->line_height = INF;
	ray->draw_start = -ray->line_height / 2 + game->screen_height / 2 + \
					game->pitch;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = \
			ray->line_height / 2 + game->screen_height / 2 + game->pitch;
	if (ray->draw_end >= game->screen_height)
		ray->draw_end = game->screen_height - 1;
}
