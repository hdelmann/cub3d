/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:15:31 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/26 19:32:18 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	ft_is_whitespace(int c)
{
	if (c == '\v' || c == '\n' || c == '\t'
		|| c == '\r' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

long	ft_atoi(const char *str)
{
	long	i;
	long	number;
	int		sign;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	return (number * sign);
}

int	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_is_whitespace(line[i]))
		i++;
	if (line[i])
		return (0);
	return (1);
}

int	filename_check(char *filename)
{
	int	i;

	i = 0;
	if (!filename)
		return (printf("Error: No file was passed,\
			 Exmple: ./cub3D <filename>\n"), 1);
	while (filename[i])
		i++;
	if (!(filename[i - 1] == 'b' && filename[i - 2]
			== 'u' && filename[i - 3] == 'c'))
	{
		printf("Error: Wrong filetype, select a file with .cub termination\n");
		exit(1);
	}
	return (1);
}

int	charset(char c)
{
	if (c == '1' || c == '0' || c == 'W' || c == 'N'
		|| c == 'S' || c == 'E' || ft_is_whitespace(c))
		return (1);
	return (0);
}
