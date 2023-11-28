/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:24:52 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 01:26:44 by jgirard-         ###   ########.fr       */
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

char	**replace_s_to_1(char **tab)
{
	char	**tab1;
	int		i;
	int		j;

	tab1 = malloc(sizeof(char *) * (charlen(tab) + 1));
	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		tab1[i] = malloc(sizeof(char) * (my_strlen(tab[i]) + 1));
		while (tab[i][j] != '\0')
		{
			if (tab[i][j] == ' ')
				tab1[i][j] = '1';
			else
				tab1[i][j] = tab[i][j];
			j++;
		}
		tab1[i][j] = '\0';
		i++;
	}
	tab1[i] = NULL;
	free_tab(tab, i);
	return (tab1);
}

void	ft_strcpy(char *dest, const char *src)
{
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
}
