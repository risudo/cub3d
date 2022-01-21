#define W 119
#define A 97
#define S 115
#define D 100
#define LEFT 65361
#define RIGHT 65363
#define ESC 65307
#define MOVE_SPEED 0.5

void move_player(t_game *game, int x, int y) {
	game->player_posx += x * MOVE_SPEED;
	game->player_posy += y * MOVE_SPEED;
}

void rotate_player(t_game *game, double dir)
{
}

int destroy_and_exit(void *a) {
    exit(1);
    return (0);
}
int key_hook(int key_code, t_game *game) {
    if (key_code == W)
    	move_player(game, 0, -1);
    if (key_code == A)
    	move_player(game, -1, 0);
    if (key_code == S)
    	move_player(game, 0, 1);
    if (key_code == D)
    	move_player(game, 1, 0);
	if (key_code == LEFT)
		rotate_player(game, 1.0);
	if (key_code == RIGHT)
		rotate_player(game, -1.0);
    if (key_code == ESC)
    	destroy_and_exit(game);
    return (0);
}
