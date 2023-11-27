/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:24:52 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/27 20:05:57 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

char	**ft_realloc2(char **map, int i)
{
	char	**map_tp;
	int		x;

	x = 0;
	map_tp = malloc(i * sizeof(char *));
	while (map[x] != NULL)
	{
		map_tp[x] = ft_strdup(map_tp[x], map[x]);
		x++;
	}
	if (x != 0)
		map_tp[x] = NULL;
	free_tab(map, charlen(map));
	return (map_tp);
}

int	charlen(char **tableau)
{
	int	longueur;

	longueur = 0;
	while (tableau[longueur] != NULL)
	{
		longueur++;
	}
	return (longueur);
}

int	my_strlen(const char *chaine)
{
	int	longueur;

	longueur = 0;
	while (chaine[longueur] != '\0')
	{
		longueur++;
	}
	return (longueur);
}

char	*replace_n_to_r(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
	return (line);
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

char	*replace_s_to_1(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			line[i] = '1';
		i++;
	}
	return (line);
}
