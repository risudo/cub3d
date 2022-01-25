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
	if (*splited && !ft_strncmp(*splited, direction, 3) && splited[1] &&
		!splited[2])
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

	*is_error = false;
	if (*line != identifier)
		return ((unsigned int)(*is_error = true));
	line += 2;
	red = cub_atoi(&line, ',', is_error);
	if (*is_error)
		return ((unsigned int)*is_error);
	grean = cub_atoi(&line, ',', is_error);
	if (*is_error)
		return ((unsigned int)*is_error);
	blue = cub_atoi(&line, '\0', is_error);
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



bool	init_cub_file(t_cub_file *cub_file, char **file_content)
{
	size_t	idx;
	bool	is_error;
	char	*wall_paths[4] = {
		cub_file->north_wall_path,
		cub_file->south_wall_path,
		cub_file->western_wall_path,
		cub_file->east_wall_path,
	};
;

	*cub_file = (t_cub_file){};
	idx = 0;
	cub_file->north_wall_path = get_path_to_texture("NO", file_content[idx++]);
	if (!cub_file->north_wall_path) {
		clear_cub_file(cub_file);
		printf("error!!\n");
		return (true);
	}
	cub_file->south_wall_path = get_path_to_texture("SO", file_content[idx++]);
	if (!cub_file->north_wall_path) {
		clear_cub_file(cub_file);
		printf("error!!\n");
		return (true);
	}
	cub_file->western_wall_path =
		get_path_to_texture("WE", file_content[idx++]);
	if (!cub_file->north_wall_path) {
		clear_cub_file(cub_file);
		printf("error!!\n");
		return (true);
	}
	cub_file->east_wall_path = get_path_to_texture("EA", file_content[idx++]);
	if (!cub_file->north_wall_path) {
		clear_cub_file(cub_file);
		printf("error!!\n");
		return (true);
	}
	while (file_content[idx] && !*file_content[idx])
		idx++;

	cub_file->sky_color = get_color(file_content[idx++], 'F', &is_error);
	if (is_error) {
		clear_cub_file(cub_file);
		printf("error!!\n");
		return (true);
	}
	cub_file->ground_color = get_color(file_content[idx++], 'C', &is_error);
	if (is_error) {
		clear_cub_file(cub_file);
		printf("error!!\n");
		return (true);
	}

	while (file_content[idx] && !*file_content[idx])
		idx++;
	cub_file->map = &file_content[idx];
	init_player(cub_file);
	/* validate_map(); */
	return (false);
}
