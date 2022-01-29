#include "utils.h"

char	*get_path_to_texture(char *direction, char *line)
{
	char	**splited;
	char	*ret;

	if (!line)
		xput_error("invalid path to texture");
	splited = ft_split(line, ' ');
	if (!splited || !*splited || \
		ft_strncmp(*splited, direction, 3) || \
		!splited[1] || splited[2])
	{
		xput_error("invalid path to texture");
	}
	ret = ft_strdup(splited[1]);
	clear_string_array(splited);
	return (ret);
}
