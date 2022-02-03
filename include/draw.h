/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:39:50 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:39:50 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H
# include <stdint.h>

typedef struct s_game	t_game;
typedef struct s_img	t_img;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_texture
{
	t_img	*wall;
	double	wall_x;
	double	step;
	int		texture_x;
	int		texture_y;
	double	texture_pos;
}	t_texture;

int			draw_screen(t_game *game);
void		init_ray(t_game *game, t_ray *ray, int x);
uint32_t	get_pixel_color(t_img *img, int x, int y);
void		set_pixel_color(t_img *img, int x, int y, int color);
void		dda(t_game *game, t_ray *ray);
void		calc_wall_height(t_game *game, t_ray *ray);
void		set_wall(t_game *game, t_ray *ray, t_texture *texture);
void		calc_coordinates_of_wall(t_game *game, \
				t_ray *ray, t_texture *texture);
void		draw_line(t_game *game, t_ray *ray, t_texture *texture, int x);

#endif /* DRAW_H */
