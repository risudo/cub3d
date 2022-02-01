#include "draw.h"
#include "game.h"

void	set_wall(t_game *game, t_ray *ray, t_texture *texture)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			texture->wall = &game->north_wall;
		else
			texture->wall = &game->south_wall;
	}
	else
	{
		if (ray->dir_y > 0)
			texture->wall = &game->west_wall;
		else
			texture->wall = &game->east_wall;
	}
}
