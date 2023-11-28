/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapset2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:41:54 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/26 20:38:25 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	map_error(void)
{
	printf("Error: There is a hole in the wall!\n");
	exit(1);
}

int	is_map_surrounded(t_runtime *r)
{
	int	i;
	int	last;

	i = 0;
	last = 0;
	if (chk_siderows(r) != 0)
		map_error();
	if (!only_wall(r->map.map[i]))
		map_error();
	i++;
	while (r->map.map[i + 1])
	{
		last = my_strlen(r->map.map[i]) - 1;
		if ((r->map.map[i][0] != '1' && r->map.map[i][0] != ' ' )
			|| (r->map.map[i][last] != '1' && r->map.map[i][last] != ' '))
			map_error();
		i++;
	}
	if (!only_wall(r->map.map[i]))
		map_error();
	return (0);
}

void	parsing(t_runtime *r, char *filename)
{
	filename_check(filename);
	file_parsing(r);
	if (check_map_t(r->map.map, CHARSET) == 0)
	{
		printf("Invalid char\n");
		exit(1);
	}
	if (is_map_surrounded(r) == 1)
	{
		printf("Error: Invalid map\n");
		exit(1);
	}
	r->map.map = replace_s_to_1(r->map.map);
	r->map.map = complete_strings(r->map.map);
	r->map.map = tab_inv(r->map.map);
}

void	map_fill(t_runtime *r, int fd)
{
	char	*line;
	int		i;
	int		t_malloc;

	line = get_next_line(fd);
	i = 0;
	t_malloc = 1;
	r->map.map = malloc(t_malloc * sizeof(char *));
	r->map.map[0] = NULL;
	while (line)
	{
		if (!is_line_empty(line))
		{
			t_malloc++;
			line = replace_n_to_r(line);
			r->map.map = ft_realloc2(r->map.map, t_malloc);
			r->map.map[i] = ft_strdup_ff(r->map.map[i], line);
			i++;
			r->map.map[i] = NULL;
		}
		r->map.lines++;
		free(line);
		line = get_next_line(fd);
	}
}

int	check_map_t(char **map, char *valid_chars)
{
	int	k;
	int	i;

	i = 0;
	k = 0;
	while (map[k])
	{
		k++;
	}
	k--;
	while (i < k)
	{
		if (!contains_only_valid_chars(map[i], valid_chars))
		{
			printf("Error: Invalid character in map\n");
			return (0);
		}
		i++;
	}
	return (1);
}
