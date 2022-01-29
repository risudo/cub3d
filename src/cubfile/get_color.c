#include "utils.h"
#include <stdio.h>
#include <limits.h>

static unsigned char	cub_atoi(char **str, char end)
{
	unsigned int	ret;

	ret = 0;
	while (**str >= '0' && **str <= '9')
	{
		if (ret > UCHAR_MAX)
			xput_error("invalid color code");
		ret = ret * 10 + (**str - '0');
		++*str;
	}
	if (**str != end)
		xput_error("invalid color code");
	++*str;
	return (ret);
}

unsigned int	get_color(char *line, char identifier)
{
	unsigned char	red;
	unsigned char	grean;
	unsigned char	blue;
	char			**splited;
	char			*head;

	splited = ft_split(line, ' ');
	if (!*splited || splited[0][0] != identifier || \
		ft_strlen(splited[0]) != 1 || \
		!splited[1] || splited[2])
	{
		xput_error("invalid color code");
	}
	head = splited[1];
	red = cub_atoi(&splited[1], ',');
	grean = cub_atoi(&splited[1], ',');
	blue = cub_atoi(&splited[1], '\0');
	free(splited[0]);
	free(head);
	free(splited);
	return (red << 16 | grean << 8 | blue);
}
