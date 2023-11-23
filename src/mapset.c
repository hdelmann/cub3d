#include "../includes/Cub3D.h"

char *ft_strchr(char *str, int ch) 
{
    while (*str != '\0') {
        if (*str == ch) {
            return (str);
        }
        str++;
    }
    return NULL;
}

int contains_only_valid_chars(char *row, char *valid_chars)
{
    int row_length = my_strlen(row);
    for (int i = 0; i < row_length; i++) {
        if (ft_strchr(valid_chars, row[i]) == NULL) {
            return 0; 
        }
    }
    return 1; 
}
int only_wall(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != '1')
            return (0);
        i++;
    }
    return (1);
}

int check_map_t(char **map, char *valid_chars)
{
    int k = 0;
    while (map[k])
    {
        k++;
    }
    k--;
    for (int i = 0; i < k; i++) {
        if (!contains_only_valid_chars(map[i], valid_chars)) 
        {

            printf("Invalid char\n");
            //exit(1);
            return 0; 
        }
    }
    return 1; 
}

int chk_siderows(t_runtime *r)
{
    int i = 0;
    int j = 0;
    int len1 = 0;
    int len2 = 0;


    while (r->map.map[i])
    {
        len1 = my_strlen(r->map.map[i]);
        if (r->map.map[i + 1])
            len2 = my_strlen(r->map.map[i + 1]);
          // printf("len1 = %d\nlen 2 = %d\n", len1, len2);
        if (len1 > len2)
        {
            j = len2;
            while(r->map.map[i][j])
            {
                if(r->map.map[i][j] == '0' &&  r->map.map[i + 1][j] != '1')
                {
                    printf("we got im\n");
                    exit(1);
                }
                else
                {
                   printf("no signals\n");
                }
                j++;
            }
        }
        if (len2 > len1)
        {
            printf("elo\n");
            j = len1;
            while (r->map.map[i + 1][j])
            {
                printf("l1 = %c\nl2 = %c\n", r->map.map[i][j], r->map.map[i + 1][j]);
                if(r->map.map[i + 1][j] == '0' &&  r->map.map[i][j] != '1')
                {
                    printf("we got im on top\n");
                   exit(1);
                }
                else
                {
                    
                    printf("All good\n");
                }
                j++;   
            }
         }
        i++;
    }
           printf("yo\n");
    return(0);
}

int is_map_surrounded(t_runtime *r)
{
    int i;
    int last;

    i = 0;
    last = 0;
    chk_siderows(r);
    if (!only_wall(r->map.map[i]))
    {
        printf("Invalid 1\n");
        return (1);
    }
    i++;
    while (r->map.map[i + 1])
    {
        last = my_strlen(r->map.map[i]) - 1;
        if (r->map.map[i][0] != '1' || r->map.map[i][last] != '1')
        {
            printf("Invalid 2\n");
            return (1);
        }
        i++;
    }
    if (!only_wall(r->map.map[i]))
    {
        printf("Invalid 3\n");
        return (1);
    }
    return (0);
}



void parsing(t_runtime *r, char *filename)
{
    file_parsing(r);
    //printf("XDDD\n");
    filename_check(filename);
    if(check_map_t(r->map.map, CHARSET) == 0)
    {
        printf("Invalid char\n");
        exit(1);
    }
    if(is_map_surrounded(r) == 1)
    {
        printf("Invalid map\n");
        exit(1);
    }
    printf("%s\n",r->txtrs[NO].path);
    printf("%s\n",r->txtrs[SO].path);
    printf("%s\n",r->txtrs[WE].path);
    printf("%s\n",r->txtrs[EA].path);
    printf("%d\n",r->color[1].c_red);
}

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
            r->map.map[i] = ft_strdup_ff(r->map.map[i], line);
            i++;
            r->map.map[i] = NULL;

        }
        r->map.lines++;
        free(line);
        line = get_next_line(fd);
    }
}