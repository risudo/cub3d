#include "cubfile.h"
#include <stdlib.h>

void	clear_path_to_texture(t_cub_file *cubfile)
{
	free(cubfile->north_wall_path);
	free(cubfile->south_wall_path);
	free(cubfile->west_wall_path);
	free(cubfile->east_wall_path);
}
