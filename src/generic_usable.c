#include "generic.h"

//char size:
//X = 10
//Y = 20

int get_txt_midX(char *str)
{
    size_t len = strlen(str);
    return ((int)len*10/2);
}

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

void set_text_color(mlx_texture_t* img,int32_t color)
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
