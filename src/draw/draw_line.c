#include "cub3d.h"

void	draw_line(t_game *game, t_ray *ray, t_texture *texture, int x)
{
	unsigned int	color;
	int				y;

	y = 0;
	while (y < ray->drawStart && y < game->screenHeight)
		set_pixel_color(&game->screen, x, y++, game->sky_color);
	while (y < ray->drawEnd && y < game->screenHeight)
	{
		texture->textureY = (int)texture->texturePos & (texture->wall->height - 1);
		texture->texturePos += texture->step;
		color = get_pixel_color(texture->wall, texture->textureX, texture->textureY);
		set_pixel_color(&game->screen, x, y++, color);
	}
	while (y < game->screenHeight)
		set_pixel_color(&game->screen, x, y++, game->ground_color);
}
