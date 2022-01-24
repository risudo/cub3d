#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include <stdlib.h>

void init_game(t_game *game) {
  game->screenWidth = 640;
  game->screenHeight = 480;
  game->mlx = mlx_init();
  game->win =
      mlx_new_window(game->mlx, game->screenWidth, game->screenHeight, "cub3d");
  game->screen.img =
      mlx_new_image(game->mlx, game->screenWidth, game->screenHeight);
  game->screen.addr =
      mlx_get_data_addr(game->screen.img, &game->screen.bits_per_pixel,
                        &game->screen.line_length, &game->screen.endian);
  game->tex_n.img =
      mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm",
                            &game->tex_n.width, &game->tex_n.height);
  game->tex_n.addr =
      mlx_get_data_addr(game->tex_n.img, &game->tex_n.bits_per_pixel,
                        &game->tex_n.line_length, &game->tex_n.endian);
  game->posX = 22.0;
  game->posY = 11.5;
  game->dirX = -1.0;
  game->dirY = 0.0;
  game->planeX = 0.0;
  game->planeY = 0.66;
  game->pitch = 100;
  game->sky_color = 0x0087cefa;
  game->ground_color = 0x00808080;
}

void init_tex(t_game *game) {
  game->tex_n.img =
      mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm",
                            &game->tex_n.width, &game->tex_n.height);
  game->tex_n.addr =
      mlx_get_data_addr(game->tex_n.img, &game->tex_n.bits_per_pixel,
                        &game->tex_n.line_length, &game->tex_n.endian);
}

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

unsigned int get_color_texture(t_img *img, int x, int y) {
  char *dst;

  dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
  return (*(unsigned int *)dst);
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color) {
  char *dst;

  dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
  *(unsigned int *)dst = color;
}

void init_ray(t_game *game, t_ray *ray, int x) {
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

void dda(t_game *game, t_ray *ray) {
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
}

void calc_wall_height(t_game *game, t_ray *ray) {
  if (ray->side == 0)
    ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
  else
    ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
  ray->lineHeight = (int)(game->screenHeight / ray->perpWallDist);
  ray->drawStart = -ray->lineHeight / 2 + game->screenHeight / 2 + game->pitch;
  if (ray->drawStart < 0)
    ray->drawStart = 0;
  ray->drawEnd = ray->lineHeight / 2 + game->screenHeight / 2 + game->pitch;
  if (ray->drawEnd >= game->screenHeight)
    ray->drawEnd = game->screenHeight - 1;
}

void calc_coordinates_of_tex(t_game *game, t_ray *ray, t_tex *tex) {
  if (ray->side == 0)
    tex->wallX = game->posY + ray->perpWallDist * ray->rayDirY;
  else
    tex->wallX = game->posX + ray->perpWallDist * ray->rayDirX;
  tex->wallX -= floor(tex->wallX);
  tex->texX = (int)(tex->wallX * (double)(game->tex_n.width));
  if (ray->side == 0 && ray->rayDirX > 0)
    tex->texX = game->tex_n.width - tex->texX - 1;
  if (ray->side == 1 && ray->rayDirY < 0)
    tex->texX = game->tex_n.width - tex->texX - 1;
  tex->step = 1.0 * game->tex_n.height / ray->lineHeight;
  tex->texPos = (ray->drawStart - game->pitch - game->screenHeight / 2 +
                 ray->lineHeight / 2) *
                tex->step;
}

void draw_line(t_game *game, t_ray *ray, t_tex *tex, int x) {
  unsigned int color;
  int y;
  y = 0;
  while (y < ray->drawStart)
    my_mlx_pixel_put(&game->screen, x, y++, game->sky_color);
  while (y < ray->drawEnd) {
    tex->texY = (int)tex->texPos & (game->tex_n.height - 1);
    tex->texPos += tex->step;
    color = get_color_texture(&game->tex_n, tex->texX, tex->texY);
    if (ray->side == 1)
      color = (color >> 1) & 8355711;
    my_mlx_pixel_put(&game->screen, x, y++, color);
  }
  while (y < game->screenHeight)
    my_mlx_pixel_put(&game->screen, x, y++, game->ground_color);
}

int draw_screen(t_game *game) {
  t_ray ray;
  t_tex tex;
  for (int x = 0; x < game->screenWidth; x++) {
    init_ray(game, &ray, x);
    dda(game, &ray);
    calc_wall_height(game, &ray);
    calc_coordinates_of_tex(game, &ray, &tex);
    draw_line(game, &ray, &tex, x);
  }
  mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
  return (0);
}

int main(void) {
  t_game game;

  init_game(&game);
  init_tex(&game);
  draw_screen(&game);
  mlx_key_hook(game.win, &key_hook, &game);
  mlx_hook(game.win, 33, 1L << 17, destroy_and_exit, NULL);
  mlx_loop(game.mlx);
}
