#include "../includes/Cub3D.h"

void load_textures(t_runtime *r)
{
  int crd = NO;
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

void  texture_to_image(t_runtime  *r, int txt, float texY, float texX, float xray, int startY)
{
  char   *pixel;
  int   color;

  (void)txt;
  pixel = r->txt_d[txt].addr + ((int)texY * r->txt_d[txt].line_length + (int)texX * r->txt_d[txt].bpp / 8);
  color = *(int *)pixel;
  my_mlx_pixel_put(r, xray, startY, color);
}

int txt_wall_ort(t_runtime *r, float ysta, float yend)
{
  calort(r);
  if (r->line.ort2 == N && roundf(ysta) != roundf(yend))
  {
    return (NO);
  }
  else if (r->line.ort2 == S && roundf(ysta) != roundf(yend))
  {
    return(SO);
  }
  else if (r->line.ort2 == E && roundf(ysta) != roundf(yend))
  {
    return(EA);

  }
  else if (r->line.ort2 == O && roundf(ysta) != roundf(yend))
  {
    return(WE);
  }
  exit(1);
}

float wallx_determination(t_runtime *r, float ysta, float yend, int txt)
{
  calort(r);
  if (r->line.ort2 == N && roundf(ysta) != roundf(yend))
  {
    return ((int)(r->line.end_fov.x * r->txt_d[txt].width / 5) % r->txt_d[txt].width);
  }
  else if (r->line.ort2 == S && roundf(ysta) != roundf(yend))
  {
    return(CASE_SIZE - (int)(r->line.end_fov.x * r->txt_d[txt].width / 5) % r->txt_d[txt].width);
  }
  else if (r->line.ort2 == E && roundf(ysta) != roundf(yend))
  {
    return((int)(r->line.end_fov.y * r->txt_d[txt].width / 5) % r->txt_d[txt].width);

  }
  else if (r->line.ort2 == O && roundf(ysta) != roundf(yend))
  {
    return((int)(r->line.end_fov.y * r->txt_d[txt].width / 5) % r->txt_d[txt].width);
  }
  exit(1);
}

void draw_textured_wall(t_runtime *r, int startY, int endY, int txt, float height, float xray)
{
  float texY;
  float texX;
  float wallX;

  //txt = NO;
  wallX = wallx_determination(r, startY, endY, txt);
  texX = wallX;
  texY = 0;
 // txt_wall_ort(r, xray, startY, endY);
  if((double)height >= HEIGHT)
  {
    printf("iwashere\n");
    texY = ((((double) height - HEIGHT) / 2) / (double)height) * CASE_SIZE;
  }
  while (startY < endY && startY < HEIGHT && texY < r->txt_d[txt].height - 1)
  {
    texture_to_image(r, txt, texY, texX, xray, startY);
    startY++;
    texY += r->txt_d[txt].height / (double)height;
  }
}