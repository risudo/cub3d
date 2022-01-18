#include "mlx.h"
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480

int	destroy_and_exit(void *a)
{
	exit(1);
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "cub3d");
	mlx_hook(mlx_win, 33, 1L << 17, destroy_and_exit, NULL);
	mlx_loop(mlx);
}
