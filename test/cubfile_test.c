#include "../include/cubfile.h"
#include "utils.h"
#include <libc.h>

void	end(void)__attribute__((destructor));

void	end(void)
{
	pid_t	current_pid;
	char	cmd_str[50];
	int		ret;

	current_pid = getpid();
	sprintf(cmd_str, "%s %d %s\n", "leaks", current_pid, ">> leaks.txt 2>&1");
	ret = system(cmd_str);
	if (ret)
		printf("\e[31m!leak detected!\e[0m\n");
}

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
	t_cub_file	cubfile;
	char		**file_content;

	file_content = read_file(av[1]);
	init_cub_file(&cubfile, file_content);
	clear_string_array(file_content);
	printf("north_wall_path  : %s\n", cubfile.north_wall_path);
	printf("south_wall_path  : %s\n", cubfile.south_wall_path);
	printf("west_wall_path: %s\n", cubfile.west_wall_path);
	printf("east_wall_path   : %s\n", cubfile.east_wall_path);
	printf("sky_color: %d,  ground_color: %d\n", cubfile.sky_color, cubfile.ground_color);
	print_map(cubfile.map);
	exit(0);
	(void)ac;
}
