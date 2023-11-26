/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   txt_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:55:17 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/26 09:49:10 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	c_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

float	wallx_determination_2(t_runtime *r, float ysta, float yend, int txt)
{
	if (r->line.ort == N && ysta <= yend)
	{
		return (CASE_SIZE - (int)(r->line.end_fov.x
			* r->txt_d[txt].width / 4) % r->txt_d[txt].width);
	}
	else if (r->line.ort == S && ysta <= yend)
	{
		return ((int)(r->line.end_fov.x
			* r->txt_d[txt].width / 4) % r->txt_d[txt].width);
	}
	else if (r->line.ort == E && ysta <= yend)
	{
		return ((int)(r->line.end_fov.y
			* r->txt_d[txt].width / 4) % r->txt_d[txt].width);
	}
	else if (r->line.ort == O && ysta <= yend)
	{
		return (CASE_SIZE - (int)(r->line.end_fov.y
			* r->txt_d[txt].width / 4) % r->txt_d[txt].width);
	}
	exit(1);
}
