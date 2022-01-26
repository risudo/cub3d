#include "cub3d.h"
#include "mlx.h"
#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  t_game game;
  t_cub_file cub_file;
  char **file_content;

  file_content = read_file("./cubfiles/example.cub");
  init_cub_file(&cub_file, file_content);
  init_game(&game, &cub_file);
  init_textures(&game, &cub_file);
  mlx_hook(game.win, KEY_PRESS, KEY_PRESS_MASK, key_press_hook, &game);
  mlx_hook(game.win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_hook, &game);
  mlx_hook(game.win, 33, 1L << 17, destroy_and_exit, &game);
  mlx_loop_hook(game.mlx, game_loop, &game);
  mlx_loop(game.mlx);
}
