#include "mlx.h"
#include "utils.h"

void	*mlx_xxpm_file_to_image(void *mlx_ptr, \
			char *filename, int *width, int *height)
{
	void	*ret;

	ret = mlx_xpm_file_to_image(mlx_ptr, filename, width, height);
	if (!ret)
	{
		xput_error("mlx_xpm_file_to_image");
	}
	return (ret);
}
