/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_line3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 02:05:46 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 02:14:18 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

t_point	calcul_12(t_point wall, t_point play, float dir, t_runtime *r)
{
	wall.x = (r->line.x_wall2 + 1) * CASE_SIZE;
	if (tan(dir) == 0 || dir == PI / 2 || dir == 3 * PI / 2)
		wall.y = play.y;
	else
		wall.y = play.y + (wall.x - play.x) * tan(dir);
	r->line.x_wall2 += 1;
	return (wall);
}

t_point	calcul_22(t_point wall, t_point play, float dir, t_runtime *r)
{
	wall.y = r->line.y_wall2 * CASE_SIZE;
	if (tan(dir) == 0 || dir == PI / 2 || dir == 3 * PI / 2)
		wall.x = play.x;
	else
		wall.x = play.x + (wall.y - play.y) / tan(dir);
	r->line.y_wall2 -= 1;
	return (wall);
}

t_point	calcul_32(t_point wall, t_point play, float dir, t_runtime *r)
{
	wall.x = r->line.x_wall2 * CASE_SIZE;
	if (tan(dir) == 0 || dir == PI / 2 || dir == 3 * PI / 2)
		wall.y = play.y;
	else
		wall.y = play.y + (wall.x - play.x) * tan(dir);
	r->line.x_wall2 -= 1;
	return (wall);
}

t_point	calcul_42(t_point wall, t_point play, float dir, t_runtime *r)
{
	wall.y = (r->line.y_wall2 + 1) * CASE_SIZE;
	if (tan(dir) == 0 || dir == PI / 2 || dir == 3 * PI / 2)
		wall.x = play.x;
	else
		wall.x = play.x + (wall.y - play.y) / tan(dir);
	r->line.y_wall2 += 1;
	return (wall);
}
