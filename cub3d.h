#ifndef CUB3D_H
#define CUB3D_H

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307
#ifndef M_PI
#define M_PI 3.1415926535
#endif /* CUB3D_H */
#define MOVE_SPEED 0.1
#define ROTATE_SPEED (M_PI / 60)
#define KEY_PRESS 2
#define KEY_RELEASE 3
#define KEY_PRESS_MASK (1L << 0)
#define KEY_RELEASE_MASK (1L << 1)
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct s_img {
  void *img;
  char *addr;
  int bits_per_pixel;
  int line_length;
  int endian;
  int width;
  int height;
} t_img;

typedef struct s_game {
  void *mlx;
  void *win;
  t_img screen;
  t_img *use;
  t_img tex_n;
  t_img tex_s;
  t_img tex_w;
  t_img tex_e;
  int screenWidth;
  int screenHeight;
  unsigned int sky_color;
  unsigned int ground_color;
  char **map;
  double posX;
  double posY;
  double dirX;
  double dirY;
  double planeX;
  double planeY;
  int pitch;
  bool is_moving;
  bool is_roteting;
  double move_dir;
} t_game;

typedef struct s_ray {
  double cameraX;
  double rayDirX;
  double rayDirY;
  int mapX;
  int mapY;
  double sideDistX;
  double sideDistY;
  double deltaDistX;
  double deltaDistY;
  double perpWallDist;
  int stepX;
  int stepY;
  int side;
  int lineHeight;
  int drawStart;
  int drawEnd;
} t_ray;

typedef struct s_tex {
  double wallX;
  double step;
  int texX;
  int texY;
  double texPos;
  int width;
  int height;
} t_tex;

typedef struct cub_file {
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
} t_cub_file;

int key_hook(int key_code, t_game *game);
int destroy_and_exit(void *a);
int draw_screen(t_game *game);
void move_player(t_game *game, double angle);
void rotate_player(t_game *game, double angle);
int key_press_hook(int key_code, t_game *game);
int key_release_hook(int key_code, t_game *game);

bool init_cub_file(t_cub_file *cub_file, char **file_content);
char **read_file(int fd, size_t idx);

#endif // CUB3D_H
