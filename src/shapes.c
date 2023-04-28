#include "generic.h"


void setup_shape(prog_t* prog)
{
    prog->shapes = malloc(sizeof(shape_t*) * 1);

    prog->shapes[0] = load_shape_from_file("./resources/shapes/square.shape", COL_BLACK);
    prog->shapes[0]->id = SP_SQUARE;
    prog->shapes[1] = load_shape_from_file("./resources/shapes/circle.shape", COL_BLACK);
    prog->shapes[0]->id = SP_CIRCLE;
    print_shape(prog->shapes[0]);
}

//returns a generic shape of size x*y grid, actual shape still needs to be drawn
shape_t* init_shape(int x,int y, uint32_t col)
{
    shape_t* shape = malloc(sizeof(shape_t));
    shape->col = col;
    shape->size_x = x;
    shape->size_y = y;

    shape->arr = malloc(sizeof(bool *) * x);
    for (int i = 0; i < x; i++)
    {
        shape->arr[i] = malloc(sizeof(bool) * y);
        memset(shape->arr[i], false, y * sizeof(bool));
    }


    return shape;
}

void print_shape(shape_t* shape)
{
    for (int i = 0; i < shape->size_x; i++)
    {
        for (int j = 0; j < shape->size_y; j++)
            printf("%d ",shape->arr[i][j]);
        printf("\n");
    }

}

void draw_shape(mlx_image_t* img, shape_t* shape,int x, int y,double scale)
{
    int offset_x = shape->size_x/2;
    int offset_y = shape->size_y/2;
    for (int i = 0; i < shape->size_x ; i++)
    {
        for (int j = 0; j < shape->size_y ; j++)
        {
/*             for (int temp = j; temp < shape->size_x * scale; i++)
            {
                if(shape->arr[i][j] && pos_on_canvas(x + i , y + j ))
                    mlx_put_pixel(img, x + i, y + j , shape->col);
            } */

            if(shape->arr[i][j] && pos_on_canvas(x + i - offset_x, y + j - offset_y))
                mlx_put_pixel(img, x + i - offset_x, y + j - offset_y, shape->col);
        }

    }

}

//line 1 = size_x
//line 2 = size_y
//rest = grid
//this file has 0 error checks!
shape_t* load_shape_from_file(char* path,uint32_t col)
{
    int fd = open(path,O_RDONLY);
    printf("fd = %i\n",fd);
    char *line = get_next_line(fd);
    int x = ft_atoi(line);
    free(line);
    line = get_next_line(fd);
    int y = ft_atoi(line);
    free(line);
    printf("[%i][%i]\n",x,y);
    shape_t* shape = malloc(sizeof(shape_t));
    shape->col = col;
    shape->size_x = x;
    shape->size_y = y;

    shape->arr = malloc(sizeof(bool *) * x);
    for (int i = 0; i < x; i++)
        shape->arr[i] = malloc(sizeof(bool) * y);

    for (int i = 0; i < y; i++)
    {
        line = get_next_line(fd);
        for (int j = 0; j < x; j++)
        {
            shape->arr[i][j] = (bool)(line[j] - '0');
        }
        free(line);
    }
    return shape;
}
