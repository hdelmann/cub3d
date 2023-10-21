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

float *ft_colision(t_runtime *r, float x0, float y0)
{
    float tmp_rad;
    float k = 0;
    float *dist_tab;
    //float dist;
    r->line.rad_raystart= r->player.pdir - r->player.FOV/4;
    tmp_rad = r->line.rad_raystart;
    dist_tab = malloc(sizeof(float));
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
    int i;
    int j;
    for (i = 0; i < WIDTH; i++) {
        for (j = 0 ; j < HEIGHT/2; j++) {
            my_mlx_put_pixel(r->img, i, j, get_rgba(20, 20, 20, 255));
        }
    }
    for (i = 0;i < WIDTH; i += 2) {
        for (j = HEIGHT/2 ;j < HEIGHT; j++) {
            my_mlx_put_pixel(r->img, i, j, get_rgba(64, 64, 64, 255));
        }
    }
    for (i = 1;i < WIDTH; i += 2) {
        for (j = HEIGHT/2 ;j < HEIGHT; j++) {
            my_mlx_put_pixel(r->img, i, j, get_rgba(128, 128, 128, 255));
        }
    }
    for (j = HEIGHT/2;j < HEIGHT; j += 2) {
        for (i = WIDTH ;i < WIDTH; i++) {
            my_mlx_put_pixel(r->img, i, j, get_rgba(128, 128, 128, 255));
        }
    }

    
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
        r->line.ort = HOR;
        //printf("i = %d\n", i);
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
            r->line.ort = VER;
            r->line.end_fov.x = r->line.end_fov2.x;
            r->line.end_fov.y = r->line.end_fov2.y;
        }
        if ((r->line.end_fov2.x == r->line.start_fov.x && r->line.end_fov2.y == r->line.start_fov.y))
        {}
        else if  (sqrt(((r->line.end_fov.x - r->line.start_fov.x) * (r->line.end_fov.x - r->line.start_fov.x)) + ((r->line.end_fov.y - r->line.start_fov.y) * (r->line.end_fov.y - r->line.start_fov.y))) > sqrt(((r->line.end_fov2.x - r->line.start_fov.x) * (r->line.end_fov2.x - r->line.start_fov.x)) + ((r->line.end_fov2.y - r->line.start_fov.y) * (r->line.end_fov2.y - r->line.start_fov.y))))
        {
            r->line.ort = VER;
            r->line.end_fov.x = r->line.end_fov2.x;
            r->line.end_fov.y = r->line.end_fov2.y;
        }
        r->line.end_defov.x = r->line.end_fov.x;
        r->line.end_defov.y = r->line.end_fov.y;
       // printf("y = %f, x = %f\n ", r->line.end_defov.y, r->line.end_defov.x);
       // my_draw_line(r);
        r->line.rad_fov = tmp_rad;
        r->line.rad_fov += 0.0005457;
        r->line.dist = calucl_dist(r->line.start_fov.x, r->line.end_defov.x, r->line.start_fov.y, r->line.end_defov.y) * cos(r->line.rad_fov - r->player.pdir_v); 
        playerrendering3D(r, i);
        i++;
        }
}
//faire un tableau pour tester les deplacement car sinon ca peut buger giltch hors map
void my_keyhook(mlx_key_data_t keydata, void *param)
{
    t_runtime *r;
    float *dist_tab;
    r = param;
    (void)keydata;
    if(mlx_is_key_down(r->mlx, MLX_KEY_D))
    {   
        /*if(r->player.dir == DIR_W)
            r->player.pdir += PI/2;
        if(r->player.dir == DIR_S)
            r->player.pdir -= PI/2;        
        if(r->player.dir == DIR_A)
            r->player.pdir -= PI;
        r->player.dir = DIR_D;*/
        r->player.pdir += PI/2;
        dist_tab = ft_colision(r, r->line.start.x + ((float)(cos(r->player.pdir))), r->line.start.y - ((float)(sin(r->player.pdir))));
        r->player.pdir -= PI/2;
        if (test_dist(dist_tab, 8) == 1)
        {
            r->player.pos.x -= 0.5 * ((float)(cos(r->player.pdir - PI/2)));
            r->player.pos.y += 0.5 * ((float)(sin(r->player.pdir - PI/2)));
        }
        //free(dist_tab);
    }
    if(mlx_is_key_down(r->mlx, MLX_KEY_W))
    {
        /*if(r->player.dir == DIR_S)
            r->player.pdir -= PI;
        if(r->player.dir == DIR_A)
            r->player.pdir += PI/2;        
        if(r->player.dir == DIR_D)
            r->player.pdir -= PI/2;
        r->player.dir = DIR_W;*/
        dist_tab = ft_colision(r, r->line.start.x + ((float)(cos(r->player.pdir_v))), r->line.start.y - ((float)(sin(r->player.pdir_v))));
        if (test_dist(dist_tab, 8) == 1)
        {
            
            r->player.pos.x += 0.5 * (float)(cos(r->player.pdir_v));
            r->player.pos.y -= 0.5 * (float)(sin(r->player.pdir_v));
        }
       // free(dist_tab);
    }   
    if(mlx_is_key_down(r->mlx, MLX_KEY_S))
    {
        /*if(r->player.dir == DIR_W)
            r->player.pdir += PI;
        if(r->player.dir == DIR_A)
            r->player.pdir -= PI/2;        
        if(r->player.dir == DIR_D)
            r->player.pdir += PI/2;
        r->player.dir = DIR_S;*/
        r->player.pdir += PI;
        dist_tab = ft_colision(r, r->line.start.x + ((float)(cos(r->player.pdir))), r->line.start.y - ((float)(sin(r->player.pdir))));
        r->player.pdir -= PI;
        if (test_dist(dist_tab, 8) == 1)
        {
            r->player.pos.x -= 0.5 * ((float)(cos(r->player.pdir)));
            r->player.pos.y += 0.5 * ((float)(sin(r->player.pdir)));
        }
    }
    if(mlx_is_key_down(r->mlx, MLX_KEY_A))
    {
        /*if(r->player.dir == DIR_W)
            r->player.pdir -= PI/2;
        if(r->player.dir == DIR_S)
            r->player.pdir += PI/2;        
        if(r->player.dir == DIR_D)
            r->player.pdir += PI;
        r->player.dir = DIR_A;*/
        r->player.pdir -= PI/2;
        dist_tab = ft_colision(r, r->line.start.x + ((float)(cos(r->player.pdir))), r->line.start.y - ((float)(sin(r->player.pdir))));
        r->player.pdir += PI/2;
        if (test_dist(dist_tab, 8) == 1)
        {
            r->player.pos.x += 0.5 * ((float)(cos(r->player.pdir - PI/2)));
            r->player.pos.y -= 0.5 * ((float)(sin(r->player.pdir - PI/2)));
        }
    }
    if(mlx_is_key_down(r->mlx, MLX_KEY_LEFT))
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
    if(mlx_is_key_down(r->mlx, MLX_KEY_RIGHT))
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