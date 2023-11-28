/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:53:45 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 00:31:59 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	load_textures(t_runtime *r)
{
	int	crd;

	crd = NO;
	while (crd <= WE)
	{
		r->txt_d[crd].img = mlx_xpm_file_to_image(r->mlx, r->txtrs[crd].path,
				&r->txt_d[crd].width, &r->txt_d[crd].height);
		if (!r->txt_d[crd].img)
		{
			printf("Error: Unable to load \"%s\"\n", r->txtrs[crd].path);
			exit(1);
		}
		r->txt_d[crd].addr = mlx_get_data_addr(r->txt_d[crd].img,
				&r->txt_d[crd].bpp, &r->txt_d[crd].line_length,
				&r->txt_d[crd].endian);
		crd++;
	}
}

int	txt_wall_ort(t_runtime *r, float ysta, float yend)
{
	if (r->line.ort == N && roundf(ysta) != roundf(yend))
	{
		return (NO);
	}
	else if (r->line.ort == S && roundf(ysta) != roundf(yend))
	{
		return (SO);
	}
	else if (r->line.ort == E && roundf(ysta) != roundf(yend))
	{
		return (EA);
	}
	else if (r->line.ort == O && roundf(ysta) != roundf(yend))
	{
		return (WE);
	}
	return (0);
}

void	texture_to_image(t_runtime	*r, int txt, float tex_y, float tex_x)
{
	char	*pixel;
	int		color;

	pixel = r->txt_d[txt].addr + ((int)(tex_y) *(int)r->txt_d[txt].line_length
			+ (int)tex_x * (int)r->txt_d[txt].bpp / 8);
	color = *(int *)pixel;
	my_mlx_pixel_put(r, (int)r->xray, r->start_y, color);
}

static int	_get_pos_in_texture(t_coord line_coords, int i, int tex_width)
{
	float	pos;

	pos = (float)(i - line_coords.a) / (line_coords.b - line_coords.a);
	pos = pos * tex_width;
	return (c_min((int)pos, tex_width - 1));
}

void	draw_textured_wall(t_runtime *r, int txt, float height, float xray)
{
	float	tex_y;
	float	tex_x;
	t_coord	line;

	r->xray = xray;
	line.a = (-height / 2) + (HEIGHT / 2);
	line.b = (height / 2) + (HEIGHT / 2);
	if (line.a < 0)
		r->start_y = 0;
	else
		r->start_y = line.a;
	if (line.b > HEIGHT -1)
		r->end_y = HEIGHT - 1;
	else
		r->end_y = line.b;
	tex_y = 0;
	tex_x = wallx_determination_2(r, r->start_y, r->end_y, txt);
	while (r->start_y < r->end_y && r->start_y < HEIGHT)
	{
		texture_to_image(r, txt, _get_pos_in_texture(line, r->start_y,
				r->txt_d[txt].width), tex_x);
		r->start_y++;
		tex_y += r->txt_d[txt].height / (double)height;
	}
}
