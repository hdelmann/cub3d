/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering3D.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:37:55 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 02:51:02 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	calort(void *param)
{
	t_runtime	*r;

	r = param;
	if (r->line.ort == VER)
	{
		if (r->line.rad_fov > PI && r->line.rad_fov <= 2 * PI)
			r->line.ort2 = S;
		else if (r->line.rad_fov >= 0 && r->line.rad_fov < PI)
			r->line.ort2 = N;
	}
	else if (r->line.ort == HOR)
	{
		if ((r->line.rad_fov <= PI / 2 && r->line.rad_fov > 0)
			|| (r->line.rad_fov >= 3 * PI / 2 && r->line.rad_fov < 2 * PI))
			r->line.ort2 = O;
		else if (r->line.rad_fov >= PI / 2 && r->line.rad_fov <= 3 * PI / 2)
			r->line.ort2 = E;
	}
}

void	calcul_board(t_runtime *r)
{
	float	dir;
	float	dist;
	int		x;
	t_point	endinter;

	dir = 3 * PI / 4 - 0.1;
	x = 0;
	while (x <= 8)
	{
		endinter = calcul_inter2(r, dir);
		dist = calucl_dist(r->player.pos.x, endinter.x, r->player.pos.y,
				endinter.y) * cos(dir);
		if (dist < 0)
			dist = -dist;
		dir += PI / 6;
		if (dist < 2.3)
		{
			printf("Error: Out of bounds\n");
			exit(1);
		}
		x++;
	}
}

void	playerrendering_3d(void *param, float xray)
{
	t_runtime	*r;
	float		height;

	r = param;
	calcul_board(r);
	if (r->line.dist < 1.5)
	{
		printf("Error: Out of bounds\n");
		exit(1);
	}
	height = fabs((64.0 / r->line.dist) * (960.0 / tan(30.0)));
	r->start_y = 540.0 - (height / 2.0);
	r->end_y = 540.0 + (height / 2.0);
	if (r->start_y < 0)
		r->start_y = 0;
	if (r->end_y > HEIGHT)
		r->end_y = height;
	draw_textured_wall(r, txt_wall_ort(r, r->start_y, r->end_y), height, xray);
}
