#ifndef GENERIC_H
#define GENERIC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/stat.h>
#include <fcntl.h>

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


#define COL_BLACK 0x000000FF

enum shape{
    SP_SQUARE,
    SP_CIRCLE,
};

typedef struct shape_s
{
    enum shape id;
    bool **arr;
    int size_x;
    int size_y;
    uint32_t col;

} shape_t;


typedef struct flag_s
{
    bool b_ff;
    uint32_t ff_col;
    bool b_draw_shape;
    double shape_scale;

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
    shape_t** shapes; //just holds 1 for now to test functionality
} prog_t;


//small utility functions
int pos_on_canvas(int x, int y);

//setup debug menu
void setup_debug_menu(prog_t* prog);
void create_btn_layout(prog_t* prog);

//debug menu functions
void enable_floodfill(void *param);
void enable_draw_shape(void *param);
void clear_canvas(void *param);
void randomize_ff_col(void *param);
void generate_noise(void *param);

//mouse_hook events
void exec_flood_fill(mouse_key_t button, action_t action, modifier_key_t mods, void *param);
void exec_draw_shape(mouse_key_t button, action_t action, modifier_key_t mods, void *param);

void mouse_scroll(double xdelta, double ydelta, void* param);

//flood fill
void rec_flood_fill(mlx_image_t* image,int x, int y, uint32_t color, uint32_t old_col);
void lin_flood_fill(mlx_image_t* img,int x, int y, uint32_t new_col, uint32_t old_col);

//shape stuff
void setup_shape(prog_t* prog);
shape_t* init_shape(int x,int y, uint32_t col);
void print_shape(shape_t* shape);
void draw_shape(mlx_image_t* img, shape_t* shape,int x, int y,double scale);
shape_t* load_shape_from_file(char* path, uint32_t col);

//useful functions outside of this project
void set_img_color(mlx_image_t* img,int32_t color);
int get_txt_midX(char *str);
uint32_t get_pixel_color(mlx_image_t* img,int x,int y);
void set_text_color(mlx_texture_t* img,int32_t color);

#endif
