#include "cubfile.h"
#include "utils.h"

static bool	is_player_pos(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static bool	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player_pos(c));
}

static void	set_player(t_cub_file *cub_file, bool *is_player, int x, int y)
{
	*is_player = true;
	cub_file->pos_x = x;
	cub_file->pos_y = y;
}

void	init_player_pos(t_cub_file *cub_file)
{
	size_t	i;
	size_t	j;
	bool	is_player;

	i = 0;
	is_player = false;
	while (cub_file->map[i])
	{
		j = 0;
		while (cub_file->map[i][j])
		{
			if (!is_valid_char(cub_file->map[i][j]))
				xput_error("invalid character");
			if (is_player && is_player_pos(cub_file->map[i][j]))
				xput_error("multiple player");
			if (is_player_pos(cub_file->map[i][j]))
				set_player(cub_file, &is_player, j, i);
			j++;
		}
		i++;
	}
	if (!is_player)
		xput_error("non player");
}
