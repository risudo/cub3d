/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cubfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:15 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/07 21:28:37 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"
#include "utils.h"

void	init_cub_file(t_cub_file *cub_file, char **file_content)
{
	size_t	idx;

	idx = 0;
	cub_file->north_wall_path = get_path_to_texture("NO", file_content[idx++]);
	cub_file->south_wall_path = get_path_to_texture("SO", file_content[idx++]);
	cub_file->west_wall_path = get_path_to_texture("WE", file_content[idx++]);
	cub_file->east_wall_path = get_path_to_texture("EA", file_content[idx++]);
	skip_empty_line(file_content, &idx);
	cub_file->floor_color = get_color(file_content[idx++], 'F');
	cub_file->ceiling_color = get_color(file_content[idx++], 'C');
	skip_empty_line(file_content, &idx);
	cub_file->map = duplicate_map(&file_content[idx]);
	init_player(cub_file);
	validate_map(cub_file->map, cub_file->pos_x, cub_file->pos_y);
}
