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

int	validate_map(char **map, int player_pos_x, int player_pos_y)
{
	char	**copy;
	bool	error;

	copy = duplicate_map(map);
	error = flood_fill(copy, player_pos_x, player_pos_y);
	clear_string_array(copy);
	if (error)
		xput_error("map is not closed");
	return (0);
}
