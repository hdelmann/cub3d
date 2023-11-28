/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:30:09 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 14:25:09 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

char	**get_map(char **file)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (file[i] && !is_map(file[i]))
		i++;
	if (!file[i])
		return (NULL);
	map = malloc(sizeof(char *) * (file_len(file) - i + 1));
	while (file[i])
	{
		map[j] = ft_strdup_r(file[i]);
		i++;
		j++;
	}
	map[j] = 0;
	free_tab(file, i);
	return (erase_empty_lines(map));
}

char	**get_textures(char **file)
{
	char	**textures;
	int		i;

	i = 0;
	while (file[i] && !is_map(file[i]))
		i++;
	textures = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (file[i] && !is_map(file[i]))
	{
		textures[i] = ft_strdup_r(file[i]);
		i++;
	}
	textures[i] = 0;
	return (erase_empty_lines(textures));
}

void	file_parsing(t_runtime *r)
{
	if (!r->map.map)
		return ;
	r->map.textures = get_textures(r->map.map);
	r->map.map = get_map(r->map.map);
	parse_txt(r);
}

int	rgb_too_long(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (my_strlen(rgb[i]) > 3
			|| (ft_atoi(rgb[i]) > 255 && ft_atoi(rgb[i]) >= 0))
			return (1);
		i++;
	}
	if (i != 3)
		return (1);
	return (0);
}

int	ft_isdigit_mod(int c)
{
	if ((c >= '0' && c <= '9') || c == ',')
	{
		return (1);
	}
	return (0);
}
