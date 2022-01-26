#include <libc.h>
#include <stdbool.h>

#include "../../include/cubfile.h"
#include "../../include/utils.h"

void	clear_string_array(char **arr)
{
	size_t	idx;

	idx = 0;
	while (arr && arr[idx])
		free(arr[idx++]);
	free(arr);
}

char	*get_path_to_texture(char *direction, char *line)
{
	char	**splited;
	char	*ret;

	if (!line)
		return (NULL);
	splited = ft_split(line, ' ');
	if (!splited)
		return (NULL);
	if (*splited && !ft_strncmp(*splited, direction, 3)
			&& splited[1] && !splited[2])
		ret = ft_strdup(splited[1]);
	else
		ret = NULL;
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
	if (splited[0][0] != identifier || \
		ft_strlen(splited[0]) != 1 || \
		!splited[1] || splited[2])
		return ((unsigned int)(*is_error = true));//
	red = cub_atoi(&splited[1], ',', is_error);
	if (*is_error)
		return ((unsigned int)*is_error);
	grean = cub_atoi(&splited[1], ',', is_error);
	if (*is_error)
		return ((unsigned int)*is_error);
	blue = cub_atoi(&splited[1], '\0', is_error);
	if (*is_error)
		return ((unsigned int)*is_error);
	return (red << 16 | grean << 8 | blue);
}

void	init_player(t_cub_file *cub_file)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (cub_file->map[y]) {
		x = 0;
		while (cub_file->map[y][x]) {
			if (cub_file->map[y][x] == 'N' || cub_file->map[y][x] == 'S' ||
				cub_file->map[y][x] == 'D' || cub_file->map[y][x] == 'E') {
				cub_file->posX = y;
				cub_file->posY = x;
				if (cub_file->map[y][x] == 'N') {
					cub_file->dirX = 0;
					cub_file->dirY = -1;
					cub_file->planeX = -0.66;
					cub_file->planeY = 0;
				}
				if (cub_file->map[y][x] == 'S') {
					cub_file->dirX = 0;
					cub_file->dirY = 1;
					cub_file->planeX = 0.66;
					cub_file->planeY = 0;
				}
				if (cub_file->map[y][x] == 'W') {
					cub_file->dirX = -1;
					cub_file->dirY = 0;
					cub_file->planeX = 0;
					cub_file->planeY = 0.66;
				}
				if (cub_file->map[y][x] == 'E') {
					cub_file->dirX = 1;
					cub_file->dirY = 0;
					cub_file->planeX = 0;
					cub_file->planeY = -0.66;
				}
				break;
			}
			++x;
		}
		if (cub_file->map[y][x])
			break;
		++y;
	}
}

void	check_wall_path(char *wall_path, t_cub_file *cubfile)
{
	if (!wall_path)
	{
		clear_cub_file(cubfile);
		xput_error("check_wall_path");
	}
}

void check_get_color_error(bool error, t_cub_file *cubfile)
{
	if (error)
	{
		clear_cub_file(cubfile);
		xput_error("check_get_color_error");
	}
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
	check_wall_path(cub_file->north_wall_path, cub_file);
	cub_file->south_wall_path = get_path_to_texture("SO", file_content[idx++]);
	check_wall_path(cub_file->south_wall_path, cub_file);
	cub_file->western_wall_path = get_path_to_texture("WE", file_content[idx++]);
	check_wall_path(cub_file->western_wall_path, cub_file);
	cub_file->east_wall_path = get_path_to_texture("EA", file_content[idx++]);
	check_wall_path(cub_file->east_wall_path, cub_file);

	skip_empty_line(file_content, &idx);

	cub_file->sky_color = get_color(file_content[idx++], 'F', &error);
	check_get_color_error(error, cub_file);
	cub_file->ground_color = get_color(file_content[idx++], 'C', &error);
	check_get_color_error(error, cub_file);

	skip_empty_line(file_content, &idx);
	cub_file->map = &file_content[idx];
	init_player(cub_file);
//	validate_map();
	return (false);
}
