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
#define DFT_CANV_WIDTH WIDTH-DBG_WIDTH
#define DBG_IMG_COLOR 0x202020FF
#define MAIN_IMG_COLOR 0xFFFFFFFF

#define SQ_BTN_SIZE 30
#define LONG_BTN_SIZE 90

#define DBG_CANV_CENTER_X WIDTH-(DBG_WIDTH/2)

typedef struct flag_s
{
    int b_ff;

} flag_t;

typedef struct debug_s
{
    int posX;
    int posY;
    int sizeX;
    int sizeY;
    mlx_image_t* backdrop;
    t_list* text_lst;
    flag_t* flags;

} debug_t;

typedef struct prog_s
{
    mlx_t* mlx;
    mlx_image_t* img;
    debug_t* dbg_menu;
    mlx_btn_t* btn_data;
    int sizeX;
    int sizeY;

} prog_t;


//small utility functions
int mouse_on_canvas(int x, int y);

//setup debug menu
void setup_debug_menu(prog_t* prog);
void create_btn_layout(prog_t* prog);

//debug menu functions
void enable_floodfill(void *param);
void clear_canvas(void *param);
void exec_flood_fill(mouse_key_t button, action_t action, modifier_key_t mods, void *param);
void flood_fill(mlx_image_t* image,int x, int y, int32_t color);



//useful functions outside of this project
void set_img_color(mlx_image_t* img,int32_t color);
int get_txt_midX(char *str);

#endif
