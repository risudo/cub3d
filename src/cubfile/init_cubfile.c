#include <libc.h>
#include <stdbool.h>

#include "cubfile.h"
#include "utils.h"

char	*get_path_to_texture(char *direction, char *line)
{
	char	**splited;
	char	*ret;

	if (!line)
		xput_error("path to texture");
	splited = ft_split(line, ' ');
	if (!splited || !*splited || \
		ft_strncmp(*splited, direction, 3) || \
		!splited[1] || splited[2])
	{
		xput_error("path to texture");
	}
	ret = ft_strdup(splited[1]);
	clear_string_array(splited);
	return (ret);
}

unsigned char	cub_atoi(char **str, char end)
{
	unsigned char	ret;

	ret = 0;
	while (**str >= '0' && **str <= '9')
	{
		if ((ret * 10 + (**str - '0')) / 10 != ret)
			xput_error("atoi");
		ret = ret * 10 + (**str - '0');
		++*str;
	}
	if (**str != end)
		xput_error("atoi");
	++*str;
	return (ret);
}

unsigned int	get_color(char *line, char identifier)
{
	unsigned char	red;
	unsigned char	grean;
	unsigned char	blue;
	char			**splited;
	char			*head;

	splited = ft_split(line, ' ');
	if (!*splited || splited[0][0] != identifier || \
		ft_strlen(splited[0]) != 1 || \
		!splited[1] || splited[2])
	{
		xput_error("get color");
	}
	head = splited[1];
	red = cub_atoi(&splited[1], ',');
	grean = cub_atoi(&splited[1], ',');
	blue = cub_atoi(&splited[1], '\0');
	free(splited[0]);
	free(head);
	free(splited);
	return (red << 16 | grean << 8 | blue);
}

void	init_player_dir(t_cub_file *cub_file)
{
	const size_t	x = cub_file->pos_x;
	const size_t	y = cub_file->pos_y;

	if (cub_file->map[y][x] == 'N')
	{
		cub_file->dir_x = 0;
		cub_file->dir_y = -1;
		cub_file->plane_x = -0.66;
		cub_file->plane_y = 0;
	}
	if (cub_file->map[y][x] == 'S')
	{
		cub_file->dir_x = 0;
		cub_file->dir_y = 1;
		cub_file->plane_x = 0.66;
		cub_file->plane_y = 0;
	}
	if (cub_file->map[y][x] == 'W')
	{
		cub_file->dir_x = -1;
		cub_file->dir_y = 0;
		cub_file->plane_x = 0;
		cub_file->plane_y = 0.66;
	}
	if (cub_file->map[y][x] == 'E')
	{
		cub_file->dir_x = 1;
		cub_file->dir_y = 0;
		cub_file->plane_x = 0;
		cub_file->plane_y = -0.66;
	}
}

void	skip_empty_line(char **file_content, size_t *idx)
{
	while (file_content[*idx] && !*file_content[*idx])
		(*idx)++;
}

void	set_player_pos(char **map, int *player_pos_x, int *player_pos_y)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_pos(map[i][j]))
			{
				*player_pos_x = j;
				*player_pos_y = i;
			}
			j++;
		}
		i++;
	}
}

void	init_cub_file(t_cub_file *cub_file, char **file_content)
{
	size_t	idx;

	idx = 0;
	cub_file->north_wall_path = get_path_to_texture("NO", file_content[idx++]);
	cub_file->south_wall_path = get_path_to_texture("SO", file_content[idx++]);
	cub_file->west_wall_path = get_path_to_texture("WE", file_content[idx++]);
	cub_file->east_wall_path = get_path_to_texture("EA", file_content[idx++]);
	skip_empty_line(file_content, &idx);
	cub_file->sky_color = get_color(file_content[idx++], 'F');
	cub_file->ground_color = get_color(file_content[idx++], 'C');
	skip_empty_line(file_content, &idx);
	cub_file->map = duplicate_map(&file_content[idx]);
	set_player_pos(cub_file->map, &cub_file->pos_x, &cub_file->pos_y);
	validate_map(cub_file->map, cub_file->pos_x, cub_file->pos_y);
	init_player_dir(cub_file);
	cub_file->map[cub_file->pos_y][cub_file->pos_x] = '0';
}
