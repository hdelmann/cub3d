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
		if (line[i] != '1' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	minisiderowsl2(t_runtime *r, int i, int j)
{
	while (r->map.map[i][j])
	{
		if ((r->map.map[i][j] == ' ' || r->map.map[i][j] == 'N'
				|| r->map.map[i][j] == 'W' || r->map.map[i][j] == 'E'
					|| r->map.map[i][j] == 'S') && r->map.map[i][j + 1] != '1')
			map_error();
		j++;
	}
}

void	minisiderowsl3(t_runtime *r, int i, int j)
{
	while (r->map.map[i + 1][j])
	{
		if ((r->map.map[i + 1][j] == ' ' || r->map.map[i + 1][j] == 'N'
				|| r->map.map[i + 1][j] == 'W' || r->map.map[i + 1][j] == 'E'
					|| r->map.map[i + 1][j] == 'S') && r->map.map[i][j] != '1')
			map_error();
		j++;
	}
}
