#include "../includes/Cub3D.h"

void    playerrendering3D(void *param){
    t_runtime *r;

    r = param;
    r->line.z = 1 / (sqrt(((r->line.end.x - r->line.start.x) * (r->line.end.x - r->line.start.x)) + ((r->line.end.y - r->line.start.y) * (r->line.end.y - r->line.start.y))));
    r->iso.x_iso = r->line.end.x - r->line.end.y;
    r->iso.y_iso = (r->line.end.x - r->line.end.y) / (2 - r->line.z);
    //my_mlx_put_pixel(r->img, fabs(r->iso.x_iso), fabs(r->iso.y_iso), get_rgba(255, 0, 0, 255));
}