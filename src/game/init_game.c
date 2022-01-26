#include "cub3d.h"
#include "mlx.h"

void	init_game(t_game *game, t_cub_file *cub_file)
{
	game->screenWidth = 640;
	game->screenHeight = 480;
	game->mlx = mlx_init();
	game->win = \
		mlx_new_window(game->mlx, \
		game->screenWidth, game->screenHeight, "cub3d");
	game->screen.img = \
		mlx_new_image(game->mlx, \
		game->screenWidth, game->screenHeight);
	game->screen.addr = \
		mlx_get_data_addr(game->screen.img, &game->screen.bits_per_pixel, \
						&game->screen.line_length, &game->screen.endian);
	game->posX = cub_file->posX;
	game->posY = cub_file->posY;
	game->dirX = cub_file->dirX;
	game->dirY = cub_file->dirY;
	game->planeX = cub_file->planeX;
	game->planeY = cub_file->planeY;
	game->pitch = 100;
	game->sky_color = cub_file->sky_color;
	game->ground_color = cub_file->ground_color;
	game->is_moving = 0;
	game->is_roteting = 0;
	game->move_dir = 0.0;
	game->map = cub_file->map;
}
