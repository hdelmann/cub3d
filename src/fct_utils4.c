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

char	**ft_strcpy_env(char **envp)
{
	int		i;
	char	**cpyenv;

	i = 0;
	cpyenv = NULL;
	while (envp[i])
	{
		cpyenv[i] = ft_strdup_f(envp[i]);
		i++;
	}
	cpyenv[i] = NULL;
	return (cpyenv);
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

char **completeStrings(char **strings) {
    // Trouver la longueur maximale
    size_t maxLength = 0;
    int i = 0;

    while (strings[i] != NULL) {
        size_t currentLength = my_strlen(strings[i]);
        if (currentLength > maxLength) {
            maxLength = currentLength;
        }
        i++;
    }

    // Allouer de la mémoire pour le nouveau tableau
    char **result = (char **)malloc((i + 1) * sizeof(char *));
    if (result == NULL) {
        perror("Erreur d'allocation de mémoire");
        exit(EXIT_FAILURE);
    }

    // Allouer de la mémoire pour chaque chaîne dans le nouveau tableau
    i = 0;
    while (strings[i] != NULL) {
        result[i] = (char *)malloc((maxLength + 1) * sizeof(char));
        if (result[i] == NULL) {
            perror("Erreur d'allocation de mémoire");
            exit(EXIT_FAILURE);
        }

        // Copier la chaîne existante dans le nouveau tableau
        ft_strcpy(result[i], strings[i]);

        // Compléter avec des '1' pour atteindre la longueur maximale
        size_t j = my_strlen(result[i]);
        while (j < maxLength) {
            result[i][j] = '1';
            j++;
        }

        // Ajouter le caractère de fin de chaîne
        result[i][maxLength] = '\0';
        i++;
    }

    // Terminer le nouveau tableau avec NULL
    result[i] = NULL;
	free_tab(strings, charlen(strings));
    return result;
}