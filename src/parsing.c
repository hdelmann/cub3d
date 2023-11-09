#include "../includes/Cub3D.h"

int parsing_map(char **map){
    (void)map;
    return (1);
}

void     init_Ppos(t_runtime *r)
{
    int y;
    int x;

    y = 0;
    while (r->map.map[y])
    {
        x = 0;
        while (r->map.map[y][x])
        {
            if (r->map.map[y][x] == 'N' || r->map.map[y][x] == 'S' || r->map.map[y][x] == 'W' ||r->map.map[y][x] == 'E')
            {
                r->player.pos.x = x * CASE_SIZE + 1 * CASE_SIZE / 2;
                r->player.pos.y = y * CASE_SIZE + 1 * CASE_SIZE / 2;
                if (r->map.map[y][x] == 'N')
                    r->player.pdir_v = PI/2;
                else if (r->map.map[y][x] == 'W')
                    r->player.pdir_v = PI;
                else if (r->map.map[y][x] == 'S')
                    r->player.pdir_v = 3*PI/2;
                else
                    r->player.pdir_v = 0;

            }
            x++;
        }
        y++;
    }
}