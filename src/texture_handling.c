#include "../includes/Cub3D.h"

void load_textures(t_runtime *r)
{
  int crd = NO;
  
  r->txt_d[crd].img = malloc(sizeof(t_img*) * 4);
  while (crd <= WE)
  {
        r->txt_d[crd].img = mlx_xpm_file_to_image(r->mlx, r->txtrs[crd].path, &r->txt_d[crd].width, &r->txt_d[crd].height);
    if(!r->txt_d[crd].img)
    {
      printf("Error: Unable to load \"%s\"\n", r->txtrs[crd].path);
      exit(1);
    }
      printf("Texture path = %s\n", r->txtrs[crd].path);
    r->txt_d[crd].addr = mlx_get_data_addr(r->txt_d[crd].img, &r->txt_d[crd].bpp, &r->txt_d[crd].line_length, &r->txt_d[crd].endian);
    crd++;
  }
}       


int txt_wall_ort(t_runtime *r, float ysta, float yend)
{
  (void)ysta;(void)yend;
  if (r->line.ort == N && roundf(ysta) != roundf(yend))
  {
    return (NO);
  }
  else if (r->line.ort == S && roundf(ysta) != roundf(yend))
  {
    return(SO);
  }
  else if (r->line.ort == E && roundf(ysta) != roundf(yend))
  {
    return(EA);

  }
  else if (r->line.ort == O && roundf(ysta) != roundf(yend))
  {
    return(WE);
  }
  printf("ooook\n");
  printf("ort = %d\n", r->line.ort);
  printf("dire = %f\n", r->line.rad_fov);
  exit(1);
}

void  texture_to_image(t_runtime  *r, int txt, float tex_y, float tex_x, float xray, int startY)
{
  char   *pixel;
  int   color;

  pixel = r->txt_d[txt].addr + ((int)(tex_y) * (int)r->txt_d[txt].line_length + (int)tex_x * (int)r->txt_d[txt].bpp /8);
  color = *(int *)pixel;
  my_mlx_pixel_put(r, (int)xray, startY, color);
}

float wallx_determination_2(t_runtime *r, float ysta, float yend, int txt)
{
  if (r->line.ort == N && ysta <= yend)
  {
    return (CASE_SIZE - (int)(r->line.end_fov.x * r->txt_d[txt].width / 5) % r->txt_d[txt].width);
  }
  else if (r->line.ort == S && ysta <= yend)
  {
    return((int)(r->line.end_fov.x * r->txt_d[txt].width / 5) % r->txt_d[txt].width);
  }
  else if (r->line.ort == E && ysta <= yend)
  {
    return((int)(r->line.end_fov.y * r->txt_d[txt].width / 5) % r->txt_d[txt].width);

  }
  else if (r->line.ort == O && ysta <= yend)
  {
    return(CASE_SIZE - (int)(r->line.end_fov.y * r->txt_d[txt].width / 5) % r->txt_d[txt].width);
  
  }
  printf("ort = %d\n", r->line.ort);
  printf("dire = %f\n", r->line.rad_fov);
  exit(1);
}


typedef struct s_coord
{
  int a;
  int b;
}       t_coord;

int	c_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static int	_get_pos_in_texture(t_coord line_coords, int i, int tex_width)
{
	float	pos;

	pos = (float)(i - line_coords.a) / (line_coords.b - line_coords.a);
	pos = pos * tex_width;
	return (c_min((int)pos, tex_width - 1));
}

void draw_textured_wall(t_runtime *r, int startY, int endY, int txt, float height, float xray)
{
	float	tex_y;
	float	tex_x;
	float	wallX;
	t_coord	line;

	line.a = (-height / 2) + (HEIGHT / 2);
	line.b = (height / 2) + (HEIGHT / 2);
	if (line.a < 0)
	{
		startY = 0;
	}
	else
		startY = line.a;
	if (line.b > HEIGHT -1)
	{
		endY = HEIGHT - 1;
	}
	else
		endY = line.b;
	tex_y = 0;
	wallX = wallx_determination_2(r, startY, endY, txt);
	tex_x = wallX;
	while (startY < endY && startY < HEIGHT)
	{
		texture_to_image(r, txt, _get_pos_in_texture(line, startY, r->txt_d[txt].width), tex_x, xray, startY);
		startY++;
		tex_y += r->txt_d[txt].height / (double)height;
	}
}
