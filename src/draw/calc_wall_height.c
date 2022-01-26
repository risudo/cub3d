#include "cub3d.h"

void	calc_wall_height(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	ray->lineHeight = (int)(game->screenHeight / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + game->screenHeight / 2 + \
					game->pitch;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + game->screenHeight / 2 + game->pitch;
	if (ray->drawEnd >= game->screenHeight)
		ray->drawEnd = game->screenHeight - 1;
}
