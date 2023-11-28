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

char *reverseString(const char *original) {
    size_t length = my_strlen(original);
    char *reversed = (char *)malloc((length + 1) * sizeof(char));

    if (reversed == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    size_t i = 0;
    while (i < length) {
        reversed[i] = original[length - i - 1];
        i++;
    }

    reversed[length] = '\0';

    return reversed;
}

char **tab_inv(char **strings) {
    // Trouver la longueur du tableau
    int numStrings = 0;
    while (strings[numStrings] != NULL) {
        numStrings++;
    }

    char **result = (char **)malloc((numStrings + 1) * sizeof(char *));

    if (result == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while (strings[i] != NULL) {
        result[i] = reverseString(strings[i]);
        i++;
    }

    // Terminer le nouveau tableau avec NULL
    result[numStrings] = NULL;
	free_tab(strings, charlen(strings));
    return result;
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
