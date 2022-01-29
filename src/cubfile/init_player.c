#include "cubfile.h"
#include "utils.h"

void	init_player(t_cub_file *cub_file)
{
	if (!*cub_file->map)
		xput_error("map");
	init_player_pos(cub_file);
	init_player_dir(cub_file);
}
