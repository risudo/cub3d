/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_empty_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:18 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:33 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	skip_empty_line(char **file_content, size_t *idx)
{
	while (file_content[*idx] && !*file_content[*idx])
		(*idx)++;
}
