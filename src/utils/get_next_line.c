#include "utils.h"

char	*rec_gnl(ssize_t i, t_gnl *gnl, int fd)
{
	char	*str;
	ssize_t	len;

	if (!(i == 0 && gnl->offset > 0))
	{
		gnl->read_len = read(fd, gnl->read_str, GNL_BUFFER_SIZE);
		if (gnl->read_len)
			gnl->ptr = gnl->read_str;
	}
	is_end(gnl);
	len = gnl->valid_len;
	str = ft_strndup(gnl->ptr, len);
	if (gnl->flag == GNL_ERROR)
		return (copy_free(NULL, str, len, i));
	else if (gnl->flag == GNL_EOF || gnl->flag == GNL_CONTINUE)
		return (copy_free(allocate_line(i + len), str, len, i));
	return (copy_free(rec_gnl(i + len, gnl, fd), str, len, i));
}

void	put_away_line(t_gnl *gnl)
{
	gnl->offset = count_valid_len(gnl->ptr, gnl->read_len) + 1;
	gnl->ptr = gnl->ptr + gnl->offset;
	if (gnl->ptr - gnl->read_str == gnl->read_len)
		gnl->offset = 0;
	gnl->times = 1;
	if ((gnl->flag == 0 || gnl->flag == -1) && gnl->times != 2)
	{
		free(gnl->read_str);
		gnl->read_str = NULL;
		gnl->times = 2;
	}
}

int	get_next_line(int fd, char **line)
{
	static t_gnl	gnl;

	if (fd < 0 || !line || GNL_BUFFER_SIZE <= 0)
		return (-1);
	if (!gnl.times)
	{
		gnl.read_str = (char *)malloc(GNL_BUFFER_SIZE * sizeof(char));
		if (!gnl.read_str)
			return (-1);
	}
	if (gnl.times == 2)
	{
		*line = allocate_line(0);
		return (0);
	}
	*line = rec_gnl(0, &gnl, fd);
	put_away_line(&gnl);
	return (gnl.flag);
}
