#include "../includes/Cub3D.h"

void fillcubeborder(t_runtime *r)
{
    int i;
    int j;
    int x;
    int y;

    y = 0;
    i = 0;
   // printf("seg ou? %c\n", r->map.un_pmap[1][1]);

    while(r->map.map[i])
    {
        x = 100;
        j = 0;
        while(r->map.map[i][j])
        {
            for (int k = y; k <= y + CASE_SIZE; k++) {
                for (int l = x; l >= x - CASE_SIZE; l--) {
                    my_mlx_put_pixel(r->img, l, k, get_rgba(105, 105, 105, 255));
                }
            }
            if (r->map.map[i][j] == '1')
            {
                for (int k = y + 2; k <= y + CASE_SIZE; k++) {
                    for (int l = x - 2; l >= x - CASE_SIZE; l--) {
                        my_mlx_put_pixel(r->img, l, k, get_rgba(255, 255, 255, 255));
                    }
                }
            }
            else if (r->map.map[i][j] != '1')
            {
                for (int k = y + 2; k <= y + CASE_SIZE; k++) {
                    for (int l = x - 2; l >= x - CASE_SIZE; l--) {
                        my_mlx_put_pixel(r->img, l, k, get_rgba(0, 0, 0, 255));
                    }
                }
            }
            x += 100;
            j++;
        }
        i++;
        y += 100;
    }
}

void playerendering2d(void  *param)
{
    t_runtime  *r;
    int i;

    i = 0;
    r = param;
    r->line.rad_in = FOV / WIDTH;
    fillcubeborder(r);
     for (int i = r->player.pos.y + 1; i < r->player.pos.y + PLAYER_SIZE; i++) {
        for (int j = r->player.pos.x  - 1; j > r->player.pos.x - PLAYER_SIZE; j--) {
            my_mlx_put_pixel(r->img, j, i, get_rgba(255, 0, 0, 255));
        }
    }
    my_draw_line(r);
    r->line.rad_raystart_v = r->player.pdir_v + FOV / 2;
    while (i < WIDTH)
    {
        my_draw_line_fov(r);
        //r->line.rad_raystart_v -= r->line.rad_in;
        i++;
        //printf("do");
    }
}

void my_keyhook(mlx_key_data_t keydata, void *param)
{
    t_runtime *r;

    r = param;
    (void)keydata;
    if(mlx_is_key_down(r->mlx, MLX_KEY_D))
    {   
        if(r->player.dir == DIR_W)
            r->player.pdir += PI/2;
        if(r->player.dir == DIR_S)
            r->player.pdir -= PI/2;        
        if(r->player.dir == DIR_A)
            r->player.pdir -= PI;
        r->player.dir = DIR_D;
        if (sqrt(((r->line.end.x - r->line.start.x) * (r->line.end.x - r->line.start.x)) + ((r->line.end.y - r->line.start.y) * (r->line.end.y - r->line.start.y))) > 15)
        {
            r->player.pos.x += roundf((float)(5* cos(r->line.rad_raystart)));
            r->player.pos.y += roundf((float)(5 * sin(r->line.rad_raystart)));
        }
    }
    if(mlx_is_key_down(r->mlx, MLX_KEY_W))
    {
        if(r->player.dir == DIR_S)
            r->player.pdir -= PI;
        if(r->player.dir == DIR_A)
            r->player.pdir += PI/2;        
        if(r->player.dir == DIR_D)
            r->player.pdir -= PI/2;
        r->player.dir = DIR_W;
        if (sqrt(((r->line.end.x - r->line.start.x) * (r->line.end.x - r->line.start.x)) + ((r->line.end.y - r->line.start.y) * (r->line.end.y - r->line.start.y))) > 15)
        {
            r->player.pos.x += roundf((float)(5* cos(r->line.rad_raystart)));
            r->player.pos.y += roundf((float)(5 * sin(r->line.rad_raystart)));
        }
    }
    if(mlx_is_key_down(r->mlx, MLX_KEY_S))
    {
        if(r->player.dir == DIR_W)
            r->player.pdir += PI;
        if(r->player.dir == DIR_A)
            r->player.pdir -= PI/2;        
        if(r->player.dir == DIR_D)
            r->player.pdir += PI/2;
        r->player.dir = DIR_S;
        if (sqrt(((r->line.end.x - r->line.start.x) * (r->line.end.x - r->line.start.x)) + ((r->line.end.y - r->line.start.y) * (r->line.end.y - r->line.start.y))) > 15)
        {
            r->player.pos.x += roundf((float)(5* cos(r->line.rad_raystart)));
            r->player.pos.y += roundf((float)(5 * sin(r->line.rad_raystart)));
            //r->player.pdir += PI;
        }
    }
    if(mlx_is_key_down(r->mlx, MLX_KEY_A))
    {
        if(r->player.dir == DIR_W)
            r->player.pdir -= PI/2;
        if(r->player.dir == DIR_S)
            r->player.pdir += PI/2;        
        if(r->player.dir == DIR_D)
            r->player.pdir += PI;
        r->player.dir = DIR_A;
        if (sqrt(((r->line.end.x - r->line.start.x) * (r->line.end.x - r->line.start.x)) + ((r->line.end.y - r->line.start.y) * (r->line.end.y - r->line.start.y))) > 15)
        {
            r->player.pos.x += roundf((float)(5* cos(r->line.rad_raystart)));
            r->player.pos.y += roundf((float)(5 * sin(r->line.rad_raystart)));
        }
    }
    if(mlx_is_key_down(r->mlx, MLX_KEY_LEFT))
    {
        r->player.pdir -= 0.0174533 * 5;
        if(r->player.pdir < 0)
		{
			r->player.pdir += 2 * PI;
		}
        r->player.pdir_v -= 0.0174533 * 5;
        if(r->player.pdir_v < 0)
		{
            r->player.pdir_v += 2 * PI;
		}

    }
    if(mlx_is_key_down(r->mlx, MLX_KEY_RIGHT))
    {
       r->player.pdir += 0.0174533 * 5;
        if(r->player.pdir > 2 * PI)
		{
			r->player.pdir -= 2 * PI;
		}
        r->player.pdir_v += 0.0174533 * 5;
        if(r->player.pdir_v > 2 * PI)
		{
			r->player.pdir_v -= 2 * PI;
		}
    }

}

void my_draw_line(t_runtime *r)
{
    int e2;
    float dx = my_fabs(r->line.start.x - r->line.end.x);
    float dy = my_fabs(r->line.start.y - r->line.end.y);
    float sx = (r->line.start.x < r->line.end.x) ? 1 : -1;
    float sy = (r->line.start.y < r->line.end.y) ? 1 : -1;
    float err = dx - dy;
    while (1)
    {
        my_mlx_put_pixel(r->img, r->line.start.x, r->line.start.y, get_rgba(0, 255, 255, 255));
        if (r->line.start.x == r->line.end.x && r->line.start.y == r->line.end.y)
            break;
        e2 = 2* err;
        if (e2 > -dy)
        {
            err -= dy;
            r->line.start.x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            r->line.start.y += sy;
        }
    }
}

void my_draw_line_fov(t_runtime *r)
{
    int e2;
    float dx = my_fabs(r->line.start_v.x - r->line.end_v.x);
    float dy = my_fabs(r->line.start_v.y - r->line.end_v.y);
    float sx = (r->line.start_v.x < r->line.end_v.x) ? 1 : -1;
    float sy = (r->line.start_v.y < r->line.end_v.y) ? 1 : -1;
    float err = dx - dy;
    while (1)
    {
        my_mlx_put_pixel(r->img, r->line.start_v.x, r->line.start_v.y, get_rgba(0, 0, 255, 255));
        if (r->line.start_v.x == r->line.end_v.x && r->line.start_v.y == r->line.end_v.y)
            break;
        e2 = 2* err;
        if (e2 > -dy)
        {
            err -= dy;
            r->line.start_v.x += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            r->line.start_v.y += sy;
        }
    }
}