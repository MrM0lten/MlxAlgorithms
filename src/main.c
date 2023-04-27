#include "generic.h"

void end_prog(void *param)
{
	prog_t* prog = param;

	if (mlx_is_key_down(prog->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(prog->mlx);
}

void cleanup(prog_t* prog)
{
    free(prog->dbg_menu);
    free(prog);
}


int main(void)
{
    prog_t* prog = malloc(sizeof(prog_t));
    prog->sizeX = WIDTH;
    prog->sizeY = HEIGHT;
    prog->mlx = mlx_init(WIDTH,HEIGHT,"Algo",false);
    prog->btn_data = mlx_button_init(prog->mlx);
    prog->img = mlx_new_image(prog->mlx, WIDTH - DBG_WIDTH, HEIGHT);
    set_img_color(prog->img, MAIN_IMG_COLOR);
    mlx_image_to_window(prog->mlx, prog->img, 0, 0);
    setup_debug_menu(prog);


    mlx_loop_hook(prog->mlx,end_prog,prog);
    mlx_loop(prog->mlx);
    mlx_button_terminate(prog->btn_data);
    mlx_terminate(prog->mlx);
    cleanup(prog);

    return 0;
}
