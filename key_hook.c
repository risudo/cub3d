#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#define W 119
#define A 97
#define S 115
#define D 100
#define LEFT 65361
#define RIGHT 65363
#define ESC 65307
#define MOVE_SPEED 0.2
#define PI 3.1415

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
	printf("key_code: %d\n", key_code);
    if (key_code == W)
        move_player(game, 0, -1);
    if (key_code == A)
        move_player(game, -1, 0);
    if (key_code == S)
        move_player(game, 0, 1);
    if (key_code == D)
        move_player(game, 1, 0);
    if (key_code == LEFT)
        rotate_player(game, PI / 50);
    if (key_code == RIGHT)
        rotate_player(game, -PI / 50);
    if (key_code == ESC)
        destroy_and_exit(game);
	draw_screen(game);
    return (0);
}
