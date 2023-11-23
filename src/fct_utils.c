#include "../includes/Cub3D.h"

char **tab_inv(char **tab)
{
	char **tab_inv;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	tab_inv = malloc(sizeof(char *) * (charlen(tab) + 1));
	while (tab[i] != NULL)
	{	
		k = 0;
		j = my_strlen(tab[i]);
		tab_inv[i] = malloc(sizeof(char) * (j + 1));
		while(j >= 0)
		{
			tab_inv[i][k] = tab[i][j];
			k++;
			j--;
		}
		tab_inv[i][k] = '\0';
		i++;
	}
	tab_inv[i] = NULL;
	return(tab_inv);
}

int test_charset(char **c)
{
	int k = 0;
	for (int j = 0; c[j] != NULL; j++)
	{
		for (int i = 0; c[j][i] != '\0'; i++)
		{
			if (c[j][i] == 'N' || c[j][i] == 'S' || c[j][i] == 'E' || c[j][i] == 'W')
				k++;
			if (k > 1)
				return (0);
			if (c[j][i] != 'N' && c[j][i] != 'S' && c[j][i] != 'E' && c[j][i] != 'W' && c[j][i] != '0' && c[j][i] != '1')
				return(0);
		}
	}
	if (k == 0)
		return(0);
	return (1);
}



float* myReallocfloat(float *ptr, int Newsize) {
	float *dst;
	int i = 0;
	dst = malloc(sizeof(float) * Newsize);
	while(ptr[i] != -1)
	{
		dst[i] = ptr[i];
		i++;
	}
	dst[i] = -1;
	free(ptr);
	return(dst);
}

float calucl_dist(float x0, float x1, float y0, float y1)
{
	float dist;
	dist = sqrt(((x1 - x0) * (x1 - x0)) + ((y1 - y0) * (y1 - y0)));
	return (dist);
}

char *ft_strdup(char	*dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
		++i;
	dst = malloc(sizeof(char) * i + 1);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}

char *ft_strdup_ff(char	*dst, char *src)
{
	int	i;

	i = 0;
//	free(dst);
	while (src[i])
		++i;
	dst = malloc(sizeof(char) * i + 1);
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		++i;
	}
	dst[i] = '\0';
	return (dst);
}

static int	ft_mots(char const *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			j++;
			while (str[i] && str[i] != c)
			i++;
		}
	}
	return (j);
}

static char	*ft_mettre(char *mot, char const *s, int i, int len)
{
	int	j;

	j = 0;
	while (len > 0)
	{
		mot[j] = s[i - len];
		j++;
		len--;
	}
	mot[j] = '\0';
	return (mot);
}

static char	**ft_sep(char const *s, char c, char **s2, int num)
{
	int	i;
	int	mot;
	int	len;

	i = 0;
	mot = 0;
	len = 0;
	while (mot < num)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			len++;
		}
		s2[mot] = (char *)malloc(sizeof(char) * (len + 1));
		if (!s2)
			return (0);
		ft_mettre(s2[mot], s, i, len);
		len = 0;
		mot++;
	}
	s2[mot] = NULL;
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char			**s2;
	unsigned int	num;

	if (!s)
		return (0);
	num = ft_mots(s, c);
	s2 = (char **)malloc(sizeof(char *) * (num + 1));
	if (!s2)
		return (0);
	ft_sep(s, c, s2, num);
	return (s2);
}


char	*ft_strjoin(char *s1, char *s2)
{
	char			*s3;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (0);
	s3 = (char *)malloc(sizeof(*s3) * (gnl_ft_strlen(s1) + gnl_ft_strlen(s2) + 1));
	if (!s3)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = 0;
	return (s3);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!n)
		return (0);
	while (n > 1 && *s1 && *s2
		&& (*(unsigned char *)s1 == *(unsigned char *)s2))
	{
		s1++;
		s2++;
		n--;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}


char	*ft_strdup_f(char *src)
{
	int		i;
	char	*p;

	i = 0;
	p = malloc((gnl_ft_strlen(src) + 1) * sizeof(char));
	if (!p)
		return (0);
	while (src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_strcpy_env(char **envp)
{
	int		i;
	char	**cpyenv;

	i = 0;
	cpyenv = NULL;
	while (envp[i])
	{
		cpyenv[i] = ft_strdup_f(envp[i]);
		i++;
	}
	cpyenv[i] = NULL;
	return (cpyenv);
}

int fileNameCheck(char *filename)
{
	int i;

	i = 0;
	if(!filename)
	{
		printf("Error: No file was passed, Exmple: ./cub3D <filename>\n");
		return (1);
	}
	while(filename[i])
		i++;
	if(filename[i - 1] == 'b' && filename[i - 2] == 'u' && filename[i - 3] == 'c')
		return(0);
	printf("Error: Wrong filetype, select a file with .cub termination\n");
	return(1);
}

int ft_is_space(int n)
{
	return(n == '\r' 
		|| n == ' ' 
		|| n == '\t'
		|| n == '\0'
		|| n == '\v');
}

int	is_line_empty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (!ft_is_space(str[i++]))
			return (0);
	}
	return (1);
}

char *replace_n_to_r(char *line)
{
    int i;

    i = 0;
    while(line[i] != '\0')
    {
        if (line[i] == '\n')
            line[i] = '\0';
        i++;
    }
    return (line);
}

void freeTab(char **array, int size) {
    if (array == NULL) {
        return;  // Si le tableau est déjà NULL, il n'y a rien à libérer
    }

    int i = 0;
    while (i < size) {
        free(array[i]);  // Libère chaque chaîne de caractères
        i++;
    }

    free(array);  // Libère le tableau de pointeurs
}

char	**ft_realloc2(char **map, int i)
{
	char	**map_tp;
	int		x;

	x = 0;
  	map_tp = malloc(i * sizeof(char *));
	while (map[x] != NULL)
	{
		map_tp[x] = ft_strdup(map_tp[x], map[x]);
		x++;
	}
	if (x != 0)
		map_tp[x] = NULL;
	freeTab(map, charlen(map));
	return (map_tp);
}

float my_fabs(float i)
{
	return(i < 0) ? -i : i;
}

int charlen(char** tableau) {
    int longueur = 0;

    while (tableau[longueur] != NULL) {
        longueur++;
    }

    return longueur;
}

int my_strlen(const char* chaine) {
    int longueur = 0;

    while (chaine[longueur] != '\0') {
        longueur++;
    }

    return longueur;
}