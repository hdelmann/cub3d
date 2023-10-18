#include "../includes/Cub3D.h"

void calcul_line(void *param)
{
    t_runtime *r;
    int i = 0;
    int j = 0;
    r = param;
    r->line.rad_raystart = r->player.pdir + FOV / 2;
    
    r->line.start.x = r->player.pos.x - 5;
    r->line.start_v.x = r->player.pos.x - 5;
    r->line.start.y = r->player.pos.y + 5;
    r->line.start_v.y = r->player.pos.y + 5;
    while(1)
    {
        r->line.end.x = roundf(r->player.pos.x + (float)(i* cos(r->line.rad_raystart))) - 5;
        r->line.end.y = roundf(r->player.pos.y + (float)(j*sin(r->line.rad_raystart))) + 5;
        i += 1;
        j += 1;
        if (r->map.map[(int)r->line.end.y / 100][(int)r->line.end.x / 100] == '1')
            break;
    }
    i = 0;
    j = 0;
    while (1)
    {
        r->line.end_v.x = roundf(r->player.pos.x + (float)(i* cos(r->line.rad_raystart_v))) - 5;
        r->line.end_v.y = roundf(r->player.pos.y + (float)(j*sin(r->line.rad_raystart_v))) + 5;
        i += 1;
        j += 1;
        if (r->map.map[(int)r->line.end_v.y / 100][(int)r->line.end_v.x / 100] == '1')
            break;
    }
}

/*void calcul_border(t_runtime *r)
{
    t_point posborder;

    posborder.x = r->player.pos.x / CASE_SIZE;
    posborder.y = r->player.pos.y / CASE_SIZE;

}*/