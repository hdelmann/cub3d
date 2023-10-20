#include "../includes/Cub3D.h"

void    playerrendering3D(void *param, float xray){
    t_runtime *r;

    float height;
    r = param;
    printf("ray%f = %f\n", xray, r->line.dist);
    height = (64.0/r->line.dist) * (160.0/tan(30.0));
    printf("height = %f\n", height);
    float y0 = 100.0 - (height / 2.0);
    float y1 = 100.0 + (height / 2.0);
    //printf("y0 = %f, y1 = %f\n", y0, y1);
    //printf("x0 = %f, x1 = %f\n", xray, xray);

    my_draw_line_3D(xray, y0, y1, r);

}

void my_draw_line_3D(float x0, float y0, float y1, t_runtime *r)
{
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
    while (1)
    {
        my_mlx_put_pixel(r->img, roundf((int)xsta), roundf((int)ysta), get_rgba(0, 255, 255, 255));
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