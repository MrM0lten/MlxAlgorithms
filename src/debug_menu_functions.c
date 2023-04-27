#include "generic.h"


void enable_floodfill(void *param)
{
    prog_t* p = param;

    if(p->dbg_menu->flags->b_ff)
    {
        mlx_set_cursor(p->mlx,NULL);
        p->dbg_menu->flags->b_ff = 0;
    }
    else
    {

        mlx_set_cursor(p->mlx,mlx_create_std_cursor(MLX_CURSOR_CROSSHAIR));
        p->dbg_menu->flags->b_ff = 1;
    }
    printf("wow\n");
}

void clear_canvas(void *param)
{
    prog_t* p = param;

    set_img_color(p->img,MAIN_IMG_COLOR);
    printf("cleared Canvas\n");
}

uint32_t get_pixel_color(mlx_image_t* img,int x,int y)
{
    long int arr_pos = (y *img->width +x) * 4;

    uint32_t color = 0;

    color |= (uint32_t)img->pixels[arr_pos++] << 24;
    color |= (uint32_t)img->pixels[arr_pos++] << 16;
    color |= (uint32_t)img->pixels[arr_pos++] << 8;
    color |= (uint32_t)img->pixels[arr_pos];

    return color;
    //fill me
}

void flood_fill(mlx_image_t* img,int x, int y, uint32_t color)
{
    if(x <= 0 + 300 || x >= DFT_CANV_WIDTH-300 || y <= 0 + 300 || y >= HEIGHT -300)
        return;
    if(get_pixel_color(img,x,y) == color)//pixel at that position is already of that color
        return;

    mlx_put_pixel(img,x,y,color);

    flood_fill(img, x , y -1 ,color);
    flood_fill(img, x , y + 1,color);
    flood_fill(img, x -1, y,color);
    flood_fill(img, x +1, y,color);

}

int mouse_on_canvas(int x, int y)
{
    if(x <= 0 || x >= DFT_CANV_WIDTH || y <= 0 || y >= HEIGHT)
        return 0;
    return 1;
}

void exec_flood_fill(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
    prog_t* p = param;
    flag_t* flags = p->dbg_menu->flags;
    if(button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS && flags->b_ff)
    {
        int x;
        int y;
        mlx_get_mouse_pos(p->mlx,&x,&y);
        printf("in exec flood fill %d,%d\n",x,y);
        if(mouse_on_canvas(x,y))
        {
            printf("executing flood fill\n");
            flood_fill(p->img,x,y,0x404040FF);
        }

    }

}
