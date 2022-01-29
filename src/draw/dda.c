#include "draw.h"
#include "game.h"

void	dda(t_game *game, t_ray *ray)
{
	while (42)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_x][ray->map_y] == '1')
			break ;
	}
}
