/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:56:57 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/26 20:57:18 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	set_fl_or_cl(t_runtime *r, char *array, int f_or_c)
{
	char	**rgb;
	int		i;

	i = 0;
	rgb = ft_split(array, ',');
	if (rgb_too_long(rgb) || file_len(rgb) > 3 || multiple_comma(array))
		exit(printf("Error: Incorrect RGB parameters\n"));
	while (rgb[i])
	{
		if (i == 0)
			r->color[f_or_c].c_blue = ft_atoi(rgb[i]);
		else if (i == 1)
			r->color[f_or_c].c_green = ft_atoi(rgb[i]);
		else if (i == 2)
			r->color[f_or_c].c_red = ft_atoi(rgb[i]);
		i++;
	}
	free_tab(rgb, charlen(rgb));
	return (0);
}

int	cmp_and_init_txt(t_runtime *r, char **array)
{
	if (file_len(array) != 2)
		return (1);
	if (!ft_strncmp(array[0], "NO", 2))
		r->txtrs[NO].path = ft_strdup_r(array[1]);
	else if (!ft_strncmp(array[0], "SO", 2))
		r->txtrs[SO].path = ft_strdup_r(array[1]);
	else if (!ft_strncmp(array[0], "EA", 2))
		r->txtrs[EA].path = ft_strdup_r(array[1]);
	else if (!ft_strncmp(array[0], "WE", 2))
		r->txtrs[WE].path = ft_strdup_r(array[1]);
	else if (!ft_strncmp(array[0], "F", 2))
		set_fl_or_cl(r, array[1], FLR);
	else if (!ft_strncmp(array[0], "C", 2))
		set_fl_or_cl(r, array[1], CEIL);
	return (0);
}

int	parse_txt(t_runtime *r)
{
	int		i;
	char	**array;

	i = 0;
	if (file_len(r->map.textures) != 6)
		exit(printf("Error: Invalid textures\n"));
	while (r->map.textures[i])
	{
		array = ft_split(r->map.textures[i], ' ');
		if (my_strlen(array[0]) > 2)
			exit(printf("Error: Invalid textures\n"));
		else if (cmp_and_init_txt(r, array))
			exit(printf("Error: Invalid textures\n"));
		free_tab(array, charlen(array));
		i++;
	}
	return (0);
}
