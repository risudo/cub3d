#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libc.h>
/* #include "../../include/utils.h" */

#define CLEAR "\033[1;1H\033[0J"
#define RED "\033[31m"
#define RESET "\033[39m"

void	print_map(char **map)
{
	printf("%s\n", CLEAR);
	for (int i = 0; map[i]; i++)
	{
		for (int j = 0; map[i][j]; j++)
		{
			if (map[i][j] == 'x')
				printf("%s", RED);
			printf("%c", map[i][j]);
			printf("%s", RESET);
		}
		printf("\n");
	}
	printf("\n");
	usleep(30000);
}

bool flood_fill(char **map, int x, int y)
{
	print_map(map);
	if (x < 0 || y < 0 || !map[y] || map[y][x] == ' ' || map[y][x] == '\0')
	{
		return (true);
	}
	if (map[y][x] == 'x')
	{
		return (false);
	}
	if (map[y][x] == '1')
	{
		return (false);
	}
	map[y][x] = 'x';
	return (flood_fill(map, x + 1, y) || flood_fill(map, x - 1, y) 
			|| flood_fill(map, x, y + 1) || flood_fill(map, x, y - 1));
}

char **allocate_copy_map(char **map, size_t map_row)
{
	char	**copy;
	size_t	i;

	i = 0;
	copy = (char**)malloc((sizeof(char *)) * (map_row + 1));
	while (map[i])
	{
		copy[i] = strdup(map[i]); //TODO:ft_strdup使う
		i++;
	}
	copy[i] = NULL;
	return copy;
}

void free_copy_map(char **map) //splitのやつ使えるかも？
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		printf("free\n");
		free(map[i]);
	}
		printf("free 2d\n");
	free(map);
}

size_t	count_map_row(char **map)
{
	size_t	i;

	while (map[i])
	{
		i++;
	}
	return (i);
}

bool	validate_map(char **map, int x, int y)
{
	char	**copy;
	bool	ret;
	size_t	map_row;

	map_row = count_map_row(map);
	copy = allocate_copy_map(map, map_row);
	ret = flood_fill(copy, x, y);
	/* free_copy_map(copy); */
	return (ret);
}

int main(void)
{
	char *map2[] = {
		"        1111111111111111111111111",
		"        1000000000110000000000001",
		"        1011000001110000000000001",
		"        1001000000000000000000001",
		"111111111011000001110000000000001",
		"100000000011000001110111110111111",
		"11110111111111011100000010001",
		"11110111111111011101010010001",
		"11000000110101011100000010001",
		"10000000000000001100000010001",
		"10000000000000001101010010001",
		"11000001110101011111011110N0111",
		"11110111 1110101 101111010001",
		"11111111 1111111 111111111111",
		NULL,
	};
	char *error_map1[] = {
		"        1111111111111111111111111",
		"        1000000000110000000000001",
		"        1011000001110000000000001",
		"        1001000000000000000000001",
		"111111011011000001110000000000001",
		"100000000011000001110111110111111",
		"11110111111111011100000010001",
		"11110111111111011101010010001",
		"11000000110101011100000010001",
		"10000000000000001100000010001",
		"10000000000000001101010010001",
		"11000001110101011111011110N0111",
		"11110111 1110101 101111010001",
		"11111111 1111111 111111111111",
		NULL,
	};
	printf("map2: %d\n", validate_map(error_map1, 26, 11));
}
