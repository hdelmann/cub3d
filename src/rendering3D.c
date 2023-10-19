#include "../includes/Cub3D.h"

void    playerrendering3D(void *param){
    t_runtime *r;

    r = param;
    r->line.z = 1 / (sqrt(((r->line.end.x - r->line.start.x) * (r->line.end.x - r->line.start.x)) + ((r->line.end.y - r->line.start.y) * (r->line.end.y - r->line.start.y))));
    r->iso.x_iso = r->line.end.x - r->line.end.y;
    r->iso.y_iso = (r->line.end.x - r->line.end.y) / (2 - r->line.z);
    my_draw_line(r);
}