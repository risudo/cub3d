#include "cub3d.h"

void	draw_line(t_game *game, t_ray *ray, t_texture *texture, int x)
{
	unsigned int	color;
	int				y;

	y = 0;
	while (y < ray->draw_start && y < game->screen_height)
		set_pixel_color(&game->screen, x, y++, game->sky_color);
	while (y < ray->draw_end && y < game->screen_height)
	{
		texture->texture_y = (int)texture->texture_pos & (texture->wall->height - 1);
		texture->texture_pos += texture->step;
		color = get_pixel_color(texture->wall, texture->texture_x, texture->texture_y);
		set_pixel_color(&game->screen, x, y++, color);
	}
	while (y < game->screen_height)
		set_pixel_color(&game->screen, x, y++, game->ground_color);
}
