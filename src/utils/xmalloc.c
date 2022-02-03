/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:49 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:49 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"
#include <stdlib.h>
#include <stdio.h>

void	*xmalloc(size_t size)
{
	void	*ret;

	ret = malloc(size);
	if (!ret)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (ret);
}
