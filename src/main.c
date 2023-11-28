/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:57:56 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 02:39:44 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	init_tmp(t_runtime *r)
{
	r->player.pos.x = 96;
	r->player.pos.y = 96;
	r->player.pdir = PI / 2;
	r->coa = 0;
	r->player.pdir_v = PI / 2;
	r->player.dir = DIR_W;
	r->line.start.x = r->player.pos.x - 5;
	r->line.start_v.x = r->player.pos.x - 5;
	r->line.start.y = r->player.pos.y + 5;
	r->line.start_v.y = r->player.pos.y + 5;
	r->line.start_fov.y = r->player.pos.y + 5;
	r->line.start_fov.x = r->player.pos.x + 5;
	r->line.end.x = r->line.start.x;
	r->line.end.y = r->line.start.y;
	r->player.fov = PI / 3;
	r->prevd = 700;
	r->line.tab_dist = malloc(1920 * sizeof(float));
}

int	main(int ac, char **av)
{
	int			fd;
	t_runtime	r;

	if (ac == 2)
	{
		r.filename = av[1];
		fd = open(av[1], O_RDONLY);
		map_fill(&r, fd);
		init_tmp(&r);
		parsing(&r, av[1]);
		init_ppos(&r);
		r.mlx = mlx_init();
		r.mlx_win = mlx_new_window(r.mlx, WIDTH, HEIGHT, "Cub3d");
		load_textures(&r);
		if (!r.mlx)
			return (-1);
		r.img.img = mlx_new_image(r.mlx, WIDTH, HEIGHT);
		r.img.addr = mlx_get_data_addr(r.img.img, &r.img.bpp,
				&r.img.line_length, &r.img.endian);
		mlx_hook(r.mlx_win, 2, 1L << 0, my_keyhook, &r);
		mlx_loop_hook(r.mlx, playerendering2d, &r);
		mlx_hook(r.mlx_win, 17, 1L << 17, close_window, &r);
		mlx_loop(r.mlx);
		return (0);
	}
}
