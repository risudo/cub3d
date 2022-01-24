#ifndef CUB3D_H
#define CUB3D_H

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307
#define PI 3.1415
#define MOVE_SPEED 0.2
#define ROTATE_SPEED (PI / 60)
#include <math.h>

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
  t_img tex_n;
  int screenWidth;
  int screenHeight;
  unsigned int sky_color;
  unsigned int ground_color;
  double posX;
  double posY;
  double dirX;
  double dirY;
  double planeX;
  double planeY;
  int pitch;
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
} t_tex;

int key_hook(int key_code, t_game *game);
int destroy_and_exit(void *a);
int draw_screen(t_game *game);

#endif //CUB3D_H

