#ifndef CUB3D_H
#define Cub3D_H

#include <unistd.h>
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
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../mlx_linux/mlx.h"
#include <math.h>
#include "../getnext/get_next_line.h"

#define PLAYER_SIZE 10
#define CASE_SIZE 64
#define PI 3.141592653589793238462643383279502884197
#define HEIGHT 1080
#define WIDTH 1920
#define CHARSET "10NEWS"
#define PCHARSET "NEWS"
#define FLR 0
#define CEIL 1
#define ESC 65307
#define W 119
#define A 97
#define S 115
#define D 100
#define L_AR 65361
#define R_AR 65363

enum Textures{
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
    t_point pos;
    float pdir;
    float pdir_v;
    int dir;
    float FOV; 
}   t_player;

typedef struct s_line
{
    float dist;
    int ort;
    int ort2;
    t_point start;
    t_point end;
    float   rad_raystart;
    float   rad_raystart_v;
    float   rad_in;
    float rad_fov;
    t_point start_v;
    t_point end_v;
    t_point end_def;
    t_point start_fov;
    t_point end_fov;
    t_point end_fov2;
    t_point end_defov;
    float *tab_dist;
    float z;
}   t_line;

typedef struct s_map
{
    char **map;
    char **textures;
    int colums;
    int lines;
}   t_map;
typedef struct isomet
{
    float   x_iso;
    float   y_iso;
}   t_isomet;

typedef struct s_txt
{
    char            *path;
    void            *walltxt;
    char	        *addr;
	int		        bpp;
	int	        	line_length;
	int		        endian;
    unsigned int    c_red;
    unsigned int    c_green;
    unsigned int    c_blue;
    unsigned int    trnpcy;
}              t_txt;


typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
    int     height;
    int     width;
	int		endian;
}           t_img;


typedef struct s_runtime
{
	t_map		map;
    t_line      line;
	t_player	player;
    void        *mlx;
    void        *mlx_win;
    void        *data;
    t_img       img;
    t_isomet    iso;
    t_txt      txtrs[4];
    t_img      txt_d[4];
    t_txt      color[2];
    char    *filename;
    int     coa;
    float      textY;
    float   *dist_tab;
}			t_runtime;

void freeTab(char **array, int size);
t_point calcul_inter(t_runtime *r, float dir);
void draw_textured_wall(t_runtime *r, int startY, int endY, int txt, float height, float xray);
void load_textures(t_runtime *r);
char	**ft_split(char const *s, char c);
int     my_mlx_put_pixel(t_runtime *r, uint32_t x, uint32_t y, uint32_t color);
int     parse_txt(t_runtime *r);
void	my_mlx_pixel_put(t_runtime *r, int x, int y, int color);
void	file_parsing(t_runtime *r);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int     check_map_t(char **map, char *valid_chars);
int     filename_check(char *filename);
int     check_invalid_mapt(t_runtime *r);
int     is_map_surrounded(t_runtime *r);
int     parsing_map(t_runtime *r);
char    *ft_strdup(char	*dst, char *src);
char *ft_strdup_ff(char	*dst, char *src);
int	    is_line_empty(char *str);
void     map_fill(t_runtime *r, int fd);
char	*ft_strdup_f(char *src);
void my_draw_line_fov(t_runtime *r);
char	**ft_realloc2(char **map, int i);
float* myReallocfloat(float *ptr, int Newsize);
void calcul_line_fovx(void *param);
void calcul_line_fovy(void *param);
char *replace_n_to_r(char *line);
char **tab_inv(char **tab);
//void draw_textured_wall(t_runtime *r, int startY, int endY, int txt, float height, float tex_x);
//int my_mlx_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
void	my_mlx_pixel_put(t_runtime *r, int x, int y, int color);
int get_rgba(int r, int g, int b, int a);
void fillcubeborder(t_runtime *r);
int playerendering2d(t_runtime *r);
void calort(void *param);
int my_keyhook(int keydata, t_runtime *r);
float calucl_dist(float x0, float x1, float y0, float y1);
void calcul_line_interx(void *param, float x0, float y0);
void calcul_line_intery(void *param, float x0, float y0);
void my_draw_line(t_runtime *r);
void my_draw_line_3D(float x0, float y0, float y1, t_runtime *r);
float my_fabs(float i);
void    playerrendering3D(void *param, float xray);
int charlen(char** tableau);
int my_strlen(const char* chaine);
void fov_rendering(t_runtime *r);
int txt_wall_ort(t_runtime *r, float ysta, float yend);
void parsing(t_runtime *r, char *filename);
void init_Ppos(t_runtime *r);

#endif