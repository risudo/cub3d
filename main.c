#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "mlx.h"

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

typedef struct s_img {
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
} t_img;

int destroy_and_exit(void *a) {
    exit(1);
    return (0);
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color) {
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

int main(void) {
    void *mlx;
    void *mlx_win;
    t_img img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, screenWidth, screenHeight, "cub3d");
    img.img = mlx_new_image(mlx, screenWidth, screenHeight);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    double posX = 22, posY = 12;  // x and y start position
    double dirX = -1, dirY = 0;   // initial direction vector
    double planeX = 0,
            planeY = 0.66;  // the 2d raycaster version of camera plane


    while (1) {
        int w = screenWidth;
        for (int x = 0; x < w; x++) {
            // calculate ray position and direction
            double cameraX =
                    2 * x / (double)w - 1;  // x-coordinate in camera space
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            // which box of the map we're in
            int mapX = (int)posX;
            int mapY = (int)posY;

            // length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;

            // length of ray from one x or y-side to next x or y-side
            // these are derived as:
            // deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
            // deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
            // which can be simplified to abs(|rayDir| / rayDirX) and
            // abs(|rayDir| / rayDirY) where |rayDir| is the length of the
            // vector (rayDirX, rayDirY). Its length, unlike (dirX, dirY) is not
            // 1, however this does not matter, only the ratio between
            // deltaDistX and deltaDistY matters, due to the way the DDA
            // stepping further below works. So the values can be computed as
            // below.
            //  Division through zero is prevented, even though technically
            //  that's not needed in C++ with IEEE 754 floating point values.
            double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

            double perpWallDist;

            // what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            int hit = 0;  // was there a wall hit?
            int side;     // was a NS or a EW wall hit?
            // calculate step and initial sideDist
            if (rayDirX < 0) {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            } else {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if (rayDirY < 0) {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            } else {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }
            // perform DDA
            while (hit == 0) {
                // jump to next map square, either in x-direction, or in
                // y-direction
                if (sideDistX < sideDistY) {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                } else {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                // Check if ray has hit a wall
                if (worldMap[mapX][mapY] > 0)
                    hit = 1;
            }
            // Calculate distance projected on camera direction. This is the
            // shortest distance from the point where the wall is hit to the
            // camera plane. Euclidean to center camera point would give fisheye
            // effect! This can be computed as (mapX - posX + (1 - stepX) / 2) /
            // rayDirX for side == 0, or same formula with Y for size == 1, but
            // can be simplified to the code below thanks to how sideDist and
            // deltaDist are computed: because they were left scaled to
            // |rayDir|. sideDist is the entire length of the ray above after
            // the multiple steps, but we subtract deltaDist once because one
            // step more into the wall was taken above.
            if (side == 0)
                perpWallDist = (sideDistX - deltaDistX);
            else
                perpWallDist = (sideDistY - deltaDistY);

            // Calculate height of line to draw on screen
            double h = screenHeight;
            int lineHeight = (int)(h / perpWallDist);

            // calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2.0 + h / 2;
            if (drawStart < 0)
                drawStart = 0;
            int drawEnd = lineHeight / 2.0 + h / 2;
            if (drawEnd >= h)
                drawEnd = h - 1;

            /* printf("drawStart: %d\n", drawStart); */
            /* printf("drawEnd: %d\n", drawEnd); */
            for (int i = 0; i <= screenHeight; i++) {
                if (i < screenHeight / 2) {
                    my_mlx_pixel_put(&img, x, i, 0x0087cefa);
                } else {
                    my_mlx_pixel_put(&img, x, i, 0x00808080);
                }
                if (i > drawStart && i <= drawEnd) {
                    my_mlx_pixel_put(&img, x, i, 0x00FF0000);
                }
            }
            mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
        }
    }

    mlx_hook(mlx_win, 33, 1L << 17, destroy_and_exit, NULL);
    mlx_loop(mlx);
}
