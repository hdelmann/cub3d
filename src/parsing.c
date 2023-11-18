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
	int i;

	i = 0;
	while (line[i] && ft_is_whitespace(line[i]))
		i++;
	if (line[i])
		return (0);
	return (1);
}

int filename_check(char *filename)
{
	int i;

	i = 0;
	if(!filename)
		return (printf("Error: No file was passed, Exmple: ./cub3D <filename>\n"), 1);
	while(filename[i])
		i++;
	if(!(filename[i - 1] == 'b' && filename[i - 2] == 'u' && filename[i - 3] == 'c'))
    {
	    printf("Error: Wrong filetype, select a file with .cub termination\n");
		exit(1);
    }
	return(1);
}

int charset(char c)
{
	if (c == '1' || c == '0' || c == 'W' || c == 'N'|| 
			c == 'S' || c == 'E' || ft_is_whitespace(c))
		return (1);
	return (0);
}

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

char	**get_map(char **file)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while(file[i] && !is_map(file[i]))
		i++;
	if (!file[i])
		return (NULL);
	map = malloc(sizeof(char *) * (file_len(file) - i + 1));
	while(file[i])
	{
		map[j] = ft_strdup_r(file[i]);
		i++;
		j++;
	}
	map[j] = 0;
	return (erase_empty_lines(map));
}

char	**get_textures(char **file)
{
	char	**textures;
	int		i;

	i = 0;
	while(file[i] && !is_map(file[i]))
		i++;
	textures = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while(file[i] && !is_map(file[i]))
	{
		textures[i] = ft_strdup_r(file[i]);
		i++;
	}
	textures[i] = 0;
	return (erase_empty_lines(textures));
}

void	file_parsing(t_runtime *r)
{
	if(!r->map.map)
		return;
	r->map.textures = get_textures(r->map.map);
	r->map.map = get_map(r->map.map);
	r->map.map = tab_inv(r->map.map);
	parse_txt(r);
}

int	 rgb_too_long(char **rgb)
{
	int i;

	i = 0;
	//printf("hello\n");
	while (rgb[i])
	{
		printf("hello = %s\n", rgb[i]);
		if(my_strlen(rgb[i]) > 3 || (ft_atoi(rgb[i]) > 255 && ft_atoi(rgb[i]) >= 0))
			return(1);
		i++;
	}
	return (0);
}

int	ft_isdigit_mod(int c)
{
	if ((c >= '0' && c <= '9') || c == ',')
	{
		return (1);
	}
	return (0);
}

int	multiple_comma(char *array)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (array[i])
	{
		if (array[i] == ',')
			comma++;
		if (!ft_isdigit_mod(array[i]))
			return(1);
		i++;
	}
	if (comma > 2)
		return (1);
	return (0);
}

int	set_fl_or_cl(t_runtime *r, char *array, int f_or_c)
{
	char **rgb;
	int i;

	i = 0;
	rgb = ft_split(array,',');
	if(rgb_too_long(rgb) || file_len(rgb) > 3 || multiple_comma(array))
		exit(printf("Error: Incorrect RGB parameters\n"));
	while (rgb[i])
	{
		if (i == 0)
			r->color[f_or_c].c_red = ft_atoi(rgb[i]);
		else if (i == 1)
			r->color[f_or_c].c_green = ft_atoi(rgb[i]);
		else if (i == 2)
			r->color[f_or_c].c_blue = ft_atoi(rgb[i]);
		i++;
	}
	return(0);
}

int cmp_and_init_txt(t_runtime *r, char **array)
{
	if (file_len(array) != 2)
		return(1);
	if (!ft_strncmp(array[0], "NO", 2))
		r->txtrs[NO].path = ft_strdup_r(array[1]);
	else if (!ft_strncmp(array[0], "SO", 2))
		r->txtrs[SO].path = ft_strdup_r(array[1]);
	else if (!ft_strncmp(array[0], "EA", 2))
		r->txtrs[EA].path = ft_strdup_r(array[1]);
	else if (!ft_strncmp(array[0], "WE", 2))
		r->txtrs[WE].path = ft_strdup_r(array[1]);
	else if (!ft_strncmp(array[0], "F", 2))
		set_fl_or_cl(r, array[1], FLR);
	else if (!ft_strncmp(array[0], "C", 2))
		set_fl_or_cl(r, array[1], CEIL);
	return (0);
}

int parse_txt(t_runtime *r)
{
	int 	i;
	char	**array;

	i = 0;
	if(file_len(r->map.textures) != 6)
		exit(printf("Invalid textures\n"));
	while (r->map.textures[i])
	{
		array = ft_split(r->map.textures[i], ' ');
		if (my_strlen(array[0]) > 2)
			exit(printf("Invalid textures\n"));
		else if(cmp_and_init_txt(r, array))
			exit(printf("Invalid textures\n"));
		//free_oldfile(array);
		i++;
	}
	return(0);
}


void     init_Ppos(t_runtime *r)
{
    int y;
    int x;
	int count;
	
	count = 0;
    y = 0;
    while (r->map.map[y])
    {
        x = 0;
        while (r->map.map[y][x])
        {
            if (r->map.map[y][x] == 'N' || r->map.map[y][x] == 'S' || r->map.map[y][x] == 'W' ||r->map.map[y][x] == 'E')
            {
				count++;
				if(count > 1)
				{
					printf("More than one spawn point %d\n", count);
					exit(1);
				}
                r->player.pos.x = x * CASE_SIZE + 1 * CASE_SIZE / 2;
                r->player.pos.y = y * CASE_SIZE + 1 * CASE_SIZE / 2;
                if (r->map.map[y][x] == 'N')
				{
                    r->player.pdir_v = PI/2;
					r->player.pdir = PI/2;
				}
                else if (r->map.map[y][x] == 'W')
				{
                    r->player.pdir_v = PI;
					r->player.pdir = PI;
				}
                else if (r->map.map[y][x] == 'S')
				{
                    r->player.pdir_v = 3*PI/2;
					r->player.pdir = 3*PI/2;
				}
                else if (r->map.map[y][x] == 'E')
				{
                    r->player.pdir_v = 0;
					 r->player.pdir = 0;
				}
				printf("angle %f\n", r->player.pdir_v);
				//exit(1);
            }
            x++;
        }
        y++;
    }
	if (!count)
		exit(printf("No player detected\n"));
}