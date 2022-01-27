#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <libc.h>
/* #include "../../include/utils.h" */

static bool flood_fill(char **map, int x, int y)
{
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

static char **allocate_copy_map(char **map, size_t map_row)
{
	char	**copy;
	size_t	i;

	i = 0;
	copy = (char**)malloc((sizeof(char *)) * (map_row + 1)); //TODO:use xmalloc
	while (map[i])
	{
		copy[i] = strdup(map[i]); //TODO:use ft_strdup
		i++;
	}
	copy[i] = NULL;
	return copy;
}

static void free_copy_map(char **map) //splitのやつ使えるかも？
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static size_t	count_map_row(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

bool	is_player_pos(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player_pos(c));
}

int	check_map_char(char **map, size_t *player_pos_x, size_t *player_pos_y)
{
	size_t	i;
	size_t	j;
	bool	is_player;

	i = 0;
	is_player = false;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_char(map[i][j]))
				return (-1);
			if (is_player_pos(map[i][j]) && is_player)
				return (-1);
			if (is_player_pos(map[i][j]))
			{
				*player_pos_x = j;
				*player_pos_y = i;
				is_player = true;
			}
			j++;
		}
		i++;
	}
	return (is_player);
}

int	validate_map(char **map, size_t *player_pos_x, size_t *player_pos_y)
{
	char	**copy;
	bool	error;
	size_t	map_row;

	if (check_map_char(map, player_pos_x, player_pos_y) == -1)
		return (-1);
	map_row = count_map_row(map);
	copy = allocate_copy_map(map, map_row);
	error = flood_fill(copy, *player_pos_x, *player_pos_y);
	free_copy_map(copy);
	if (error)
		return (-1);
	return (0);
}

// validate_map でプレイヤーの場所出してから init_player
//
