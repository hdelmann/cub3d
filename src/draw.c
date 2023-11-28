/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:20:58 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 01:26:52 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	my_mlx_draw_pixel(char *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	my_mlx_put_pixel(t_runtime *r, uint32_t x, uint32_t y, uint32_t color)
{
	char	*dst;

	dst = r->img.addr + (y * r->img.line_length + x *(r->img.bpp / 8));
	my_mlx_draw_pixel(dst, color);
	return (0);
}

void	my_mlx_pixel_put(t_runtime *r, int x, int y, int color)
{
	char	*dst;

	dst = r->img.addr + (y * r->img.line_length + x * (r->img.bpp / 8));
	*(unsigned int *)dst = color;
}

void	free_tab(char **array, int size)
{
	int	i;

	if (array == NULL)
	{
		return ;
	}
	i = 0;
	while (i < size)
	{
		free (array[i]);
		i++;
	}
	free (array);
}
