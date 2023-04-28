#include "generic.h"

void create_btn_layout(prog_t* prog)
{
    char *h_txt = "DEBUG MENU";
    mlx_image_t* header = mlx_put_string(prog->mlx,h_txt,DBG_CANV_CENTER_X - get_txt_midX(h_txt),0);

    button_t* reset = mlx_create_button(prog->btn_data,NULL,LONG_BTN_SIZE,SQ_BTN_SIZE);
    mlx_set_btn_text(reset,"Reset Canvas",TEXT_CENTER);
    btn_bind_on_click(reset,clear_canvas,prog);
    mlx_button_to_window(prog->mlx,reset,prog->dbg_menu->posX,20);

    button_t* ff = mlx_create_button(prog->btn_data,NULL,SQ_BTN_SIZE,SQ_BTN_SIZE);
    mlx_set_btn_text(ff,"FF",TEXT_CENTER);
    btn_bind_on_click(ff,enable_floodfill,prog);
    mlx_button_to_window(prog->mlx,ff,prog->dbg_menu->posX,50);

    btn_textures_t *text = mlx_create_btn_textures_from_colors(30,30,prog->dbg_menu->flags->ff_col,prog->dbg_menu->flags->ff_col,prog->dbg_menu->flags->ff_col);
    button_t* ff_col = mlx_create_button(prog->btn_data,text,SQ_BTN_SIZE,SQ_BTN_SIZE);
    mlx_set_btn_text(ff_col,"RC",TEXT_CENTER);
    btn_bind_on_click(ff_col,randomize_ff_col,prog);
    mlx_button_to_window(prog->mlx,ff_col,prog->dbg_menu->posX + 30,50);
}

void setup_debug_menu(prog_t* prog)
{
    prog->dbg_menu = malloc(sizeof(debug_t));
    prog->dbg_menu->sizeX = DBG_WIDTH;
    prog->dbg_menu->sizeY = HEIGHT;
    prog->dbg_menu->posX = WIDTH - DBG_WIDTH;
    prog->dbg_menu->posY = 0;
    prog->dbg_menu->backdrop =  mlx_new_image(prog->mlx, DBG_WIDTH, HEIGHT);
    set_img_color(prog->dbg_menu->backdrop, DBG_IMG_COLOR);
    mlx_image_to_window(prog->mlx, prog->dbg_menu->backdrop, prog->dbg_menu->posX, prog->dbg_menu->posY);

    // flags
    prog->dbg_menu->flags = malloc(sizeof(flag_t));
    prog->dbg_menu->flags->b_ff = false;
    prog->dbg_menu->flags->ff_col = 0x303030FF;


    create_btn_layout(prog);
    //hooks
    generic_mouse_hook(prog->btn_data,exec_flood_fill,prog);
}

