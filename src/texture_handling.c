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

void  texture_to_image(t_runtime  *r, int txt, float texY, float texX, float xray, int startY)
{
  char   *pixel;
  int   color;

  pixel = r->txt_d[txt].addr + ((int)(texY) * (int)r->txt_d[txt].line_length + (int)texX * (int)r->txt_d[txt].bpp /8);
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

void draw_textured_wall(t_runtime *r, int startY, int endY, int txt, float height, float xray)
{
  float texY;
  float texX;
  float wallX;

  texY = 0;
  wallX = wallx_determination_2(r, startY, endY, txt);
  texX = wallX;
  if(height >= HEIGHT)
  {
    texY += (((r->txt_d[txt].height - HEIGHT) / 2) / height) * CASE_SIZE;
  }
  while (startY < endY && startY < HEIGHT && texY < r->txt_d[txt].height - 1)
  { 

    texture_to_image(r, txt, texY, texX, xray, startY);
  
    startY++;
    texY += r->txt_d[txt].height / (double)height;
  }
}