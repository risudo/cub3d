#include "../../include/cubfile.h"
#include "../../include/utils.h"

char **read_file(int fd, size_t idx)
{
	char	**ret;
	char	*line;
	int		is_end;

	is_end = get_next_line(fd, &line);
	if (is_end == GNL_ERROR)
	{
		printf("error\n");
		exit(1);
	}
	else if (is_end == GNL_EOF)
	{
		ret = xmalloc(sizeof(*ret) * (idx + 2));
		ret[idx] = line;
		ret[idx + 1] = NULL;
		return (ret);
	}
	else
		ret = read_file(fd, idx + 1);
	ret[idx] = line;
	return (ret);
}

