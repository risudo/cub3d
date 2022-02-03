/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xxpm_file_to_image.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:48 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:48 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "utils.h"

void	*mlx_xxpm_file_to_image(void *mlx_ptr, \
			char *filename, int *width, int *height)
{
	void	*ret;

	ret = mlx_xpm_file_to_image(mlx_ptr, filename, width, height);
	if (!ret)
	{
		xput_error("mlx_xpm_file_to_image");
	}
	return (ret);
}
