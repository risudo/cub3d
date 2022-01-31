#include "game.h"
#include "mlx.h"
#include "cubfile.h"
#include "utils.h"

void	init_game(t_game *game, t_cub_file *cub_file)
{
	game->screen_width = 640;
	game->screen_height = 480;
	game->mlx = mlx_xinit();
	game->win = \
		mlx_xnew_window(game->mlx, \
		game->screen_width, game->screen_height, "cub3d");
	game->screen.img = \
		mlx_xnew_image(game->mlx, \
		game->screen_width, game->screen_height);
	game->screen.addr = \
		mlx_get_data_addr(game->screen.img, &game->screen.bits_per_pixel, \
						&game->screen.line_length, &game->screen.endian);
	game->pos_x = cub_file->pos_x;
	game->pos_y = cub_file->pos_y;
	game->dir_x = cub_file->dir_x;
	game->dir_y = cub_file->dir_y;
	game->plane_x = cub_file->plane_x;
	game->plane_y = cub_file->plane_y;
	game->pitch = 100;
	game->sky_color = cub_file->sky_color;
	game->ground_color = cub_file->ground_color;
	game->is_moving = 0;
	game->is_rotating = 0;
	game->move_dir = 0.0;
	game->map = cub_file->map;
}
