/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering3D.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:37:55 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/26 19:21:51 by jgirard-         ###   ########.fr       */
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

void	playerrendering_3d(void *param, float xray)
{
	t_runtime	*r;
	float		height;

	r = param;
	if (r->line.dist <= 1.0)
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
