/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:35:14 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/04 18:59:53 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "mlx.h"
#include "define.h"
#include "cubfile.h"
#include "game.h"

static void	check_arg(int argc, char **argv)
{
	char	*suffix;

	if (argc != 2)
		xput_error("invalid argument");
	suffix = ft_strrchr(argv[1], '.');
	if (!suffix || ft_strncmp(suffix, ".cub", 5))
		xput_error("invalid file name");
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
	mlx_hook(game->win, CLIENT_MESSAGE, \
			STRUCTURE_NOTIFY_MASK, destroy_and_exit, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game		game;

	check_arg(argc, argv);
	init(&game, argv[1]);
	start_game(&game);
}
