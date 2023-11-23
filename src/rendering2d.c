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
                    my_mlx_put_pixel(r, l, k, get_rgba(105, 105, 105, 255));
                }
            }
            if (r->map.map[i][j] == '1')
            {
                for (int k = y + 2; k <= y + CASE_SIZE; k++) {
                    for (int l = x - 2; l >= x - CASE_SIZE; l--) {
                         my_mlx_put_pixel(r, l, k, get_rgba(255, 255, 255, 255));
                    }
                }
            }
            else if (r->map.map[i][j] != '1')
            {
                for (int k = y + 2; k <= y + CASE_SIZE; k++) {
                    for (int l = x - 2; l >= x - CASE_SIZE; l--) {
                        my_mlx_put_pixel(r, l, k, get_rgba(0, 0, 0, 255));
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

float *ft_colision(t_runtime *r, float x0, float y0)
{
    float tmp_rad;
    float k = 0;
    float *dist_tab;
    //float dist;
    r->line.rad_raystart= r->player.pdir - r->player.FOV/4;
    tmp_rad = r->line.rad_raystart;
    dist_tab = malloc(sizeof(float) + 1);
    dist_tab[0] = -1;
    while (k < 6)
    {
        dist_tab = myReallocfloat(dist_tab, k + 2);
        //printf("i = %d\n", i);
        tmp_rad = r->line.rad_raystart;
        if (r->line.rad_raystart < 0)
        {
            r->line.rad_fov += 2 * PI; 
        }
        else if (r->line.rad_raystart > (2 * PI))
        {
            r->line.rad_fov -= 2 * PI; 
        }
        //printf("rad2 = %f\n", r->line.rad_in);
        calcul_line_interx(r, x0, y0);
        calcul_line_intery(r, x0, y0);
        if (r->line.end.x == r->line.start.x && r->line.end.y == r->line.start.y)
        { 
            r->line.end.x = r->line.end_v.x;
            r->line.end.y = r->line.end_v.y;
        }
        if ((r->line.end_v.x == r->line.start_v.x && r->line.end_v.y == r->line.start_v.y))
        {}
        else if  (sqrt(((r->line.end.x - r->line.start.x) * (r->line.end.x - r->line.start.x)) + ((r->line.end.y - r->line.start.y) * (r->line.end.y - r->line.start.y))) > sqrt(((r->line.end_v.x - r->line.start_v.x) * (r->line.end_v.x - r->line.start_v.x)) + ((r->line.end_v.y - r->line.start_v.y) * (r->line.end_v.y - r->line.start_v.y))))
        {
            r->line.end.x = r->line.end_v.x;
            r->line.end.y = r->line.end_v.y;
        }
        r->line.end_def.x = r->line.end.x;
        r->line.end_def.y = r->line.end.y;
        //printf("y = %f, x = %f\n ", r->line.end_defov.y, r->line.end_defov.x);
       // my_draw_line(r);
        r->line.rad_raystart = tmp_rad;
        r->line.rad_raystart += r->player.FOV/8;
        //dist = calucl_dist(x0, r->line.end_def.x, y0, r->line.end_def.y) * cos(r->line.rad_raystart - r->player.pdir); 
        dist_tab[(int)k] = calucl_dist(x0, r->line.end_def.x, y0, r->line.end_def.y) * cos(r->line.rad_raystart - r->player.pdir);
        //
       // printf("distt = %f\n", r->line.tab_dist[(int)k]);
        k++;
        dist_tab[(int)k] = -1;
    }
    return(dist_tab);
}

int playerendering2d(t_runtime  *r)
{
    //fillcubeborder(r);
    /*for (int i = r->player.pos.y + 1; i < r->player.pos.y + PLAYER_SIZE; i++) {
        for (int j = r->player.pos.x  - 1; j > r->player.pos.x - PLAYER_SIZE; j--) {
            my_mlx_put_pixel(r->img, j, i, get_rgba(255, 0, 0, 255));
        }
    }*/
     //printf("SOMEONE KILL ME\n");
    //mlx_hook(r->mlx_win, 2, 1L<<0, my_keyhook, &r);
   // mlx_key_hook(r->mlx_win, my_keyhook, r);
  // mlx_hook(r->mlx_win, 2, 1L<<0, my_keyhook, r);
    //mlx_key_hook(r->mlx_win, my_keyhook, r);
    int i;
    int j;
    for (i = 0; i < WIDTH; i++) {
        for (j = 0 ; j < HEIGHT/2; j++) {
            my_mlx_put_pixel(r, i, j, get_rgba(r->color[CEIL].c_red, r->color[CEIL].c_green, r->color[CEIL].c_blue, 255));
        }
    }
    for (i = 0;i < WIDTH; i += 2) {
        for (j = HEIGHT/2 ;j < HEIGHT; j++) {
            my_mlx_put_pixel(r, i, j, get_rgba(255, 0, 0, 255));
        }
    }
    for (i = 1;i < WIDTH; i += 2) {
        for (j = HEIGHT/2 ;j < HEIGHT; j++) {
            my_mlx_put_pixel(r, i, j, get_rgba(r->color[FLR].c_red, r->color[FLR].c_green, r->color[FLR].c_blue, 255));
        }
    }
    for (j = HEIGHT/2;j < HEIGHT; j += 2) {
        for (i = WIDTH ;i < WIDTH; i++) {
            my_mlx_put_pixel(r, i, j, get_rgba(255, 0, 0, 255));
        }
    }
    fov_rendering(r);
    mlx_put_image_to_window(r->mlx, r->mlx_win, r->img.img, 0, 0);
    return(0);
}

void fov_rendering(t_runtime *r)
{
    float tmp_rad;
    float i = 0;
    t_point endinter;
    int x = 0;
    r->line.rad_fov= r->player.pdir_v + r->player.FOV/2;
    tmp_rad = r->line.rad_fov;
    while (tmp_rad >= r->player.pdir_v - r->player.FOV/2)
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
       // my_draw_line(r);
        //r->line.rad_fov = tmp_rad;
        //fflush(stdout);
        //r->line.rad_fov -= r->player.FOV / WIDTH;
        r->line.rad_fov = tmp_rad;
        r->line.rad_fov -= 0.0005457;
        r->line.dist = calucl_dist(r->player.pos.x, endinter.x, r->player.pos.y, endinter.y) * cos(r->line.rad_fov - r->player.pdir_v);
        playerrendering3D(r, x);
        i++;
        x++;
    }
}

void fov_renderingg(t_runtime *r)
{
    float tmp_rad;
    float i = 0;
    t_point endinter;
    float a =  -PI / 7;
    int x = 0;

    while (x < WIDTH)
    {
        tmp_rad = r->player.pdir + a;
        if (tmp_rad < 0)
        {
            tmp_rad += 2 * PI; 
        }
        else if (tmp_rad > 2 * PI)
        {
            tmp_rad -= 2 * PI;
        }
        printf("a = %f tmprad = %f xpl = %d et yplay = %d == %c\n", a, tmp_rad, (int)r->player.pos.x / 64, (int)r->player.pos.y / 64, r->map.map[(int)r->player.pos.y / 64][(int)r->player.pos.x / 64]);
        endinter = calcul_inter(r, tmp_rad);
        r->line.end_fov.x = endinter.x;
        r->line.end_fov.y = endinter.y;
        printf("x = %f, y = %f\n ", endinter.x, endinter.y);
       // my_draw_line(r);
        //r->line.rad_fov = tmp_rad;
        //fflush(stdout);
        //r->line.rad_fov -= r->player.FOV / WIDTH;
        r->line.rad_fov = tmp_rad;
        r->line.dist = calucl_dist(r->player.pos.x, endinter.x, r->player.pos.y, endinter.y) * cos(a);
        playerrendering3D(r, x);
        printf("tim\n");
        a += ((2 * PI / 7) / (WIDTH));
        i++;
        x++;
    }
}

//void fov_rendering_2(t_runtime *r)
//{
//    float tmp_rad;
//    float i = 0;
//    t_point endinter;
//    r->line.rad_fov= r->player.pdir_v + r->player.FOV/2;
//    tmp_rad = r->line.rad_fov;
//    while (tmp_rad >= r->player.pdir_v - r->player.FOV/2)
//    {
//        //r->line.ort = HOR;
//        //printf("i = %d\n", i);
//        tmp_rad = r->line.rad_fov;
//        if (r->line.rad_fov < 0)
//        {
//            r->line.rad_fov += 2 * PI; 
//        }
//        else if (r->line.rad_fov > 2 * PI)
//        {
//            r->line.rad_fov -= 2 * PI;
//        }
//        printf("tmprad = %f xpl = %d et yplay = %d == %c\n", r->line.rad_fov, (int)r->player.pos.x / 64, (int)r->player.pos.y / 64, r->map.map[(int)r->player.pos.y / 64][(int)r->player.pos.x / 64]);
//        endinter = calcul_inter(r, r->line.rad_fov);
//        r->line.end_defov.x = endinter.x;
//        r->line.end_defov.y = endinter.y;
//        printf("y = %f, x = %f\n\n", r->line.end_defov.y, r->line.end_defov.x);
//       // my_draw_line(r);
//        r->line.rad_fov = tmp_rad;
//        fflush(stdout);
//        r->line.rad_fov -= r->player.FOV / WIDTH;
//        r->line.dist = calucl_dist(r->player.pos.x, r->line.end_defov.x, r->player.pos.y, r->line.end_defov.y) * cos(r->line.rad_fov - r->player.pdir_v); 
//        playerrendering3D(r, i);
//        printf("tim\n");
//        i++;
//    }
//}
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
        system("pkill ffplay");
        exit(1);
    }
    if(keycode == A)
    {   
        r->player.pos.x -= 0.5 * ((float)(cos(r->player.pdir_v - PI/2)));
        r->player.pos.y -= 0.5 * ((float)(sin(r->player.pdir_v - PI/2)));
    }
    if(keycode == W)
    {       
        r->player.pos.x += 0.5 * (float)(cos(r->player.pdir_v));
        r->player.pos.y += 0.5 * (float)(sin(r->player.pdir_v));
    }   
    if(keycode == S || r->coa == 1)
    {
        r->player.pos.x -= 0.5 * ((float)(cos(r->player.pdir_v)));
        r->player.pos.y -= 0.5 * ((float)(sin(r->player.pdir_v)));
    }
    if(keycode == D)
    {
        r->player.pos.x += 0.5 * ((float)(cos(r->player.pdir_v - PI/2)));
        r->player.pos.y += 0.5 * ((float)(sin(r->player.pdir_v - PI/2)));
    }
    if(keycode == R_AR)
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
    if(keycode == L_AR)
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
        my_mlx_put_pixel(r, roundf((int)xsta), roundf((int)ysta), get_rgba(0, 255, 255, 255));
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