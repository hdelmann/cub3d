#include "../includes/Cub3D.h"



void calcul_line_interx(void *param, float x0, float y0)
{
    t_runtime *r;
    r = param;
    r->line.start.x = r->player.pos.x - 5;
    r->line.start_v.x = r->player.pos.x - 5;
    r->line.start.y = r->player.pos.y + 5;
    r->line.start_v.y = r->player.pos.y + 5;
    float tmpx = x0;
    float tmpy = y0;
    r->line.end.x = r->line.start.x;
    r->line.end.y = r->line.start.y;
    while (r->map.map[(int)r->line.end.y / CASE_SIZE][(int)r->line.end.x / CASE_SIZE] != '1')
    {
        if (r->line.rad_raystart >= PI && r->line.rad_raystart <= 2 * PI)
        {
            r->line.end.y = floor(tmpy / CASE_SIZE) * CASE_SIZE + CASE_SIZE;
        }
        else if (r->line.rad_raystart >= 0 && r->line.rad_raystart <= PI)
        {
            r->line.end.y = floor(tmpy / CASE_SIZE) * CASE_SIZE - 1;
        }
        else
        {
             break;
        }
        r->line.end.x = tmpx + (tmpy - r->line.end.y) / tan(r->line.rad_raystart);
        tmpx = r->line.end.x;
        tmpy = r->line.end.y;
        if ((int)(tmpy / CASE_SIZE) >= charlen(r->map.map) || (int)(tmpx / CASE_SIZE) >= my_strlen(r->map.map[(int)(tmpy / CASE_SIZE)]) || (int)tmpx <= 0 || (int)tmpy <= 0)
        {
            r->line.end.x = r->line.start.x;
            r->line.end.y = r->line.start.y;
            break;
        }
    }
}

void calcul_line_intery(void *param, float x0, float y0)
{
    t_runtime *r;
    r = param;
    r->line.start.x = r->player.pos.x - 5;
    r->line.start_v.x = r->player.pos.x - 5;
    r->line.start.y = r->player.pos.y + 5;
    r->line.start_v.y = r->player.pos.y + 5;
    float tmpx = x0;
    float tmpy = y0;
    r->line.end_v.x = r->line.start.x;
    r->line.end_v.y = r->line.start.y;
    while (r->map.map[(int)r->line.end_v.y / CASE_SIZE][(int)r->line.end_v.x / CASE_SIZE] != '1')
    {
        if ((r->line.rad_raystart< PI / 2 && r->line.rad_raystart > 0) || (r->line.rad_raystart > 3 * PI/2))
        {
            r->line.end_v.x = floor(tmpx / CASE_SIZE) * CASE_SIZE +CASE_SIZE;
        }
        else if (r->line.rad_raystart > PI/ 2 && r->line.rad_raystart < 3 * PI/2)
        {
            r->line.end_v.x = floor(tmpx / CASE_SIZE) * CASE_SIZE - 1;
        }
        else {
             break;
        }
        r->line.end_v.y = tmpy + (tmpx - r->line.end_v.x) * tan(r->line.rad_raystart);
        tmpx = r->line.end_v.x;
        tmpy = r->line.end_v.y;
        if ((int)tmpx <= 0 || (int)tmpy <= 0 || (int)(tmpy / CASE_SIZE) >= charlen(r->map.map) || (int)(tmpx / CASE_SIZE) >= my_strlen(r->map.map[(int)tmpy / CASE_SIZE]))
        {
            r->line.end_v.x = r->line.start.x;
            r->line.end_v.y = r->line.start.y;
            break;
        }
    }
}

void calcul_line_fovy(void *param)
{
    t_runtime *r;
    r = param;
    r->line.start_fov.x = r->player.pos.x - 5;
    r->line.start_fov.x = r->player.pos.x - 5;
    float tmpx = r->line.start_fov.x;
    float tmpy = r->line.start_fov.y;
    r->line.end_fov.x = r->line.start_fov.x;
    r->line.end_fov.y = r->line.start_fov.y;
    /*while (r->line.rad_fov >= 2 * PI)
    {
        r->line.rad_fov -= 2 * PI;
    }
    while (r->line.rad_fov < 0)
    {
        r->line.rad_fov += 2 * PI;
    } */ 
    while (r->map.map[(int)r->line.end_fov.y / CASE_SIZE][(int)r->line.end_fov.x / CASE_SIZE] != '1')
    {
        if ((r->line.rad_fov <= PI / 2 && r->line.rad_fov >= 0) || (r->line.rad_fov >= 3 * PI/2 && r->line.rad_fov <= 2 *PI))
        {
            r->line.end_fov.x = floor(tmpx / CASE_SIZE) * CASE_SIZE +CASE_SIZE;
        }
        else if (r->line.rad_fov >= PI/ 2 && r->line.rad_fov <= 3 * PI/2)
        {
            r->line.end_fov.x = floor(tmpx / CASE_SIZE) * CASE_SIZE - 1;
        }
        else {
            //printf("oui = %f\n", r->line.rad_fov);
             break;
        }
        r->line.end_fov.y = tmpy + (tmpx - r->line.end_fov.x) * tan(r->line.rad_fov);
        tmpx = r->line.end_fov.x;
        tmpy = r->line.end_fov.y;
        if ((int)tmpx <= 0 || (int)tmpy <= 0 || (int)(tmpy / CASE_SIZE) >= charlen(r->map.map) ||(int)(tmpx / CASE_SIZE) >= my_strlen(r->map.map[(int)tmpy / CASE_SIZE]))
        {
            //printf("je lvaais dit vrm\n");
            r->line.end_fov.x = r->line.start_fov.x;
            r->line.end_fov.y = r->line.start_fov.y;
            break;
        }
    }
}

void calcul_line_fovx(void *param)
{
    t_runtime *r;
    r = param;
    r->line.start_fov.x = r->player.pos.x - 5;
    r->line.start_fov.y = r->player.pos.y + 5;
    float tmpx = r->line.start_fov.x;
    float tmpy = r->line.start_fov.y;
    r->line.end_fov2.x = r->line.start_fov.x;
    r->line.end_fov2.y = r->line.start_fov.y;
    while (r->map.map[(int)r->line.end_fov2.y / CASE_SIZE][(int)r->line.end_fov2.x / CASE_SIZE] != '1')
    {
        if (r->line.rad_fov >= PI && r->line.rad_fov <= 2 * PI)
        {
            r->line.end_fov2.y = floor(tmpy / CASE_SIZE) * CASE_SIZE + CASE_SIZE;
        }
        else if (r->line.rad_fov >= 0 && r->line.rad_fov <= PI)
        {
            r->line.end_fov2.y = floor(tmpy / CASE_SIZE) * CASE_SIZE - 1;
        }
        else
        {
             break;
        }
        //printf("rad3 = %f\n", r->line.rad_in);
        r->line.end_fov2.x = tmpx + (tmpy - r->line.end_fov2.y) / tan(r->line.rad_fov);
        tmpx = r->line.end_fov2.x;
        tmpy = r->line.end_fov2.y;
        if ((int)(tmpx / CASE_SIZE) >= my_strlen(r->map.map[(int)(tmpy / CASE_SIZE)]) || (int)tmpx <= 0 || (int)tmpy <= 0)
        {
            //printf("je lvaais dit\n");
            r->line.end_fov2.x = r->line.start_fov.x;
            r->line.end_fov2.y = r->line.start_fov.y;
            break;
        }
    }
}

/*void calcul_border(t_runtime *r)
{
    t_point posborder;

    posborder.x = r->player.pos.x / CASE_SIZE;
    posborder.y = r->player.pos.y / CASE_SIZE;

}*/