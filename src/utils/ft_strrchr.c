#include "utils.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;

	ret = NULL;
	while (*s)
	{
		if (*s == c)
			ret = (char *)s;
		++s;
	}
	if (*s == c)
		ret = (char *)s;
	return (ret);
}
