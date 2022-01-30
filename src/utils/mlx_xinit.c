#include "utils.h"
#include "mlx.h"

void	*mlx_xinit(void)
{
	void	*ret;

	ret = mlx_init();
	if (!ret)
	{
		xput_error("mlx_init");
	}
	return (ret);
}
