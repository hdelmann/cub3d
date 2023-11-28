/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 01:02:23 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 02:16:55 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	draw_ceil(t_runtime *r)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 2)
		{
			my_mlx_put_pixel(r, i, j, get_rgba(r->color[CEIL].c_red,
					r->color[CEIL].c_green, r->color[CEIL].c_blue, 255));
			j++;
		}
		i++;
	}
}

void	draw_ceil2(t_runtime *r)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIDTH)
	{
		j = HEIGHT / 2;
		while (j < HEIGHT)
		{
			my_mlx_put_pixel(r, i, j, get_rgba(r->color[FLR].c_red,
					r->color[FLR].c_green, r->color[FLR].c_blue, 255));
			j++;
		}
		i += 2;
	}
}

void	draw_ceil3(t_runtime *r)
{
	int	i;
	int	j;

	i = 1;
	while (i < WIDTH)
	{
		j = HEIGHT / 2;
		while (j < HEIGHT)
		{
			my_mlx_put_pixel(r, i, j, get_rgba(r->color[FLR].c_red,
					r->color[FLR].c_green, r->color[FLR].c_blue, 255));
			j++;
		}
		i += 2;
	}
}

int	playerendering2d(t_runtime *r)
{
	int	i;
	int	j;

	draw_ceil(r);
	draw_ceil2(r);
	draw_ceil3(r);
	j = HEIGHT / 2;
	while (j < HEIGHT)
	{
		i = WIDTH;
		while (i < WIDTH)
		{
			my_mlx_put_pixel(r, i, j, get_rgba(r->color[CEIL].c_red,
					r->color[CEIL].c_green, r->color[CEIL].c_blue, 255));
			i++;
		}
		j += 2;
	}
	fov_rendering(r);
	mlx_put_image_to_window(r->mlx, r->mlx_win, r->img.img, 0, 0);
	return (0);
}

void	p_posini(t_runtime *r)
{
	if (r->player.pos.x - (int)r->player.pos.x == 0
		&& (int)r->player.pos.x % CASE_SIZE == 0)
		r->player.pos.x -= 0.01;
	if (r->player.pos.y - (int)r->player.pos.y == 0
		&& (int)r->player.pos.y % CASE_SIZE == 0)
		r->player.pos.y -= 0.01;
}
