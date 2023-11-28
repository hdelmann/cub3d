/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_line2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 02:05:46 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 02:14:18 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

t_point	calcul_wall1(float dir, t_point wall, t_point play, t_runtime *r)
{
	if (dir > r->teta)
	{
		if (dir > 3 * PI / 2 && dir < 2 * PI)
			wall = calcul_1(wall, play, dir, r);
		else if (dir > PI && dir < 3 * PI / 2)
			wall = calcul_2(wall, play, dir, r);
		else if (dir > PI / 2 && dir < PI)
			wall = calcul_3(wall, play, dir, r);
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
	return (wall);
}

t_point	calcul_wall2(float dir, t_point wall, t_point play, t_runtime *r)
{
	if (dir > r->teta2)
	{
		if (dir > 3 * PI / 2 && dir < 2 * PI)
			wall = calcul_12(wall, play, dir, r);
		else if (dir > PI && dir < 3 * PI / 2)
			wall = calcul_22(wall, play, dir, r);
		else if (dir > PI / 2 && dir < PI)
			wall = calcul_32(wall, play, dir, r);
		else
			wall = calcul_42(wall, play, dir, r);
	}
	else
	{
		if (dir > 3 * PI / 2 && dir < 2 * PI)
			wall = calcul_22(wall, play, dir, r);
		else if (dir > PI && dir < 3 * PI / 2)
			wall = calcul_32(wall, play, dir, r);
		else if (dir > PI / 2 && dir < PI)
			wall = calcul_42(wall, play, dir, r);
		else
			wall = calcul_12(wall, play, dir, r);
	}
	return (wall);
}

t_point	calcul_inter(t_runtime *r, float dir)
{
	t_point	play;
	t_point	wall;

	play.x = r->player.pos.x;
	play.y = r->player.pos.y;
	r->line.x_wall = play.x / CASE_SIZE;
	r->line.y_wall = play.y / CASE_SIZE;
	wall.x = 0;
	wall.y = 0;
	while (r->map.map[(int)r->line.y_wall][(int)r->line.x_wall] != '1')
	{
		r->teta = calcul_teta(dir, play, r->line.x_wall, r->line.y_wall);
		wall = calcul_wall1(dir, wall, play, r);
		play.x = wall.x;
		play.y = wall.y;
	}
	return (wall);
}

t_point	calcul_inter2(t_runtime *r, float dir)
{
	t_point	play;
	t_point	wall;

	play.x = r->player.pos.x;
	play.y = r->player.pos.y;
	r->line.x_wall2 = play.x / CASE_SIZE;
	r->line.y_wall2 = play.y / CASE_SIZE;
	wall.x = 0;
	wall.y = 0;
	while (r->map.map[(int)r->line.y_wall2][(int)r->line.x_wall2] != '1')
	{
		r->teta2 = calcul_teta(dir, play, r->line.x_wall2, r->line.y_wall2);
		wall = calcul_wall2(dir, wall, play, r);
		play.x = wall.x;
		play.y = wall.y;
	}
	return (wall);
}
