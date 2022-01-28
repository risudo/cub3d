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
	if (!splited)
		xput_error("path to texture");
	if (*splited && !ft_strncmp(*splited, direction, 3)
			&& splited[1] && !splited[2])
		ret = ft_strdup(splited[1]);
	else
		xput_error("path to texture");
	clear_string_array(splited);
	return (ret);
}

void	clear_cub_file(t_cub_file *cub_file)
{
	free(cub_file->north_wall_path);
	free(cub_file->south_wall_path);
	free(cub_file->western_wall_path);
	free(cub_file->east_wall_path);
	clear_string_array(cub_file->map);
}

unsigned char	cub_atoi(char **str, char end, bool *is_error)
{
	unsigned char ret;

	ret = 0;
	while (**str >= '0' && **str <= '9') {
		if ((ret * 10 + (**str - '0')) / 10 != ret)
			return ((unsigned char)(*is_error = true));
		ret = ret * 10 + (**str - '0');
		++*str;
	}
	if (**str != end)
		return ((unsigned char)(*is_error = true));
	++*str;
	return (ret);
}

unsigned int	get_color(char *line, char identifier, bool *is_error)
{
	unsigned char	red;
	unsigned char	grean;
	unsigned char	blue;
	char			**splited;

	splited= ft_split(line, ' ');
	*is_error = false;
	if (!splited[0] || splited[0][0] != identifier || \
		ft_strlen(splited[0]) != 1 || \
		!splited[1] || splited[2])
		xput_error("get color");
	red = cub_atoi(&splited[1], ',', is_error);
	if (*is_error)
		xput_error("get color");
	grean = cub_atoi(&splited[1], ',', is_error);
	if (*is_error)
		xput_error("get color");
	blue = cub_atoi(&splited[1], '\0', is_error);
	if (*is_error)
		xput_error("get color");
//	clear_string_array(splited); //ダブルフリーになるのなんで？？
	return (red << 16 | grean << 8 | blue);
}

void	init_player(t_cub_file *cub_file)
{
	size_t	x;
	size_t	y;

	x = cub_file->pos_x;
	y = cub_file->pos_y;
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
	cub_file->map[y][x] = '0';
}

void	skip_empty_line(char **file_content, size_t *idx)
{
	while (file_content[*idx] && !*file_content[*idx])
		(*idx)++;
}

bool	init_cub_file(t_cub_file *cub_file, char **file_content)
{
	size_t	idx;
	bool	error;

	*cub_file = (t_cub_file){};
	idx = 0;
	cub_file->north_wall_path = get_path_to_texture("NO", file_content[idx++]);
	cub_file->south_wall_path = get_path_to_texture("SO", file_content[idx++]);
	cub_file->western_wall_path = get_path_to_texture("WE", file_content[idx++]);
	cub_file->east_wall_path = get_path_to_texture("EA", file_content[idx++]);
	skip_empty_line(file_content, &idx);
	cub_file->sky_color = get_color(file_content[idx++], 'F', &error);
	cub_file->ground_color = get_color(file_content[idx++], 'C', &error);
	skip_empty_line(file_content, &idx);
	cub_file->map = &file_content[idx];
	validate_map(cub_file->map, &cub_file->pos_x, &cub_file->pos_y);
	init_player(cub_file);
	return (false);
}
