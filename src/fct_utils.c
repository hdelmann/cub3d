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

char	*reverse_string(const char *original)
{
	size_t	length;
	char	*reversed;
	size_t	i;

	length = my_strlen(original);
	reversed = (char *)malloc((length + 1) * sizeof(char));
	if (reversed == NULL)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < length)
	{
		reversed[i] = original[length - i - 1];
		i++;
	}
	reversed[length] = '\0';
	return (reversed);
}

char	**tab_inv(char **strings)
{
	int		num_strings;
	int		i;
	char	**result;

	i = 0;
	num_strings = 0;
	while (strings[num_strings] != NULL)
	{
		num_strings++;
	}
	result = (char **)malloc((num_strings + 1) * sizeof(char *));
	if (result == NULL)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	while (strings[i] != NULL)
	{
		result[i] = reverse_string(strings[i]);
		i++;
	}
	result[num_strings] = NULL;
	free_tab(strings, charlen(strings));
	return (result);
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
