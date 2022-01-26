#include <stdio.h>
#include <fcntl.h>
#include "../include/cubfile.h"
#include <stdbool.h>

void print_map(char **map)
{
	for (int i = 0; map[i]; i++)
	{
		for (int j = 0; map[i][j]; j++)
		{
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

int main(int ac, char **av)
{
	t_cub_file cubfile;
	int fd;
	char **file_content;
	bool err;

	file_content = read_file(av[1]);
	err = init_cub_file(&cubfile, file_content);
	printf("err: %d\n", err);
	printf("north_wall_path  : %s\n", cubfile.north_wall_path);
	printf("south_wall_path  : %s\n", cubfile.south_wall_path);
	printf("western_wall_path: %s\n", cubfile.western_wall_path);
	printf("east_wall_path   : %s\n", cubfile.east_wall_path);
	printf("sky_color: %d,  ground_color: %d\n", cubfile.sky_color, cubfile.ground_color);
	print_map(cubfile.map);
}