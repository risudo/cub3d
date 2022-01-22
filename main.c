#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "cub3d.h"
#include "mlx.h"

int worldMap[24][24] = {
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

char *map[] = {"111111111111111111111111", "100000000000000000000001",
               "100000000000000000000001", "100000000000000000000001",
               "100000222220000303030001", "100000200020000000000001",
               "100000200020000300030001", "100000200020000000000001",
               "100000220220000303030001", "100000000000000000000001",
               "100000000000000000000001", "100000000000000000000001",
               "100000000000000000000001", "100000000000000000000001",
               "100000000000000000000001", "100000000000000000000001",
               "144444444000000000000001", "140400004000000000000001",
               "140000504000000000000001", "140400004000000000000001",
               "140444444000000000000001", "140000000000000000000001",
               "144444444000000000000001", "111111111111111111111111"};

void my_mlx_pixel_put(t_img *img, int x, int y, int color) {
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void init_game(t_game *game) {
    game->screenWidth = 640;
    game->screenHeight = 480;
    game->mapWidth = 24;
    game->mapHeight = 24;
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, game->screenWidth, game->screenHeight,
                               "cub3d");
    game->img.img =
        mlx_new_image(game->mlx, game->screenWidth, game->screenHeight);
    game->img.addr =
        mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
                          &game->img.line_length, &game->img.endian);
    game->posX = 15;
    game->posY = 12;
    game->dirX = -1;
    game->dirY = 0;
    game->planeX = 0;
    game->planeY = 0.66;
}

void init_ray(t_ray *ray, t_game *game, int x) {
    ray->cameraX = 2 * x / (double)game->screenWidth - 1;
    ray->rayDirX = game->dirX + game->planeX * ray->cameraX;
    ray->rayDirY = game->dirY + game->planeY * ray->cameraX;
    ray->mapX = (int)game->posX;
    ray->mapY = (int)game->posY;
    ray->deltaDistX = (ray->rayDirX == 0) ? 1e30 : fabs(1 / ray->rayDirX);
    ray->deltaDistY = (ray->rayDirY == 0) ? 1e30 : fabs(1 / ray->rayDirY);
    if (ray->rayDirX < 0) {
        ray->stepX = -1;
        ray->sideDistX = (game->posX - ray->mapX) * ray->deltaDistX;
    } else {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - game->posX) * ray->deltaDistX;
    }
    if (ray->rayDirY < 0) {
        ray->stepY = -1;
        ray->sideDistY = (game->posY - ray->mapY) * ray->deltaDistY;
    } else {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - game->posY) * ray->deltaDistY;
    }
}

int get_color(char c)
{
	if (c == '1')
		return 0x00FF0000;
	else if (c == '2')
		return 0x00008000;
	else if (c == '3')
		return 0x000000ff;
	else if (c == '4')
		return 0x00ffffff;
	return 0;
}

void dda(t_ray *ray, t_game *game) {
    while (42) {
        if (ray->sideDistX < ray->sideDistY) {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        } else {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }
        if (map[ray->mapX][ray->mapY] > '0')
			break;
    }
	game->color = get_color(map[ray->mapX][ray->mapY]);
    if (ray->side == 0)
        ray->perpWallDist = ray->sideDistX - ray->deltaDistX;
    else
        ray->perpWallDist = ray->sideDistY - ray->deltaDistY;
}

int get_drawStart(const int lineHeight, const int screenHeight,
                  const double perpWallDist) {
    int ret;

    ret = -lineHeight / 2.0 + screenHeight / 2;
    if (ret < 0)
        ret = 0;
    return (ret);
}

int get_drawEnd(const int lineHeight, const int screenHeight,
                const double perpWallDist) {
    int ret;

    ret = lineHeight / 2.0 + screenHeight / 2;
    if (ret >= screenHeight)
        ret = screenHeight - 1;
    return (ret);
}

void draw_line(t_ray *ray, t_game *game, int x) {
    const int lineHeight = (int)(game->screenHeight / ray->perpWallDist);
    const int drawStart =
        get_drawStart(lineHeight, game->screenHeight, ray->perpWallDist);
    const int drawEnd =
        get_drawEnd(lineHeight, game->screenHeight, ray->perpWallDist);
    int height;

    height = 0;
    while (height <= game->screenHeight) {
        if (height < game->screenHeight / 2) {
            my_mlx_pixel_put(&game->img, x, height, 0x0087cefa);
        } else {
            my_mlx_pixel_put(&game->img, x, height, 0x00808080);
        }
        if (height > drawStart && height <= drawEnd) {
			my_mlx_pixel_put(&game->img, x, height, game->color);
        }
        ++height;
    }
}

void draw_screen(t_game *game) {
    int x;
    t_ray ray;

    x = 0;
    while (x < game->screenWidth) {
        init_ray(&ray, game, x);
        dda(&ray, game);
        draw_line(&ray, game, x);
        ++x;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int main(void) {
    t_game game;

    init_game(&game);
    draw_screen(&game);
    printf("key_hook\n");
    mlx_key_hook(game.win, &key_hook, &game);
    mlx_hook(game.win, 33, 1L << 17, destroy_and_exit, NULL);
    mlx_loop(game.mlx);
}

