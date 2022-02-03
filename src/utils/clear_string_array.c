/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_string_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:42 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:42 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	clear_string_array(char **arr)
{
	size_t	idx;

	idx = 0;
	while (arr && arr[idx])
		free(arr[idx++]);
	free(arr);
}
