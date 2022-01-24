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

void move_player(t_game *game, int angle) {
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

int key_hook(int key_code, t_game *game) {
  if (key_code == KEY_W)
    move_player(game, PI);
  if (key_code == KEY_A)
    move_player(game, -PI / 2);
  if (key_code == KEY_S)
    move_player(game, 0);
  if (key_code == KEY_D)
    move_player(game, PI / 2);
  if (key_code == KEY_LEFT)
    rotate_player(game, ROTATE_SPEED);
  if (key_code == KEY_RIGHT)
    rotate_player(game, -ROTATE_SPEED);
  if (key_code == KEY_ESC)
    destroy_and_exit(game);
  draw_screen(game);
  return (0);
}