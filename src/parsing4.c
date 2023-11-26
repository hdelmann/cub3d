/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:30:12 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/26 19:32:31 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	file_len(char **file)
{
	int	i;

	if (!file)
		return (0);
	i = 0;
	while (file[i])
		i++;
	return (i);
}

char	*ft_strdup_r(const char *s1)
{
	int		i;
	char	*dest;

	dest = malloc((sizeof(char)) * (my_strlen(s1) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_map(char *line)
{
	int		i;

	i = 0;
	while (line[i] && charset(line[i]))
		i++;
	if (!line[i] && !is_empty(line))
		return (1);
	return (0);
}

void	free_oldfile(char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		free(file[i]);
		i++;
	}
	free(file);
	file = NULL;
}

char	**erase_empty_lines(char **file)
{
	char	**n_file;
	int		empty_lines;
	int		i;
	int		j;

	i = 0;
	j = 0;
	empty_lines = 0;
	while (file[i])
	{
		if (is_empty(file[i]))
			empty_lines++;
		i++;
	}
	n_file = malloc(sizeof(char *) * (file_len(file) - empty_lines + 1));
	i = 0;
	while (file[i])
	{
		if (!is_empty(file[i]))
			n_file[j++] = ft_strdup_r(file[i]);
		i++;
	}
	n_file[j] = 0;
	free_oldfile(file);
	return (n_file);
}
