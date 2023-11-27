/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:00:43 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/26 21:00:51 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

float calcul_teta(float dir, t_point play, int Xwall, int Ywall)
{
    float teta;

    if (dir > 3 * PI / 2 && dir < 2 * PI)
        teta = 2 * PI + atan(((Ywall * CASE_SIZE) - play.y) / (((Xwall + 1) * CASE_SIZE) - play.x));
    else if (dir > PI && dir < 3 * PI / 2)
        teta = PI + atan(((Ywall * CASE_SIZE) - play.y) / ((Xwall * CASE_SIZE) - play.x));
    else if (dir > PI / 2 && dir < PI)
        teta = PI + atan((((Ywall + 1) * CASE_SIZE) - play.y) / ((Xwall * CASE_SIZE) - play.x));
    else
        teta = atan((((Ywall + 1) * CASE_SIZE) - play.y) / (((Xwall + 1) * CASE_SIZE) - play.x));
    return(teta);
}

t_point calcul_1(t_point wall, t_point play, float dir, t_runtime *r)
{
    r->line.ort = O;
    wall.x = (r->line.Xwall + 1) * CASE_SIZE;
    if (tan(dir) == 0 || dir == PI / 2 || dir == 3 * PI / 2)
        wall.y = play.y;
    else 
        wall.y = play.y + (wall.x - play.x) * tan(dir);
    r->line.Xwall += 1;
    return(wall);
}

t_point calcul_2(t_point wall, t_point play, float dir, t_runtime *r)
{
    r->line.ort = N;
    wall.y = r->line.Ywall * CASE_SIZE;
    if (tan(dir) == 0|| dir == PI / 2 || dir == 3 * PI / 2)
        wall.x = play.x;
    else 
        wall.x = play.x + (wall.y - play.y) / tan(dir);
    r->line.Ywall -= 1;
    return(wall);
}

t_point calcul_3(t_point wall, t_point play, float dir, t_runtime *r)
{
    r->line.ort = E;
    wall.x = r->line.Xwall * CASE_SIZE;
    if (tan(dir) == 0 || dir == PI / 2 || dir == 3 * PI / 2)
        wall.y = play.y;
    else 
        wall.y = play.y + (wall.x - play.x) * tan(dir);
    r->line.Xwall -= 1;
    return(wall);
}

t_point calcul_4(t_point wall, t_point play, float dir, t_runtime *r)
{
    r->line.ort = S;
    wall.y = (r->line.Ywall + 1) * CASE_SIZE;
    if(tan(dir) == 0 || dir == PI / 2 || dir == 3 * PI / 2)
        wall.x = play.x;
    else
        wall.x = play.x + (wall.y - play.y) / tan(dir);
    r->line.Ywall += 1;
    return(wall);
}


t_point calcul_wall1(float dir, t_point wall, t_point play, t_runtime *r, float teta)
{
    if (dir > teta)
    {
        if (dir > 3 * PI / 2 && dir < 2 * PI)
            wall = calcul_1(wall, play, dir, r);
        else if (dir > PI && dir < 3 * PI/2)
            wall = calcul_2(wall, play, dir, r);
        else if (dir > PI / 2 && dir < PI)
            wall = calcul_3(wall, play, dir,  r);
        else
            wall = calcul_4(wall, play, dir, r);
    }
    else
    {
        if (dir > 3 * PI / 2 && dir < 2 * PI)
            wall = calcul_2(wall, play, dir, r);
        else if (dir > PI && dir < 3 * PI / 2)
            wall = calcul_3(wall, play, dir, r);
	    else if (dir > PI / 2 && dir < PI)
            wall = calcul_4(wall, play, dir, r);
        else
            wall = calcul_1(wall, play, dir, r);
    }
    return(wall);
}

t_point calcul_inter(t_runtime *r, float dir)
{
    t_point play;
    t_point wall;
    play.x = r->player.pos.x;
    play.y = r->player.pos.y;
    float teta;

    r->line.Xwall = play.x / CASE_SIZE;
    r->line.Ywall = play.y / CASE_SIZE;
    wall.x = 0;
    wall.y = 0;
    while (r->map.map[(int)r->line.Ywall][(int)r->line.Xwall] != '1')
    {
        teta = calcul_teta(dir, play, r->line.Xwall, r->line.Ywall);
        wall = calcul_wall1(dir, wall, play, r, teta);
        play.x = wall.x;
        play.y = wall.y;
    }
    return(wall);
}