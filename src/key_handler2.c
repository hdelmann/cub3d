/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 02:11:32 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 02:50:20 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	my_keyhook(int keycode, t_runtime *r)
{
	if (keycode == ESC)
		destroy_all(r);
	else if (keycode == A)
	{
		r->player.pos.x += 1 * ((float)(cos(r->player.pdir_v + PI / 2)));
		r->player.pos.y += 1 * ((float)(sin(r->player.pdir_v + PI / 2)));
	}
	else if (keycode == W)
	{
		r->player.pos.x += 1 * (float)(cos(r->player.pdir_v));
		r->player.pos.y += 1 * (float)(sin(r->player.pdir_v));
	}
	else if (keycode == S || r->coa == 1)
	{
		r->player.pos.x -= 1 * ((float)(cos(r->player.pdir_v)));
		r->player.pos.y -= 1 * ((float)(sin(r->player.pdir_v)));
	}
	else if (keycode == D)
		d_handler(r);
	else if (keycode == R_AR)
		r_arrow_handle(r);
	else if (keycode == L_AR)
		l_arrow_handle(r);
	return (0);
}

void	fov_rendering(t_runtime *r)
{
	float	tmp_rad;
	t_point	endinter;
	int		x;

	x = 0;
	r->line.rad_fov = r->player.pdir + r->player.fov / 2;
	tmp_rad = r->line.rad_fov;
	p_posini(r);
	while (tmp_rad >= r->player.pdir - r->player.fov / 2)
	{
		tmp_rad = r->line.rad_fov;
		while (r->line.rad_fov < 0)
			r->line.rad_fov += 2 * PI;
		while (r->line.rad_fov > 2 * PI)
			r->line.rad_fov -= 2 * PI;
		endinter = calcul_inter(r, r->line.rad_fov);
		r->line.end_fov.x = endinter.x;
		r->line.end_fov.y = endinter.y;
		r->line.rad_fov = tmp_rad;
		r->line.rad_fov -= 0.0005457;
		r->line.dist = calucl_dist(r->player.pos.x, endinter.x, r->player.pos.y,
				endinter.y) * cos(r->line.rad_fov - r->player.pdir_v);
		playerrendering_3d(r, x);
		x++;
	}
}
