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
