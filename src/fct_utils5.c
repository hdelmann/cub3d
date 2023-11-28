/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:24:52 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/26 18:30:57 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

int	calcul_max_l(char **strings)
{
	size_t	max_length;
	int		i;
	size_t	current_length;

	i = 0;
	max_length = 0;
	while (strings[i] != NULL)
	{
		current_length = my_strlen(strings[i]);
		if (current_length > max_length)
		{
			max_length = current_length;
		}
		i++;
	}
	return (max_length);
}
