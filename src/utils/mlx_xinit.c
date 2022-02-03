/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:47 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:47 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "mlx.h"

void	*mlx_xinit(void)
{
	void	*ret;

	ret = mlx_init();
	if (!ret)
	{
		xput_error("mlx_init");
	}
	return (ret);
}
