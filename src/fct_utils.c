/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:13:45 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/26 18:20:30 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

char	**tab_inv(char **tab)
{
	char	**tab_inv;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	tab_inv = malloc(sizeof(char *) * (charlen(tab) + 1));
	while (tab[i] != NULL)
	{
		k = 0;
		j = my_strlen(tab[i]);
		tab_inv[i] = malloc(sizeof(char) * (j + 1));
		while (j >= 0)
		{
			tab_inv[i][k] = tab[i][j];
			k++;
			j--;
		}
		tab_inv[i][k] = '\0';
		i++;
	}
	tab_inv[i] = NULL;
	return (tab_inv);
}

float	*my_reallocfloat(float *ptr, int Newsize)
{
	float	*dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(float) * Newsize);
	while (ptr[i] != -1)
	{
		dst[i] = ptr[i];
		i++;
	}
	dst[i] = -1;
	free(ptr);
	return (dst);
}

float	calucl_dist(float x0, float x1, float y0, float y1)
{
	float	dist;

	dist = sqrt(((x1 - x0) * (x1 - x0))
			+ ((y1 - y0) * (y1 - y0)));
	return (dist);
}

char	*ft_strdup(char	*dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
		++i;
	dst = malloc(sizeof(char) * i + 1);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup_ff(char	*dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
		++i;
	dst = malloc(sizeof(char) * i + 1);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}
