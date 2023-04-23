#include "MLX42.h"

#define WIDTH 1600
#define HEIGHT 800

int main(void)
{
    mlx_t* mlx = mlx_init(WIDTH,HEIGHT,"Algo",false);
    mlx_image_t* img = mlx_new_image(mlx, WIDTH, HEIGHT);

    mlx_loop(mlx);
    return 0;
}
