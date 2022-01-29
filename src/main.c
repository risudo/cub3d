#include "utils.h"
#include "mlx.h"
#include "define.h"
#include "cubfile.h"
#include "game.h"
/*
#include <stdio.h>

void	end(void)__attribute__((destructor));

void	end(void)
{
	pid_t	current_pid;
	char	cmd_str[50];
	int		ret;

	current_pid = getpid();
	sprintf(cmd_str, "%s %d %s\n", "leaks", current_pid, ">> leaks.txt 2>&1");
	ret = system(cmd_str);
	if (ret)
		printf("\e[31m!leak detected!\e[0m\n");
	else
		printf("leaks not found\n");
}
*/

static void	check_arg(int argc)
{
	if (argc != 2)
	{
		xput_error("invalid argument");
	}
}

static void	init(t_game *game, char *file_path)
{
	t_cub_file	cub_file;
	char		**file_content;

	file_content = read_file(file_path);
	init_cub_file(&cub_file, file_content);
	clear_string_array(file_content);
	init_game(game, &cub_file);
	init_textures(game, &cub_file);
	clear_path_to_texture(&cub_file);
}

static void	start_game(t_game *game)
{
	mlx_hook(game->win, KEY_PRESS, KEY_PRESS_MASK, key_press_hook, game);
	mlx_hook(game->win, KEY_RELEASE, KEY_RELEASE_MASK, key_release_hook, game);
	mlx_hook(game->win, 33, 1L << 17, destroy_and_exit, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game		game;

	check_arg(argc);
	init(&game, argv[1]);
	start_game(&game);
}
