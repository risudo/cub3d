#ifndef CUB3D_H
# define CUB3D_H

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
# ifndef M_PI
# define M_PI 3.1415926535
# endif
# define MOVE_SPEED 0.1
# define ROTATE_SPEED (M_PI / 60)
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_PRESS_MASK (1L << 0)
# define KEY_RELEASE_MASK (1L << 1)
# include <math.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdint.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
} t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		screen;
	t_img		texture_n;
	t_img		texture_s;
	t_img		texture_w;
	t_img		texture_e;
	int			screenWidth;
	int			screenHeight;
	uint32_t	sky_color;
	uint32_t	ground_color;
	char		**map;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	int			pitch;
	bool		is_moving;
	bool		is_roteting;
	double		move_dir;
}t_game;

typedef struct s_ray
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
}t_ray;

typedef struct s_texture
{
	t_img *wall;
	double wallX;
	double step;
	int textureX;
	int textureY;
	double texturePos;
}t_texture;

typedef struct cub_file
{
	char *north_wall_path;
	char *south_wall_path;
	char *western_wall_path;
	char *east_wall_path;
	unsigned int sky_color;
	unsigned int ground_color;
	char **map;
	int posX;
	int posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
}t_cub_file;

int			draw_screen(t_game *game);
void		init_ray(t_game *game, t_ray *ray, int x);
uint32_t	get_pixel_color(t_img *img, int x, int y);
void		set_pixel_color(t_img *img, int x, int y, int color);
void		dda(t_game *game, t_ray *ray);
void		calc_wall_height(t_game *game, t_ray *ray);
void		set_wall(t_game *game, t_ray *ray, t_texture *texture);
void		calc_coordinates_of_wall(t_game *game, t_ray *ray, t_texture *texture);
void		draw_line(t_game *game, t_ray *ray, t_texture *texture, int x);


int			key_press_hook(int key_code, t_game *game);
int			key_release_hook(int key_code, t_game *game);
void		init_textures(t_game *game, t_cub_file *cub_file);
void		init_game(t_game *game, t_cub_file *cub_file);
int			game_loop(t_game *game);
int			destroy_and_exit(void *arg);

bool		init_cub_file(t_cub_file *cub_file, char **file_content);
char		**read_file(char *filepath);

#endif /* CUB3D_H */
