#include "utils.h"
#include "mlx.h"

void	*mlx_xnew_image(void *mlx_ptr, int width, int height)
{
	void	*ret;

	ret = mlx_new_image(mlx_ptr, width, height);
	if (!ret)
	{
		xput_error("mlx_new_image");
	}
	return (ret);
}
