#include "../includes/Cub3D.h"
// void my_draw_line_4D(float x0, float y0, float y1, t_runtime *r, int txt)
// {
//     float xsta = x0;
//     float ysta = y0;
//     float xend = x0;
//     float yend = y1;
//     float dx = my_fabs(xsta - xend);
//     float dy = my_fabs(ysta - yend);
//     float sx = (xsta < xend) ? 1 : -1;
//     float sy = (ysta < yend) ? 1 : -1;
//     float err = dx - dy;
//     int   color;
//     while (1 && xsta <= WIDTH && ysta <= HEIGHT && xsta >= 0 && ysta >= 0)
//     {
//         // Calculate the offset in the texture's pixels for the current pixel
//        int tx = (int)xend % r->txtrs[txt].walltxt->width;
//        int ty = (int)yend % r->txtrs[txt].walltxt->height;
//        int texture_pixel = (ty * r->txtrs[txt].walltxt->width + tx) * sizeof(int32_t);

//        // Get the color of the pixel in the texture
//        color = *(int32_t*)(r->txtrs[txt].walltxt->pixels + texture_pixel);

//        // Calculate the offset in the image's pixels for the current pixel
//       // int img_pixel = (y1 * r->img->width + xsta) * sizeof(int32_t);

//        // Set the color of the pixel in the image
//          my_mlx_put_pixel(r->img, xsta, ysta, color);

//        // Check if the line has been drawn
//        if (xsta == xend && y1 == yend)
//            break;

//        // Calculate the error for the next pixel
//        int e2 = 2 * err;
//        if (e2 > -dy)
//        {
//            err -= dy;
//            xsta += sx;
//        }
//        if (e2 < dx)
//        {
//            err += dx;
//            y1 += sy;
//        }
//     }
    


// }

void    playerrendering3D(void *param, float xray){
    t_runtime *r;

    float height;
    r = param;
    //printf("ray%f = %f\n", xray, r->line.dist);
    height = fabs((64.0/r->line.dist) * (960.0/tan(30.0)));
    //printf("height = %f\n", height);
    float y0 = 540.0 - (height / 2.0);
    float y1 = 540.0 + (height / 2.0);
    //printf("x0 = %f, x1 = %f\n", xray, xray);
    if (y0 < 0)
        y0 = 0;
    if (y1 > HEIGHT)
        y1 = HEIGHT;
    
    //printf("y0 = %f, y1 = %f\n", y0, y1);
    //draw_textured_wall(r, y0, y1, SO, height, xray);
    my_draw_line_3D(xray, y0, y1, r);

}



void my_draw_line_3D(float x0, float y0, float y1, t_runtime *r)
{
    //printf("GET PREGNANT\n");
    float xsta = x0;
    float ysta = y0;
    float xend = x0;
    float yend = y1;
    int e2;
    float dx = my_fabs(xsta - xend);
    float dy = my_fabs(ysta - yend);
    float sx = (xsta < xend) ? 1 : -1;
    float sy = (ysta < yend) ? 1 : -1;
    float err = dx - dy;
    while (1 && xsta <= WIDTH && ysta <= HEIGHT && xsta >= 0 && ysta >= 0)
    {
        if (r->line.ort == VER && roundf(ysta) != roundf(yend))
             my_mlx_put_pixel(r, roundf((int)xsta), roundf((int)ysta), get_rgba(0, 0, 255, 255));
        else if (r->line.ort == HOR && roundf(ysta) != roundf(yend))
            my_mlx_put_pixel(r, roundf((int)xsta), roundf((int)ysta), get_rgba(0, 255, 0, 255));
        else if (roundf(ysta) == roundf(yend) || roundf(ysta) == roundf(yend) - 1 || roundf(xsta) == 0 || roundf(xsta) == 1)
            my_mlx_put_pixel(r, roundf((int)xsta), roundf((int)ysta), get_rgba(0, 255, 0, 255));
        //my_mlx_put_pixel(r->img, roundf((int)xsta), roundf((int)ysta), get_rgba(0, 155, 0, 255));
        if (roundf(xsta) == roundf(xend) && roundf(ysta) == roundf(yend))
            break;
        e2 = 2* err;
        if (e2 > -dy)
        {
            err -= dy;
            xsta += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            ysta  += sy;
        }
    }
}



