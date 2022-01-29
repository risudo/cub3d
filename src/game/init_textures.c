#include "mlx.h"
#include "game.h"
#include "cubfile.h"

void	init_texture(t_img *img, void *mlx, char *path)
{
	img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
								&img->line_length, &img->endian);
}

void	init_textures(t_game *game, t_cub_file *cub_file)
{
	init_texture(&game->north_wall, game->mlx, cub_file->north_wall_path);
	init_texture(&game->south_wall, game->mlx, cub_file->south_wall_path);
	init_texture(&game->west_wall, game->mlx, cub_file->west_wall_path);
	init_texture(&game->east_wall, game->mlx, cub_file->east_wall_path);
}
