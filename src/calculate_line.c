/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 21:00:43 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 02:08:18 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

float	calcul_teta(float dir, t_point play, int x_wall, int y_wall)
{
	float	teta;

	if (dir > 3 * PI / 2 && dir < 2 * PI)
		teta = 2 * PI + atan(((y_wall * CASE_SIZE) - play.y)
				/ (((x_wall + 1) * CASE_SIZE) - play.x));
	else if (dir > PI && dir < 3 * PI / 2)
		teta = PI + atan(((y_wall * CASE_SIZE) - play.y)
				/ ((x_wall * CASE_SIZE) - play.x));
	else if (dir > PI / 2 && dir < PI)
		teta = PI + atan((((y_wall + 1) * CASE_SIZE) - play.y)
				/ ((x_wall * CASE_SIZE) - play.x));
	else
		teta = atan((((y_wall + 1) * CASE_SIZE) - play.y)
				/ (((x_wall + 1) * CASE_SIZE) - play.x));
	return (teta);
}

t_point	calcul_1(t_point wall, t_point play, float dir, t_runtime *r)
{
	r->line.ort = O;
	wall.x = (r->line.x_wall + 1) * CASE_SIZE;
	if (tan(dir) == 0 || dir == PI / 2 || dir == 3 * PI / 2)
		wall.y = play.y;
	else
		wall.y = play.y + (wall.x - play.x) * tan(dir);
	r->line.x_wall += 1;
	return (wall);
}

t_point	calcul_2(t_point wall, t_point play, float dir, t_runtime *r)
{
	r->line.ort = N;
	wall.y = r->line.y_wall * CASE_SIZE;
	if (tan(dir) == 0 || dir == PI / 2 || dir == 3 * PI / 2)
		wall.x = play.x;
	else
		wall.x = play.x + (wall.y - play.y) / tan(dir);
	r->line.y_wall -= 1;
	return (wall);
}

t_point	calcul_3(t_point wall, t_point play, float dir, t_runtime *r)
{
	r->line.ort = E;
	wall.x = r->line.x_wall * CASE_SIZE;
	if (tan(dir) == 0 || dir == PI / 2 || dir == 3 * PI / 2)
		wall.y = play.y;
	else
		wall.y = play.y + (wall.x - play.x) * tan(dir);
	r->line.x_wall -= 1;
	return (wall);
}

t_point	calcul_4(t_point wall, t_point play, float dir, t_runtime *r)
{
	r->line.ort = S;
	wall.y = (r->line.y_wall + 1) * CASE_SIZE;
	if (tan(dir) == 0 || dir == PI / 2 || dir == 3 * PI / 2)
		wall.x = play.x;
	else
		wall.x = play.x + (wall.y - play.y) / tan(dir);
	r->line.y_wall += 1;
	return (wall);
}
