/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:16 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:31 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"
#include "utils.h"

void	init_player(t_cub_file *cub_file)
{
	if (!*cub_file->map)
		xput_error("map");
	init_player_pos(cub_file);
	init_player_dir(cub_file);
}
