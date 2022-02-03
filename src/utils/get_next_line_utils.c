/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsudo <rsudo@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:34:46 by rsudo             #+#    #+#             */
/*   Updated: 2022/02/03 17:34:46 by rsudo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

ssize_t	count_valid_len(const char *str, ssize_t len)
{
	ssize_t	cnt;

	cnt = 0;
	while (cnt < len && *str)
	{
		if (str[cnt] == '\n')
			return (cnt);
		cnt++;
	}
	return (cnt);
}

char	*copy_free(char *dst, char *src, ssize_t len, ssize_t idx)
{
	ssize_t	i;

	i = 0;
	while (i < len && dst && src)
	{
		dst[i + idx] = src[i];
		i++;
	}
	if (!src)
	{
		free(dst);
		dst = NULL;
	}
	free(src);
	src = NULL;
	return (dst);
}

char	*allocate_line(ssize_t len)
{
	char	*ret;

	ret = (char *)malloc((len + 1) * sizeof(char));
	if (ret)
		ret[len] = '\0';
	return (ret);
}

void	is_end(t_gnl *gnl)
{
	ssize_t	len;

	if (gnl->flag == 2 || gnl->offset == 0)
		len = gnl->read_len;
	else
		len = gnl->read_len - (gnl->ptr - gnl->read_str);
	gnl->valid_len = count_valid_len(gnl->ptr, len);
	if (len < 0)
		gnl->flag = GNL_ERROR;
	else if (len == 0)
		gnl->flag = GNL_EOF;
	else if (gnl->valid_len < len)
		gnl->flag = GNL_CONTINUE;
	else
		gnl->flag = 2;
}

char	*ft_strndup(char *src, ssize_t len)
{
	char	*ret;
	ssize_t	i;

	ret = (char *)malloc(len * sizeof(char));
	i = 0;
	while (i < len && ret)
	{
		ret[i] = src[i];
		i++;
	}
	return (ret);
}
