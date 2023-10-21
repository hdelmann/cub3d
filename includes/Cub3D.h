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
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <MLX42/MLX42.h>
#include <math.h>
#include "../getnext/get_next_line.h"

#define PLAYER_SIZE 10
#define CASE_SIZE 64
#define PI 3.141592653589793238462643383279502884197
#define HEIGHT 1080
#define WIDTH 1920

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
    int colums;
    int lines;
}   t_map;
typedef struct isomet
{
    float   x_iso;
    float   y_iso;
}   t_isomet;

typedef struct runetime
{
	t_map		map;
    t_line      line;
	t_player	player;
    mlx_t *mlx;
    mlx_t *mlx3;
    mlx_image_t *img;
    mlx_image_t *img3;
    t_isomet    iso;
    
}			t_runtime;


int parsing_map(char **map);
char *ft_strdup(char	*dst, char *src);
int	is_line_empty(char *str);
void    map_fill(t_runtime *r, int fd);
char	*ft_strdup_f(char *src);
void my_draw_line_fov(t_runtime *r);
char	**ft_realloc2(char **map, int i);
float* myReallocfloat(float *ptr, int Newsize);
void calcul_line_fovx(void *param);
void calcul_line_fovy(void *param);
char *replace_n_to_r(char *line);
int my_mlx_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
int get_rgba(int r, int g, int b, int a);
void fillcubeborder(t_runtime *r);
void playerendering2d(void *param);
void my_keyhook(mlx_key_data_t keydata, void *param);
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

#endif