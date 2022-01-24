#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void rotate_player(t_game *game, double angle) {

  double oldDirX;
  double oldPlaneX;

  oldDirX = game->dirX;
  game->dirX = game->dirX * cos(angle) - game->dirY * sin(angle);
  game->dirY = oldDirX * sin(angle) + game->dirY * cos(angle);
  oldPlaneX = game->planeX;
  game->planeX = game->planeX * cos(angle) - game->planeY * sin(angle);
  game->planeY = oldPlaneX * sin(angle) + game->planeY * cos(angle);
}

void move_player(t_game *game, double angle) {
  rotate_player(game, angle);
//   if (map[(int)(game->posX - game->dirX * MOVE_SPEED)][(int)game->posY] == '0')
    game->posX -= game->dirX * MOVE_SPEED;
//   if (map[(int)game->posX][(int)(game->posY - game->dirY * MOVE_SPEED)] == '0')
    game->posY -= game->dirY * MOVE_SPEED;
  rotate_player(game, -angle);
}

int destroy_and_exit(void *a) {
  exit(1);
  return (0);
}

int key_press_hook(int key_code, t_game *game) {
    if (key_code == KEY_W)
        game->move_dir = M_PI;
    if (key_code == KEY_A)
        game->move_dir = -M_PI_2;
    if (key_code == KEY_S)
        game->move_dir = 0.0;
    if (key_code == KEY_D)
        game->move_dir = M_PI_2;
    if (key_code == KEY_LEFT)
        game->move_dir = ROTATE_SPEED;
    if (key_code == KEY_RIGHT)
        game->move_dir = -ROTATE_SPEED;
    if (key_code == KEY_ESC)
        destroy_and_exit(game);
    if (key_code == KEY_W || key_code == KEY_A || key_code == KEY_S ||
        key_code == KEY_D)
        game->is_moving = true;
    if (key_code == KEY_LEFT || key_code == KEY_RIGHT)
        game->is_roteting = true;
    return (0);
}

int key_release_hook(int key_code, t_game *game) {
    if (game->is_moving == true) {
        game->is_moving = false;
    }
    if (game->is_roteting == true) {
        game->is_roteting = false;
    }
    return (0);
}
