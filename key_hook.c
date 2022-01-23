#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>

void move_player(t_game *game, int x, int y) {
    game->posX += x * MOVE_SPEED;
    game->posY += y * MOVE_SPEED;
}

void rotate_player(t_game *game, double angle) {
	double dirX;
	double dirY;

	dirX = game->dirX * cos(angle) - game->dirY * sin(angle);
	dirY = game->dirX * sin(angle) + game->dirY * cos(angle);
	game->dirX = dirX;
	game->dirY = dirY;
}

int destroy_and_exit(void *a) {
    exit(1);
    return (0);
}
int key_hook(int key_code, t_game *game) {
    if (key_code == KEY_W)
        move_player(game, 0, -1);
    if (key_code == KEY_A)
        move_player(game, -1, 0);
    if (key_code == KEY_S)
        move_player(game, 0, 1);
    if (key_code == KEY_D)
        move_player(game, 1, 0);
    if (key_code == KEY_LEFT)
        rotate_player(game, PI / 50);
    if (key_code == KEY_RIGHT)
        rotate_player(game, -PI / 50);
    if (key_code == KEY_ESC)
        destroy_and_exit(game);
	draw_screen(game);
    return (0);
}
