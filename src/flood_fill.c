#include "generic.h"

//note this function has issues because of the stack size limitation
void rec_flood_fill(mlx_image_t* img,int x, int y, uint32_t new_col, uint32_t old_col)
{
    if(x <= 0 + 300 || x >= DFT_CANV_WIDTH-300 || y <= 0 + 300 || y >= HEIGHT -300)
        return;
    if(get_pixel_color(img,x,y) != old_col)//pixel at that position is already of that color
        return;

    mlx_put_pixel(img,x,y,new_col);

    rec_flood_fill(img, x , y -1 ,new_col,old_col);
    rec_flood_fill(img, x , y + 1,new_col,old_col);
    rec_flood_fill(img, x -1, y,new_col,old_col);
    rec_flood_fill(img, x +1, y,new_col,old_col);

}

void lin_flood_fill(mlx_image_t* img,int x, int y, uint32_t new_col, uint32_t old_col)
{
    bool **visited = (bool **)malloc(img->width * sizeof(bool *));
    for (int i = 0; i < img->width; i++) {
        visited[i] = (bool *)malloc(img->height * sizeof(bool));
        memset(visited[i], false, img->height * sizeof(bool));
    }
    int stack_size = 0;
    int max_stack_size = img->width * img->height;

    int *stack_x = malloc(sizeof(int) *max_stack_size);
    int *stack_y = malloc(sizeof(int) *max_stack_size);

    // push the starting pixel onto the stack
    stack_x[stack_size] = x;
    stack_y[stack_size] = y;
    stack_size++;
    while(stack_size > 0) {
        // pop the top pixel from the stack
        stack_size--;
        int curr_x = stack_x[stack_size];
        int curr_y = stack_y[stack_size];
        // check if the pixel color matches the old color and it has not been visited
        if(!visited[curr_x][curr_y] && get_pixel_color(img, curr_x, curr_y) == old_col) {
            // fill the pixel with the new color
            mlx_put_pixel(img, curr_x, curr_y, new_col);
            visited[curr_x][curr_y] = true;
            // push the neighboring pixels onto the stack if they have not been visited
            if(curr_x > 0 && !visited[curr_x - 1][curr_y]) {
                stack_x[stack_size] = curr_x - 1;
                stack_y[stack_size] = curr_y;
                stack_size++;
            }
            if(curr_x < img->width-1 && !visited[curr_x + 1][curr_y]) {
                stack_x[stack_size] = curr_x + 1;
                stack_y[stack_size] = curr_y;
                stack_size++;
            }
            if(curr_y > 0 && !visited[curr_x][curr_y - 1]) {
                stack_x[stack_size] = curr_x;
                stack_y[stack_size] = curr_y - 1;
                stack_size++;
            }
            if(curr_y < img->height-1 && !visited[curr_x][curr_y + 1]) {
                stack_x[stack_size] = curr_x;
                stack_y[stack_size] = curr_y + 1;
                stack_size++;
            }
        }
    }

    for (int i = 0; i < img->width; i++)
        free( visited[i]);
    free(visited);
    free(stack_x);
    free(stack_y);

}
