#include <stdio.h>
#include <stdbool.h>
#include "utils.h"

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
	copy = (char**)xmalloc((sizeof(char *)) * (map_row + 1));
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[i] = NULL;
	return copy;
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

int	check_map_char(char **map, int *player_pos_x, int *player_pos_y)
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

int	validate_map(char **map, int *player_pos_x, int *player_pos_y)
{
	char	**copy;
	bool	error;
	size_t	map_row;

	if (!map[0] || check_map_char(map, player_pos_x, player_pos_y) == -1)
		xput_error("map error");
	map_row = count_map_row(map);
	copy = allocate_copy_map(map, map_row);
	error = flood_fill(copy, *player_pos_x, *player_pos_y);
	clear_string_array(copy);
	if (error)
		xput_error("map error");
	return (0);
}
