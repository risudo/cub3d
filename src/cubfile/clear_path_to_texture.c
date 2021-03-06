/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_path_to_texture.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:33:19 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:30 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"
#include <stdlib.h>

void	clear_path_to_texture(t_cub_file *cubfile)
{
	free(cubfile->north_wall_path);
	free(cubfile->south_wall_path);
	free(cubfile->west_wall_path);
	free(cubfile->east_wall_path);
}
