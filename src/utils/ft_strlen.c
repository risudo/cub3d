/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:44 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:44 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubfile.h"
#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	size_t	ret;

	ret = 0;
	while (str[ret])
		++ret;
	return (ret);
}
