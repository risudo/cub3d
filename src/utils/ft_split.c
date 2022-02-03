/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:43 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:43 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static char	*substr(char *start, char *end)
{
	char	*ret;
	size_t	idx;

	ret = xmalloc(sizeof(*ret) * (end - start + 1));
	idx = 0;
	while (start != end)
		ret[idx++] = *start++;
	ret[idx] = '\0';
	return (ret);
}

static char	**rec_split(char *str, const char c, size_t idx)
{
	char	**ret;
	char	*ptr;

	while (*str && *str == c)
		++str;
	if (!*str)
	{
		ret = xmalloc(sizeof(*ret) * (idx + 1));
		ret[idx] = NULL;
		return (ret);
	}
	ptr = (char *)str;
	while (*str && *str != c)
		++str;
	ptr = substr(ptr, str);
	ret = rec_split(str, c, idx + 1);
	ret[idx] = ptr;
	return (ret);
}

char	**ft_split(char *s, char c)
{
	if (!s)
		return (NULL);
	return (rec_split((char *)s, c, 0));
}
