//
// Created by 横田尚紀 on 2022/01/19.
//

#ifndef CUB3D_CUB3D_H
#define CUB3D_CUB3D_H
#define WALL '1'
#include <math.h>

typedef struct s_img {
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_img;

typedef struct s_game {
    void *mlx;
    void *win;
    t_img img;
    int screenWidth;
    int screenHeight;
    int mapWidth;
    int mapHeight;
    // char **map;
	// int **map;
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;
	int color;
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
} t_ray;

int key_hook(int key_code, t_game *game);
int destroy_and_exit(void *a);
void draw_screen(t_game *game);
#endif //CUB3D_CUB3D_H
