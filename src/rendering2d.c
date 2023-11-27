#include "../includes/Cub3D.h"

int test_dist(float *tab, int dist)
{
    for (int i = 0; tab[i] != -1 ; i++)
    {
        if (tab[i] < dist)
        {
            printf("dist= %f\n", tab[i]);
            return (0);
        }
    }
    return (1);
}

int playerendering2d(t_runtime  *r)
{

    int i;
    int j;
    for (i = 0; i < WIDTH; i++) {
        for (j = 0 ; j < HEIGHT/2; j++) {
            my_mlx_put_pixel(r, i, j, get_rgba(r->color[CEIL].c_red, r->color[CEIL].c_green, r->color[CEIL].c_blue, 255));
        }
    }
    for (i = 0;i < WIDTH; i += 2) {
        for (j = HEIGHT/2 ;j < HEIGHT; j++) {
            my_mlx_put_pixel(r, i, j, get_rgba(r->color[FLR].c_red, r->color[FLR].c_green, r->color[FLR].c_blue, 255));
        }
    }
    for (i = 1;i < WIDTH; i += 2) {
        for (j = HEIGHT/2 ;j < HEIGHT; j++) {
            my_mlx_put_pixel(r, i, j, get_rgba(r->color[FLR].c_red, r->color[FLR].c_green, r->color[FLR].c_blue, 255));
        }
    }
    for (j = HEIGHT/2;j < HEIGHT; j += 2) {
        for (i = WIDTH ;i < WIDTH; i++) {
            my_mlx_put_pixel(r, i, j, get_rgba(r->color[CEIL].c_red, r->color[CEIL].c_green, r->color[CEIL].c_blue, 255));
        }
    }
    fov_rendering(r);
    mlx_put_image_to_window(r->mlx, r->mlx_win, r->img.img, 0, 0);
    return(0);
}

void fov_rendering(t_runtime *r)
{
    float tmp_rad;
    t_point endinter;

    float i = 0;
    int x = 0;
    r->line.rad_fov= r->player.pdir + r->player.fov/2;
    tmp_rad = r->line.rad_fov;
    if (r->player.pos.x - (int)r->player.pos.x == 0 && (int)r->player.pos.x % CASE_SIZE == 0)
        r->player.pos.x -= 0.01;
    if (r->player.pos.y - (int)r->player.pos.y == 0 && (int)r->player.pos.y % CASE_SIZE == 0)
        r->player.pos.y -= 0.01;
    while (tmp_rad >= r->player.pdir - r->player.fov/2)
    {
        tmp_rad = r->line.rad_fov;
        while (r->line.rad_fov < 0)
        {
            r->line.rad_fov += 2 * PI; 
        }
        while (r->line.rad_fov > 2 * PI)
        {
            r->line.rad_fov -= 2 * PI;
        }
        endinter = calcul_inter(r, r->line.rad_fov);
        r->line.end_fov.x = endinter.x;
        r->line.end_fov.y = endinter.y;
        r->line.rad_fov = tmp_rad;
        r->line.rad_fov -= 0.0005457;
        r->line.dist = calucl_dist(r->player.pos.x, endinter.x, r->player.pos.y, endinter.y) * cos(r->line.rad_fov - r->player.pdir_v);
        playerrendering_3d(r, x);
        i++;
        x++;
    }
}

//faire un tableau pour tester les deplacement car sinon ca peut buger giltch hors map
int my_keyhook(int keycode, t_runtime *r)
{
    float *dist_tab;
    //(void)keydata;
    (void)dist_tab;
    //printf("keydata = %d\n", keycode);

    if (keycode == ESC)
    {
        mlx_destroy_image(r->mlx, r->img.img);
        mlx_destroy_image(r->mlx, r->txt_d[NO].img);
        mlx_destroy_image(r->mlx, r->txt_d[EA].img);
        mlx_destroy_image(r->mlx, r->txt_d[SO].img);
        mlx_destroy_image(r->mlx, r->txt_d[WE].img);
        mlx_destroy_window(r->mlx, r->mlx_win);
        free_tab(r->map.map, charlen(r->map.map));
        system("pkill ffplay");
        exit(1);
    }
    else if(keycode == A)
    {   
        r->player.pos.x += 1 * ((float)(cos(r->player.pdir_v + PI/2)));
        r->player.pos.y += 1 * ((float)(sin(r->player.pdir_v + PI/2)));
        //if ((int)r->player.pos.x % 64 == 0)
        //    r->player.pos.x += 0.5 * ((float)(cos(r->player.pdir_v + PI/2)));
        //if ((int)r->player.pos.y % 64 == 0)
        //    r->player.pos.y += 0.5 * ((float)(sin(r->player.pdir_v + PI/2)));
    }
    else if(keycode == W)
    {       
        r->player.pos.x += 1 * (float)(cos(r->player.pdir_v));
        r->player.pos.y += 1 * (float)(sin(r->player.pdir_v));
        //if ((int)r->player.pos.x % 64 == 0)
        //    r->player.pos.x += 0.5 * ((float)(cos(r->player.pdir_v)));
        //if ((int)r->player.pos.y % 64 == 0)
        //    r->player.pos.y += 0.5 * ((float)(sin(r->player.pdir_v)));
    }   
    else if(keycode == S || r->coa == 1)
    {
        r->player.pos.x -= 1 * ((float)(cos(r->player.pdir_v)));
        r->player.pos.y -= 1 * ((float)(sin(r->player.pdir_v)));
        //if ((int)r->player.pos.x % 64 == 0)
        //    r->player.pos.x -= 0.5 * ((float)(cos(r->player.pdir_v)));
        //if ((int)r->player.pos.y % 64 == 0)
        //    r->player.pos.y -= 0.5 * ((float)(sin(r->player.pdir_v)));
    }
    else if(keycode == D)
    {
        r->player.pos.x += 1 * ((float)(cos(r->player.pdir_v - PI/2)));
        r->player.pos.y += 1 * ((float)(sin(r->player.pdir_v - PI/2)));
        //if ((int)r->player.pos.x % 64 == 0)
        //    r->player.pos.x += 0.5 * ((float)(cos(r->player.pdir_v - PI/2)));
        //if ((int)r->player.pos.y % 64 == 0)
        //    r->player.pos.y += 0.5 * ((float)(sin(r->player.pdir_v - PI/2)));
    }
    else if(keycode == R_AR)
    {
        r->player.pdir -= 0.0174533;
        if(r->player.pdir < 0)
		{
			r->player.pdir += 2 * PI;
		}
        r->player.pdir_v -= 0.0174533;
        if(r->player.pdir_v < 0)
		{
            r->player.pdir_v += 2 * PI;
		}

    }
    else if(keycode == L_AR)
    {
       r->player.pdir += 0.0174533;
        if(r->player.pdir > 2 * PI)
		{
			r->player.pdir -= 2 * PI;
		}
        r->player.pdir_v += 0.0174533;
        if(r->player.pdir_v > 2 * PI)
		{
			r->player.pdir_v -= 2 * PI;
		}
    }
    return(0);
}

/*void my_draw_line_fov(t_runtime *r)
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