/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xnew_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:47 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:47 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "mlx.h"

void	*mlx_xnew_window(void *mlx_ptr, int x, int y, char *title)
{
	void	*ret;

	ret = mlx_new_window(mlx_ptr, x, y, title);
	if (!ret)
	{
		xput_error("mlx_new_window");
	}
	return (ret);
}
