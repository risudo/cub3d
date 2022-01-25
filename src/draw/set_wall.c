#include "cub3d.h"

void	set_wall(t_game *game, t_ray *ray, t_texture *texture)
{
	if (ray->side == 0)
	{
		if (ray->rayDirX > 0)
			texture->wall = &game->texture_e;
		else
			texture->wall = &game->texture_w;
	}
	else
	{
		if (ray->rayDirY > 0)
			texture->wall = &game->texture_s;
		else
			texture->wall = &game->texture_n;
	}
}
