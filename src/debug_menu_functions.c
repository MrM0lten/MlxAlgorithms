#include "generic.h"


void enable_floodfill(void *param)
{
    prog_t* p = param;

    if(p->dbg_menu->flags->b_ff == true)
    {
        printf("disabled ff\n");
        mlx_set_cursor(p->mlx,NULL);
        p->dbg_menu->flags->b_ff = 0;
    }
    else
    {
        printf("enabled ff\n");
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
        if(mouse_on_canvas(x,y) && get_pixel_color(p->img,x,y) != flags->ff_col)
        {
            printf("executing flood fill\n");
            lin_flood_fill(p->img,x,y,flags->ff_col,get_pixel_color(p->img,x,y));
        }

    }

}

void randomize_ff_col(void *param)
{
    prog_t* p = param;
    flag_t* flags = p->dbg_menu->flags;

    printf("Old Color = %d\n", flags->ff_col);
    srand(time(NULL));
    uint32_t col = 0;
    int rshift = 24;
    for (int i = 0; i < 3; i++)
    {
        int r = rand() % 255;
        col |= r << rshift;
        rshift -= 8;
    }
    col |= 255; //setting the alpha to always be 255

    t_btn_list* lst = (t_btn_list*)p->btn_data->buttons;
    printf("1\n");
    printf("1\n");
    printf("1\n");
    button_t* b = (button_t*)lst->content;
    printf("button pos[%d][%d]\n",b->world_posx,b->world_posy);
    //dirty cast, only works because texture and image have the same named vars!
    //lin_flood_fill((mlx_image_t*)b->textures->tex_hlight,1, 1, col, flags->ff_col);
    //lin_flood_fill((mlx_image_t*)b->textures->tex_def,3, 3, col, get_pixel_color((mlx_image_t*)b->textures->tex_def,4,4));
    //lin_flood_fill((mlx_image_t*)b->textures->tex_pressed,1, 1, col, get_pixel_color((mlx_image_t*)b->textures->tex_pressed,1,1));
    set_text_color(b->textures->tex_hlight, col);
    set_text_color(b->textures->tex_def, col);
    set_text_color(b->textures->tex_pressed, col);
    printf("1\n");
    flags->ff_col = col;
    printf("New Color = %d\n", col);
}
