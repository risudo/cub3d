#include <stdio.h>
#include <stdbool.h>
#include "utils.h"
#include "cubfile.h"

static bool	flood_fill(char **map, int x, int y)
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

static bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player_pos(c));
}

static void	check_map_char(char **map)
{
	size_t	i;
	size_t	j;
	bool	is_player;

	i = 0;
	is_player = false;
	if (!*map)
		xput_error("map");
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_char(map[i][j]))
				xput_error("map");
			if (is_player_pos(map[i][j]) && is_player)
				xput_error("map");
			if (is_player_pos(map[i][j]))
			{
				is_player = true;
			}
			j++;
		}
		i++;
	}
	if (!is_player)
		xput_error("map");
}

int	validate_map(char **map, int player_pos_x, int player_pos_y)
{
	char	**copy;
	bool	error;

	check_map_char(map);
	copy = duplicate_map(map);
	error = flood_fill(copy, player_pos_x, player_pos_y);
	clear_string_array(copy);
	if (error)
		xput_error("map");
	return (0);
}
