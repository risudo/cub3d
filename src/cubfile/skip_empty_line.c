#include <stddef.h>

void	skip_empty_line(char **file_content, size_t *idx)
{
	while (file_content[*idx] && !*file_content[*idx])
		(*idx)++;
}
