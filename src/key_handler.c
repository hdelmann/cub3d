/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 02:11:32 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 14:32:34 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	close_window(int keycode, t_runtime *r)
{
	(void)keycode;
	(void)r;
	exit (1);
	return (0);
}

void	destroy_all(t_runtime *r)
{
	mlx_destroy_image(r->mlx, r->img.img);
	mlx_destroy_image(r->mlx, r->txt_d[NO].img);
	mlx_destroy_image(r->mlx, r->txt_d[EA].img);
	mlx_destroy_image(r->mlx, r->txt_d[SO].img);
	mlx_destroy_image(r->mlx, r->txt_d[WE].img);
	mlx_destroy_window(r->mlx, r->mlx_win);
	free_tab(r->map.map, charlen(r->map.map));
	exit(1);
}

void	r_arrow_handle(t_runtime *r)
{
	r->player.pdir -= 0.0174533;
	if (r->player.pdir < 0)
	{
		r->player.pdir += 2 * PI;
	}
	r->player.pdir_v -= 0.0174533;
	if (r->player.pdir_v < 0)
	{
		r->player.pdir_v += 2 * PI;
	}
}

void	l_arrow_handle(t_runtime *r)
{
	r->player.pdir += 0.0174533;
	if (r->player.pdir > 2 * PI)
	{
		r->player.pdir -= 2 * PI;
	}
	r->player.pdir_v += 0.0174533;
	if (r->player.pdir_v > 2 * PI)
	{
		r->player.pdir_v -= 2 * PI;
	}
}

void	d_handler(t_runtime *r)
{
	r->player.pos.x += 1 * ((float)(cos(r->player.pdir_v - PI / 2)));
	r->player.pos.y += 1 * ((float)(sin(r->player.pdir_v - PI / 2)));
}
