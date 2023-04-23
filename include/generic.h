#ifndef GENERIC_H
#define GENERIC_H

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "MLX42.h"
#include "mlx_button.h"

#define WIDTH 1600
#define HEIGHT 800
#define DBG_WIDTH 400
#define DBG_IMG_COLOR 0x202020FF
#define MAIN_IMG_COLOR 0xFFFFFFFF

typedef struct debug_s
{
    mlx_image_t* backdrop;
    t_list* btn_lst;

} debug_t;

typedef struct prog_s
{
    mlx_t* mlx;
    mlx_image_t* img;
    debug_t* dbg_menu;

} prog_t;

debug_t* setup_debug_menu(mlx_t* mlx);
void set_img_color(mlx_image_t* img,int32_t color);

#endif
