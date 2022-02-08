/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubfile.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:39:49 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/07 21:28:21 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBFILE_H
# define CUBFILE_H
# include <stdbool.h>
# include <stdio.h>
# include <stdint.h>

typedef struct s_cub_file {
	char		*north_wall_path;
	char		*south_wall_path;
	char		*west_wall_path;
	char		*east_wall_path;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	char		**map;
	int			pos_x;
	int			pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}	t_cub_file;

typedef struct s_dir
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_dir;

char		**read_file(char *filepath);
void		init_cub_file(t_cub_file *cub_file, char **file_content);
int			validate_map(char **map, int player_pos_x, int player_pos_y);
char		*get_path_to_texture(char *direction, char *line);
uint32_t	get_color(char *line, char identifier);
void		skip_empty_line(char **file_content, size_t *idx);
void		init_player(t_cub_file *cub_file);
void		init_player_pos(t_cub_file *cub_file);
void		init_player_dir(t_cub_file *cub_file);
void		clear_path_to_texture(t_cub_file *cubfile);
#endif
