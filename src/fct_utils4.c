/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:24:52 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/26 18:30:57 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (n > 1 && *s1 && *s2
		&& (*(unsigned char *)s1 == *(unsigned char *)s2))
	{
		s1++;
		s2++;
		n--;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*ft_strdup_f(char *src)
{
	int		i;
	char	*p;

	i = 0;
	p = malloc((gnl_ft_strlen(src) + 1) * sizeof(char));
	if (!p)
		return (0);
	while (src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	ft_is_space(int n)
{
	return (n == '\r'
		|| n == ' '
		|| n == '\t'
		|| n == '\0'
		|| n == '\v');
}

int	is_line_empty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_is_space(str[i++]))
			return (0);
	}
	return (1);
}

char	**complete_strings(char **strings)
{
	size_t	max_length;
	int		i;
	size_t	j;
	char	**result;

	max_length = calcul_max_l(strings);
	result = (char **)malloc((charlen(strings) + 1) * sizeof(char *));
	i = 0;
	while (strings[i] != NULL)
	{
		result[i] = (char *)malloc((max_length + 1) * sizeof(char));
		ft_strcpy(result[i], strings[i]);
		j = my_strlen(result[i]);
		while (j < max_length)
		{
			result[i][j] = '1';
			j++;
		}
		result[i][max_length] = '\0';
		i++;
	}
	result[i] = NULL;
	free_tab(strings, charlen(strings));
	return (result);
}
