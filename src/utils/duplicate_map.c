#include "utils.h"

static size_t	count_map_row(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		i++;
	}
	return (i);
}

char	**duplicate_map(char **map)
{
	char	**copy;
	size_t	i;

	i = 0;
	copy = (char **)xmalloc((sizeof(char *)) * (count_map_row(map) + 1));
	while (map[i])
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
