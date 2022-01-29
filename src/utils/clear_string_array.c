#include <stdlib.h>

void	clear_string_array(char **arr)
{
	size_t	idx;

	idx = 0;
	while (arr && arr[idx])
		free(arr[idx++]);
	free(arr);
}
