#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "utils.h"

char	**read_file_rec(int fd, size_t idx)
{
	char	**ret;
	char	*line;
	int		is_end;

	ret = NULL;
	is_end = get_next_line(fd, &line);
	if (is_end == GNL_ERROR)
		xput_error(strerror(errno));
	else if (is_end == GNL_EOF)
	{
		ret = xmalloc(sizeof(*ret) * (idx + 2));
		ret[idx] = line;
		ret[idx + 1] = NULL;
		return (ret);
	}
	else
		ret = read_file_rec(fd, idx + 1);
	ret[idx] = line;
	return (ret);
}

char	**read_file(char *filepath)
{
	int		fd;
	char	**file_content;

	fd = open(filepath, O_RDONLY);
	file_content = read_file_rec(fd, 0);
	close(fd);
	return (file_content);
}
