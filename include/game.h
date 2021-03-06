/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:39:51 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/07 21:33:12 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdbool.h>
# include <stdint.h>

typedef struct s_cub_file	t_cub_file;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_img		north_wall;
	t_img		south_wall;
	t_img		west_wall;
	t_img		east_wall;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	char		**map;
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	bool		is_moving;
	bool		is_rotating;
	double		move_dir;
}	t_game;

int		key_press_hook(int key_code, t_game *game);
int		key_release_hook(int key_code, t_game *game);
void	init_textures(t_game *game, t_cub_file *cub_file);
void	init_game(t_game *game, t_cub_file *cub_file);
int		game_loop(t_game *game);
int		destroy_and_exit(void *arg);
#endif /* GAME_H */
