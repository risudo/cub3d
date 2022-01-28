#ifndef CUBFILE_H
#define CUBFILE_H
#include <stdbool.h>
#include <stdio.h>

typedef struct	cub_file {
	char			*north_wall_path;
	char			*south_wall_path;
	char			*western_wall_path;
	char			*east_wall_path;
	unsigned int	sky_color;
	unsigned int	ground_color;
	char			**map;
	int				pos_x; //? size_tにしたら動かなくなるのなんで？？
	int				pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}	t_cub_file;

char	**read_file(char *filepath);
bool	init_cub_file(t_cub_file *cub_file, char **file_content);
int	validate_map(char **map, int *player_pos_x, int *player_pos_y);
#endif
