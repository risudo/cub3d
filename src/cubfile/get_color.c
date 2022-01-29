#include "utils.h"
#include <stdio.h>
#include <limits.h>

static uint8_t	cub_atoi(char **str, char end)
{
	uint32_t	ret;

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

uint32_t	get_color(char *line, char identifier)
{
	uint8_t	red;
	uint8_t	grean;
	uint8_t	blue;
	char	**splited;
	char	*head;

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
