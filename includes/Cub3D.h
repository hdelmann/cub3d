/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:18:41 by jgirard-          #+#    #+#             */
/*   Updated: 2023/11/28 02:35:13 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include "../mlx_linux/mlx.h"
# include <math.h>
# include "../getnext/get_next_line.h"

enum {
	DIR_S,
	DIR_W,
	DIR_A,
	DIR_D,
};

enum {
	HOR,
	VER,
};

enum {
	N,
	SD,
	E,
	O,
};

# define PLAYER_SIZE 10
# define CASE_SIZE 100
# define PI 3.141592653589793238462643383279502884197
# define HEIGHT 1080
# define WIDTH 1920
# define CHARSET "10NEWS "
# define DIRSET  "NEWS0"
# define PCHARSET "NEWS"
# define FLR 0
# define CEIL 1
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define L_AR 65361
# define R_AR 65363

enum e_Textures{
	NO,
	SO,
	EA,
	WE
};

typedef struct point
{
	float	x;
	float	y;
}			t_point;

typedef struct player
{
	t_point	pos;
	float	pdir;
	float	pdir_v;
	int		dir;
	float	fov;
}		t_player;

typedef struct s_line
{
	int		x_wall;
	int		y_wall;
	int		x_wall2;
	int		y_wall2;
	float	dist;
	int		ort;
	int		ort2;
	t_point	start;
	t_point	end;
	float	rad_raystart;
	float	rad_raystart_v;
	float	rad_in;
	float	rad_fov;
	t_point	start_v;
	t_point	end_v;
	t_point	end_def;
	t_point	start_fov;
	t_point	end_fov;
	t_point	end_fov2;
	t_point	end_defov;
	float	*tab_dist;
	float	z;
}	t_line;

typedef struct s_map
{
	char	**map;
	char	**textures;
	int		colums;
	int		lines;
}		t_map;

typedef struct isomet
{
	float	x_iso;
	float	y_iso;
}		t_isomet;

typedef struct s_txt
{
	char			*path;
	void			*walltxt;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	unsigned int	c_red;
	unsigned int	c_green;
	unsigned int	c_blue;
	unsigned int	trnpcy;
}		t_txt;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		height;
	int		width;
	int		endian;
}		t_img;

typedef struct s_coord
{
	int	a;
	int	b;
}		t_coord;

typedef struct s_runtime
{
	t_map		map;
	t_line		line;
	t_player	player;
	void		*mlx;
	void		*mlx_win;
	void		*data;
	t_img		img;
	t_isomet	iso;
	t_txt		txtrs[4];
	t_img		txt_d[4];
	t_txt		color[2];
	char		*filename;
	int			coa;
	float		*dist_tab;
	float		start_y;
	float		end_y;
	float		xray;
	int			len1;
	float		teta;
	float		teta2;
	float		prevd;
	int			len2;
}			t_runtime;

void	ft_strcpy(char *dest, const char *src);
char	**complete_strings(char **strings);
void	free_tab(char **array, int size);
t_point	calcul_inter(t_runtime *r, float dir);
t_point	calcul_inter2(t_runtime *r, float dir);
char	*ft_strdup_r(const char *s1);
int		chk_siderows(t_runtime *r);
char	**erase_empty_lines(char **file);
int		file_len(char **file);
int		is_map(char *line);
int		contains_only_valid_chars(char *row, char *valid_chars);
int		only_wall(char *line);
int		rgb_too_long(char **rgb);
long	ft_atoi(const char *str);
void	draw_textured_wall(t_runtime *r, int txt, float height, float xray);
void	load_textures(t_runtime *r);
int		ft_isdigit_mod(int c);
char	**ft_split(char const *s, char c);
int		my_mlx_put_pixel(t_runtime *r, uint32_t x, uint32_t y, uint32_t color);
int		parse_txt(t_runtime *r);
int		multiple_comma(char *array);
char	**replace_s_to_1(char **tab);
void	my_mlx_pixel_put(t_runtime *r, int x, int y, int color);
void	file_parsing(t_runtime *r);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		check_map_t(char **map, char *valid_chars);
int		filename_check(char *filename);
int		check_invalid_mapt(t_runtime *r);
int		is_map_surrounded(t_runtime *r);
int		parsing_map(t_runtime *r);
void	map_error(void);
char	*ft_strdup(char	*dst, char *src);
char	*ft_strdup_ff(char	*dst, char *src);
int		is_line_empty(char *str);
int		c_min(int a, int b);
void	map_fill(t_runtime *r, int fd);
char	*ft_strdup_f(char *src);
float	wallx_determination_2(t_runtime *r, float ysta, float yend, int txt);
void	my_draw_line_fov(t_runtime *r);
char	**ft_realloc2(char **map, int i);
float	*my_reallocfloat(float *ptr, int Newsize);
void	calcul_line_fovx(void *param);
void	calcul_line_fovy(void *param);
char	*replace_n_to_r(char *line);
char	**tab_inv(char **strings);
int		charset(char c);
int		is_empty(char *line);
void	my_mlx_pixel_put(t_runtime *r, int x, int y, int color);
void	destroy_all(t_runtime *r);
int		get_rgba(int r, int g, int b, int a);
void	fillcubeborder(t_runtime *r);
int		playerendering2d(t_runtime *r);
void	calort(void *param);
int		my_keyhook(int keydata, t_runtime *r);
float	calucl_dist(float x0, float x1, float y0, float y1);
void	calcul_line_interx(void *param, float x0, float y0);
void	calcul_line_intery(void *param, float x0, float y0);
void	my_draw_line(t_runtime *r);
int		close_window(int keycode, t_runtime *r);
void	my_draw_line_3D(float x0, float y0, float y1, t_runtime *r);
float	my_fabs(float i);
void	playerrendering_3d(void *param, float xray);
int		charlen(char **tableau);
int		my_strlen(const char *chaine);
void	fov_rendering(t_runtime *r);
int		txt_wall_ort(t_runtime *r, float ysta, float yend);
void	parsing(t_runtime *r, char *filename);
void	minisiderowsl2(t_runtime *r, int i, int j);
void	minisiderowsl3(t_runtime *r, int i, int j);
void	init_ppos(t_runtime *r);
t_point	calcul_1(t_point wall, t_point play, float dir, t_runtime *r);
t_point	calcul_2(t_point wall, t_point play, float dir, t_runtime *r);
t_point	calcul_3(t_point wall, t_point play, float dir, t_runtime *r);
t_point	calcul_4(t_point wall, t_point play, float dir, t_runtime *r);
t_point	calcul_12(t_point wall, t_point play, float dir, t_runtime *r);
t_point	calcul_22(t_point wall, t_point play, float dir, t_runtime *r);
t_point	calcul_32(t_point wall, t_point play, float dir, t_runtime *r);
t_point	calcul_42(t_point wall, t_point play, float dir, t_runtime *r);
float	calcul_teta(float dir, t_point play, int x_wall, int y_wall);
void	d_handler(t_runtime *r);
void	r_arrow_handle(t_runtime *r);
void	l_arrow_handle(t_runtime *r);
void	p_posini(t_runtime *r);
int		calcul_max_l(char **strings);

#endif