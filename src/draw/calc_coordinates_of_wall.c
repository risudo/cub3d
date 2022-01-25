#include "cub3d.h"

void	calc_coordinates_of_wall(t_game *game, t_ray *ray, t_texture *texture)
{
	if (ray->side == 0)
		texture->wallX = game->posY + ray->perpWallDist * ray->rayDirY;
	else
		texture->wallX = game->posX + ray->perpWallDist * ray->rayDirX;
	texture->wallX -= floor(texture->wallX);
	texture->textureX = (int)(texture->wallX * (double)(texture->wall->width));
	if (ray->side == 0 && ray->rayDirX > 0)
		texture->textureX = texture->wall->width - texture->textureX - 1;
	if (ray->side == 1 && ray->rayDirY < 0)
		texture->textureX = texture->wall->width - texture->textureX - 1;
	texture->step = 1.0 * texture->wall->height / ray->lineHeight;
	texture->texturePos = (ray->drawStart - game->pitch - game->screenHeight / 2.0 + \
				ray->lineHeight / 2.0) * \
				texture->step;
}
