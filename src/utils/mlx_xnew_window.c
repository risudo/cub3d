/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xnew_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:48 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:48 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "mlx.h"

void	*mlx_xnew_image(void *mlx_ptr, int width, int height)
{
	void	*ret;

	ret = mlx_new_image(mlx_ptr, width, height);
	if (!ret)
	{
		xput_error("mlx_new_image");
	}
	return (ret);
}
