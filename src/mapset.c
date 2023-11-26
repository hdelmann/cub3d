/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:22:36 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/26 20:38:12 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

char	*ft_strchr(char *str, int ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
		{
			return (str);
		}
		str++;
	}
	return (NULL);
}

int	contains_only_valid_chars(char *row, char *valid_chars)
{
	int	row_length;
	int	i;

	i = 0;
	row_length = my_strlen(row);
	while (i < row_length)
	{
		if (ft_strchr(valid_chars, row[i]) == NULL)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	only_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

void	mini_siderowsl1(t_runtime *r, int i, int j)
{
	r->len1 = my_strlen(r->map.map[i]);
	if (r->map.map[i + 1])
		r->len2 = my_strlen(r->map.map[i + 1]);
	if (r->len1 > r->len2)
	{
		j = r->len2;
		while (r->map.map[i][j])
		{
			if (r->map.map[i][j] == '0' && r->map.map[i + 1][j] != '1')
				map_error();
			j++;
		}
	}
	if (r->len2 > r->len1)
	{
		j = r->len1;
		while (r->map.map[i + 1][j])
		{
			if (r->map.map[i + 1][j] == '0' && r->map.map[i][j] != '1')
				map_error();
			j++;
		}
	}
}

int	chk_siderows(t_runtime *r)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	r->len1 = 0;
	r->len2 = 0;
	while (r->map.map[i])
	{
		mini_siderowsl1(r, i, j);
		i++;
	}
	return (0);
}
