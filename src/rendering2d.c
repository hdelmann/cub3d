#include "../includes/Cub3D.h"



void fillcubeborder(t_runtime *r)
{
    int i;
    int j;
    int x;
    int y;

    y = 20;
    i = 0;
   // printf("seg ou? %c\n", r->map.un_pmap[1][1]);

    while(r->map.map[i])
    {
        x = 64;
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
            x += 64;
            j++;
        }
        i++;
        y += 64;
    }
}

void playerendering2d(void  *param)
{
    t_runtime  *r;
    r = param;
    //fillcubeborder(r);
    /*for (int i = r->player.pos.y + 1; i < r->player.pos.y + PLAYER_SIZE; i++) {
        for (int j = r->player.pos.x  - 1; j > r->player.pos.x - PLAYER_SIZE; j--) {
            my_mlx_put_pixel(r->img, j, i, get_rgba(255, 0, 0, 255));
        }
    }*/
    for (int i = 0; i < 320; i++) {
        for (int j = 0 ; j < 200; j++) {
            my_mlx_put_pixel(r->img, i, j, get_rgba(255, 0, 0, 255));
        }
    }
    calcul_line_intery(r);
    calcul_line_interx(r);
    if (r->line.end.x == r->line.start.x && r->line.end.y == r->line.start.y)
    {        
        r->line.end.x = r->line.end_v.x;
        r->line.end.y = r->line.end_v.y;
    }
    else if  (!(r->line.end_v.x == r->line.start_v.x && r->line.end_v.y == r->line.start_v.y) && sqrt(((r->line.end.x - r->line.start.x) * (r->line.end.x - r->line.start.x)) + ((r->line.end.y - r->line.start.y) * (r->line.end.y - r->line.start.y))) > sqrt(((r->line.end_v.x - r->line.start.x) * (r->line.end_v.x - r->line.start.x)) + ((r->line.end_v.y - r->line.start.y) * (r->line.end_v.y - r->line.start.y))))
    {
        r->line.end.x = r->line.end_v.x;
        r->line.end.y = r->line.end_v.y;
    }
    r->line.end_def.x = r->line.end.x;
    r->line.end_def.y = r->line.end.y;
    fov_rendering(r);
}

void fov_rendering(t_runtime *r)
{
    float tmp_rad;
    float i = 0;
    r->line.rad_fov= r->player.pdir_v - r->player.FOV/2;
    tmp_rad = r->line.rad_fov;
    while (tmp_rad <= r->player.pdir_v + r->player.FOV/2)
    {
        //printf("i = %d\n", i);
        i++;
        tmp_rad = r->line.rad_fov;
        if (r->line.rad_fov < 0)
        {
            r->line.rad_fov += 2 * PI; 
        }
        else if (r->line.rad_fov >= 2 * PI)
        {
            r->line.rad_fov -= 2 * PI;
        }
        //printf("rad2 = %f\n", r->line.rad_in);
        calcul_line_fovx(r);
        calcul_line_fovy(r);
        if (r->line.end_fov.x == r->line.start_fov.x && r->line.end_fov.y == r->line.start_fov.y)
        {  
            r->line.end_fov.x = r->line.end_fov2.x;
            r->line.end_fov.y = r->line.end_fov2.y;
        }
        if ((r->line.end_fov2.x == r->line.start_fov.x && r->line.end_fov2.y == r->line.start_fov.y))
        {}
        else if  (sqrt(((r->line.end_fov.x - r->line.start_fov.x) * (r->line.end_fov.x - r->line.start_fov.x)) + ((r->line.end_fov.y - r->line.start_fov.y) * (r->line.end_fov.y - r->line.start_fov.y))) > sqrt(((r->line.end_fov2.x - r->line.start_fov.x) * (r->line.end_fov2.x - r->line.start_fov.x)) + ((r->line.end_fov2.y - r->line.start_fov.y) * (r->line.end_fov2.y - r->line.start_fov.y))))
        {
            r->line.end_fov.x = r->line.end_fov2.x;
            r->line.end_fov.y = r->line.end_fov2.y;
        }
        r->line.end_defov.x = r->line.end_fov.x;
        r->line.end_defov.y = r->line.end_fov.y;
       // printf("y = %f, x = %f\n ", r->line.end_defov.y, r->line.end_defov.x);
       // my_draw_line(r);
        r->line.rad_fov = tmp_rad;
        r->line.rad_fov += 0.003290;
        r->line.dist = calucl_dist(r->line.start_fov.x, r->line.end_defov.x, r->line.start_fov.y, r->line.end_defov.y) * cos(r->line.rad_fov - r->player.pdir_v);
        printf("ray%f = %f\n", i, r->line.dist);
        playerrendering3D(r, i);
    }
}
//faire un tableau pour tester les deplacement car sinon ca peut buger giltch hors map
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
        if (sqrt(((r->line.end_def.x - r->player.pos.x) * (r->line.end_def.x - r->player.pos.x)) + ((r->line.end_def.y - r->player.pos.y) * (r->line.end_def.y - r->player.pos.y))) > 10)
        {
            r->player.pos.x += roundf((float)(cos(r->player.pdir)));
            r->player.pos.y -= roundf((float)(sin(r->player.pdir)));
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
        if (sqrt(((r->line.end_def.x - r->player.pos.x) * (r->line.end_def.x - r->player.pos.x)) + ((r->line.end_def.y - r->player.pos.y) * (r->line.end_def.y - r->player.pos.y))) > 10)
        {
            r->player.pos.x += roundf((float)(cos(r->player.pdir)));
            r->player.pos.y -= roundf((float)(sin(r->player.pdir)));
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
        if (sqrt(((r->line.end_def.x - r->player.pos.x) * (r->line.end_def.x - r->player.pos.x)) + ((r->line.end_def.y - r->player.pos.y) * (r->line.end_def.y - r->player.pos.y))) > 10)
        {
            r->player.pos.x += roundf((float)(cos(r->player.pdir)));
            r->player.pos.y -= roundf((float)(sin(r->player.pdir)));
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
        if (sqrt(((r->line.end_def.x - r->player.pos.x) * (r->line.end_def.x - r->player.pos.x)) + ((r->line.end_def.y - r->player.pos.y) * (r->line.end_def.y - r->player.pos.y))) > 10)
        {
            r->player.pos.x += roundf((float)(cos(r->player.pdir)));
            r->player.pos.y -= roundf((float)(sin(r->player.pdir)));
        }
    }
    if(mlx_is_key_down(r->mlx, MLX_KEY_LEFT))
    {
        r->player.pdir -= 0.0174533 * 2;
        if(r->player.pdir < 0)
		{
			r->player.pdir += 2 * PI;
		}
        r->player.pdir_v -= 0.0174533 * 2;
        if(r->player.pdir_v < 0)
		{
            r->player.pdir_v += 2 * PI;
		}

    }
    if(mlx_is_key_down(r->mlx, MLX_KEY_RIGHT))
    {
       r->player.pdir += 0.0174533 * 2;
        if(r->player.pdir > 2 * PI)
		{
			r->player.pdir -= 2 * PI;
		}
        r->player.pdir_v += 0.0174533 * 2;
        if(r->player.pdir_v > 2 * PI)
		{
			r->player.pdir_v -= 2 * PI;
		}
    }
}

void my_draw_line(t_runtime *r)
{
    float xsta = r->line.start_fov.x;
    float ysta = r->line.start_fov.y;
    float xend = r->line.end_defov.x;
    float yend = r->line.end_defov.y;
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
/*
void my_draw_line_fov(t_runtime *r)
{
    int k = 0;
    float tmpx = r->line.start_v.x;
    float tmpy = r->line.start_v.y;
    float tmprad = r->line.rad_raystart_v;
    while (k < WIDTH / 2)
    { 

        int i = 0;
        int j = 0;
        while (1)
        {
            r->line.end_v.x = roundf(r->player.pos.x + (float)(i* cos(r->line.rad_raystart_v))) - 5;
            r->line.end_v.y = roundf(r->player.pos.y + (float)(j*sin(r->line.rad_raystart_v))) + 5;
            i += 1;
            j += 1;
            if (r->map.map[(int)r->line.end_v.y / 100][(int)r->line.end_v.x / 100] == '1')
                break;
        }
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
        r->line.rad_raystart_v += r->line.rad_in;
        k++;
        r->line.start_v.y = tmpy;
        r->line.start_v.x = tmpx;
    }
    r->line.rad_raystart_v = tmprad;
    k = 0;
    while (k < WIDTH / 2)
    { 

        int i = 0;
        int j = 0;
        while (1)
        {
            r->line.end_v.x = roundf(r->player.pos.x + (float)(i* cos(r->line.rad_raystart_v))) - 5;
            r->line.end_v.y = roundf(r->player.pos.y + (float)(j*sin(r->line.rad_raystart_v))) + 5;
            i += 1;
            j += 1;
            if (r->map.map[(int)r->line.end_v.y / 100][(int)r->line.end_v.x / 100] == '1')
                break;
        }
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
        r->line.rad_raystart_v -= r->line.rad_in;
        k++;
        r->line.start_v.y = tmpy;
        r->line.start_v.x = tmpx;
    }
}   */