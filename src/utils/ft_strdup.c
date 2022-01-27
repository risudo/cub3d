#include "utils.h"

char	*ft_strdup(const char *str)
{
	char	*ret;
	size_t	idx;

	ret = xmalloc(ft_strlen(str) + 1);
	idx = 0;
	while (*str)
		ret[idx++] = *str++;
	ret[idx] = '\0';
	return (ret);
}
