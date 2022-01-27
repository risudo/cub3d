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
