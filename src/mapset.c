#include "../includes/Cub3D.h"


void    map_fill(t_runtime *r, int fd)
{
    char *line;
    int i;
    int t_malloc;
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
            r->map.map[i] = ft_strdup(r->map.map[i], line);
            i++;
            r->map.map[i] = NULL;
        }
        line = get_next_line(fd);
    }
}