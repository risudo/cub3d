#include "cub3d.h"
#include "mlx.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void init_game(t_game *game, t_cub_file *cub_file) {
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
  game->posX = cub_file->posX;
  game->posY = cub_file->posY;
  game->dirX = cub_file->dirX;
  game->dirY = cub_file->dirY;
  game->planeX = cub_file->planeX;
  game->planeY = cub_file->planeY;
  game->pitch = 100;
  game->sky_color = cub_file->sky_color;
  game->ground_color = cub_file->ground_color;
  game->is_moving = 0;
  game->is_roteting = 0;
  game->move_dir = 0.0;
  game->map = cub_file->map;
}

void init_tex(t_img *img, void *mlx, char *path) {
  img->img = mlx_xpm_file_to_image(mlx, path, &img->width, &img->height);
  img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
                                &img->line_length, &img->endian);
}

void init_texs(t_game *game, t_cub_file *cub_file) {
  init_tex(&game->tex_n, game->mlx, cub_file->north_wall_path);
  init_tex(&game->tex_s, game->mlx, cub_file->south_wall_path);
  init_tex(&game->tex_w, game->mlx, cub_file->western_wall_path);
  init_tex(&game->tex_e, game->mlx, cub_file->east_wall_path);
}

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
    if (game->map[ray->mapX][ray->mapY] > '0')
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

void set_use(t_game *game, t_ray *ray) {
  if (ray->side == 0) {
    if (ray->rayDirX > 0) {
      game->use = &game->tex_e;
    } else {
      game->use = &game->tex_w;
    }
  } else {
    if (ray->rayDirY > 0) {
      game->use = &game->tex_s;
    } else {
      game->use = &game->tex_n;
    }
  }
}

void calc_coordinates_of_tex(t_game *game, t_ray *ray, t_tex *tex) {
  if (ray->side == 0)
    tex->wallX = game->posY + ray->perpWallDist * ray->rayDirY;
  else
    tex->wallX = game->posX + ray->perpWallDist * ray->rayDirX;
  tex->wallX -= floor(tex->wallX);
  tex->texX = (int)(tex->wallX * (double)(game->use->width));
  if (ray->side == 0 && ray->rayDirX > 0)
    tex->texX = game->use->width - tex->texX - 1;
  if (ray->side == 1 && ray->rayDirY < 0)
    tex->texX = game->use->width - tex->texX - 1;
  tex->step = 1.0 * game->use->height / ray->lineHeight;
  tex->texPos = (ray->drawStart - game->pitch - game->screenHeight / 2.0 +
                 ray->lineHeight / 2.0) *
                tex->step;
}

void draw_line(t_game *game, t_ray *ray, t_tex *tex, int x) {
  unsigned int color;
  int y;
  y = 0;
  while (y < ray->drawStart)
    my_mlx_pixel_put(&game->screen, x, y++, game->sky_color);
  while (y < ray->drawEnd) {
    tex->texY = (int)tex->texPos & (game->use->height - 1);
    tex->texPos += tex->step;
    color = get_color_texture(game->use, tex->texX, tex->texY);
    /* if (ray->side == 1) */
    /*   color = (color >> 1) & 8355711; */
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
    set_use(game, &ray);
    calc_wall_height(game, &ray);
    calc_coordinates_of_tex(game, &ray, &tex);
    draw_line(game, &ray, &tex, x);
  }
  mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
  return (0);
}

void update_player(t_game *game) {
  if (game->is_moving == true) {
    move_player(game, game->move_dir);
  }
  if (game->is_roteting == true) {
    rotate_player(game, game->move_dir);
  }
}

int loop(t_game *game) {
  update_player(game);
  draw_screen(game);
  return (0);
}

int main(void) {
  t_game game;
  t_cub_file cub_file;
  char **file_content;

  int fd = open("example.cub", O_RDONLY);
  file_content = read_file(fd, 0);
  init_cub_file(&cub_file, file_content);
  init_game(&game, &cub_file);
  init_texs(&game, &cub_file);
  mlx_hook(game.win, KEY_PRESS, KEY_PRESS_MASK, key_press_hook, &game);
  mlx_hook(game.win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_hook, &game);
  mlx_hook(game.win, 33, 1L << 17, destroy_and_exit, NULL);
  mlx_loop_hook(game.mlx, loop, &game);
  mlx_loop(game.mlx);
}
