#include "../includes/Cub3D.h"
void init_tmp(t_runtime *r)
{
    r->player.pos.x = 96;
    r->player.pos.y = 96;
    r->player.pdir = PI/2;
    r->player.pdir_v = PI/2;
    r->player.dir = DIR_W;
    r->line.start.x = r->player.pos.x - 5;
    r->line.start_v.x = r->player.pos.x - 5;
    r->line.start.y = r->player.pos.y + 5;
    r->line.start_v.y = r->player.pos.y + 5;
    r->line.start_fov.y = r->player.pos.y + 5;
    r->line.start_fov.x = r->player.pos.x + 5;
    r->line.end.x = r->line.start.x;
    r->line.end.y = r->line.start.y;
    r->player.FOV = PI/3;
    r->line.tab_dist = malloc(1920 * sizeof(float));
}

int main(int ac, char **av)
{
    int fd;
    t_runtime r;
    
    if (ac == 2)
    {
        r.filename = av[1];
        fd = open(av[1], O_RDONLY);
        map_fill(&r, fd);
        init_tmp(&r);
        parsing(&r, av[1]);
        init_Ppos(&r);
        mlx_set_setting(MLX_MAXIMIZED, false);
        r.mlx = mlx_init(WIDTH , HEIGHT, "Cub3D", true);
        load_textures(&r);
        if (!r.mlx) 
            return (-1);
        r.img = mlx_new_image(r.mlx, WIDTH, HEIGHT);
        if (!r.img || (mlx_image_to_window(r.mlx, r.img, 0, 0) < 0))
		    return(-1);
        mlx_loop_hook(r.mlx, &playerendering2d, &r);
	    mlx_key_hook(r.mlx, &my_keyhook, &r);
	    mlx_loop(r.mlx);
	    mlx_terminate(r.mlx);
    }
}