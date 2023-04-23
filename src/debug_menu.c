#include "generic.h"

void set_img_color(mlx_image_t* img,int32_t color)
{
    uint8_t* pixelarr = img->pixels;

    size_t pxl_size = img->height * img->width * 4;
    for (size_t i = 0; i < pxl_size; i++)
    {
        pixelarr[i++] = (uint8_t)(color >> 24);
	    pixelarr[i++] = (uint8_t)(color >> 16);
	    pixelarr[i++] = (uint8_t)(color >> 8);
	    pixelarr[i] = (uint8_t)(color & 0xFF);
    }
}

debug_t* setup_debug_menu(mlx_t* mlx)
{
    debug_t* dbg = malloc(sizeof(debug_t));
    dbg->backdrop =  mlx_new_image(mlx, DBG_WIDTH, HEIGHT);
    set_img_color(dbg->backdrop, DBG_IMG_COLOR);
    mlx_image_to_window(mlx, dbg->backdrop, WIDTH - DBG_WIDTH, 0);
    return dbg;
}
