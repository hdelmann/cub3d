/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:30:05 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/26 20:56:45 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	multiple_comma(char *array)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (array[i])
	{
		if (array[i] == ',')
			comma++;
		if (!ft_isdigit_mod(array[i]))
			return (1);
		i++;
	}
	if (comma > 2)
		return (1);
	return (0);
}

void	spwn_chk(int count)
{
	if (count > 1)
	{
		printf("Error: More than one spawn point!\n%d \
spawns detected\n", count);
		exit(1);
	}
	if (!count)
		exit(printf("Error: No player detected\n"));
}

int	pos_chk(t_runtime *r, int y, int x, int count)
{
	count++;
	spwn_chk(count);
	r->player.pos.x = x * CASE_SIZE + 1 * CASE_SIZE / 2;
	r->player.pos.y = y * CASE_SIZE + 1 * CASE_SIZE / 2;
	if (r->map.map[y][x] == 'S')
	{
		r->player.pdir_v = PI / 2;
		r->player.pdir = PI / 2;
	}
	else if (r->map.map[y][x] == 'W')
	{
		r->player.pdir_v = PI;
		r->player.pdir = PI;
	}
	else if (r->map.map[y][x] == 'N')
	{
		r->player.pdir_v = 3 * PI / 2;
		r->player.pdir = 3 * PI / 2;
	}
	else if (r->map.map[y][x] == 'E')
	{
		r->player.pdir_v = 0;
		r->player.pdir = 0;
	}
	return (count);
}

void	init_ppos(t_runtime *r)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (r->map.map[y])
	{
		x = 0;
		while (r->map.map[y][x])
		{
			if (r->map.map[y][x] == 'N' || r->map.map[y][x] == 'S'
					|| r->map.map[y][x] == 'W' || r->map.map[y][x] == 'E')
			{
				count = pos_chk(r, y, x, count);
			}
			x++;
		}
		y++;
	}
	spwn_chk(count);
}
