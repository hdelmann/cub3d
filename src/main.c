#include "../includes/Cub3D.h"
void init_tmp(t_runtime *r)
{
    r->player.pos.x = 205;
    r->player.pos.y = 195;
    r->player.pdir = PI;
    r->player.pdir_v = PI;
    r->player.dir = DIR_W;
    r->line.rad_raystart_v = r->player.pdir_v + FOV / 2;
}

int main(int ac, char **av)
{
    int fd;
    t_runtime r;
    if (ac == 2)
    {
        fd = open(av[1], O_RDONLY);
        map_fill(&r, fd);
        if (parsing_map(av) == 0)
        {
            printf("Wrong map\n");
            return(-1);
        }
        mlx_set_setting(MLX_MAXIMIZED, false);
        r.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
        if (!r.mlx) 
            return (-1);
        r.img = mlx_new_image(r.mlx, WIDTH, HEIGHT);
        if (!r.img || (mlx_image_to_window(r.mlx, r.img, 0, 0) < 0))
		    return(-1);
        init_tmp(&r);
        mlx_loop_hook(r.mlx, &playerendering2d, &r);
        mlx_loop_hook(r.mlx, &calcul_line, &r);
	    mlx_key_hook(r.mlx, &my_keyhook, &r);
	    mlx_loop(r.mlx);
	    mlx_terminate(r.mlx);
    }
}