#include "cubfile.h"

static void	set_player_dir(t_cub_file *cub_file, t_dir dir)
{
	cub_file->dir_x = dir.dir_x;
	cub_file->dir_y = dir.dir_y;
	cub_file->plane_x = dir.plane_x;
	cub_file->plane_y = dir.plane_y;
}

void	init_player_dir(t_cub_file *cub_file)
{
	const size_t	x = cub_file->pos_x;
	const size_t	y = cub_file->pos_y;

	if (cub_file->map[y][x] == 'N')
	{
		set_player_dir(cub_file, (t_dir){0, -1, -0.66, 0});
	}
	if (cub_file->map[y][x] == 'S')
	{
		set_player_dir(cub_file, (t_dir){0, 1, 0.66, 0});
	}
	if (cub_file->map[y][x] == 'W')
	{
		set_player_dir(cub_file, (t_dir){-1, 0, 0, 0.66});
	}
	if (cub_file->map[y][x] == 'E')
	{
		set_player_dir(cub_file, (t_dir){1, 0, 0, -0.66});
	}
	cub_file->map[y][x] = '0';
}
