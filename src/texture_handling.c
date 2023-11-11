// #include "../includes/Cub3D.h"

// void load_textures(t_runtime *r)
// {
//     printf("Texture path = %s\n", r->txtrs[NO].path);
//     xpm_t*  xpmNO = mlx_load_xpm42(r->txtrs[NO].path);
//     xpm_t*  xpmEA = mlx_load_xpm42(r->txtrs[EA].path);
//     xpm_t*  xpmWE = mlx_load_xpm42(r->txtrs[WE].path);
//     xpm_t*  xpmSO = mlx_load_xpm42(r->txtrs[SO].path);
// 		//exit(1);
//     if(!xpmNO || !xpmEA || !xpmWE || !xpmSO)
//         exit(printf("No textures were detected\n"));
//    // printf("yahallo\n");
//     r->txtrs[NO].walltxt = mlx_texture_to_image(r->mlx, &xpmNO->texture);
//     r->txtrs[EA].walltxt = mlx_texture_to_image(r->mlx, &xpmEA->texture);
//     r->txtrs[WE].walltxt = mlx_texture_to_image(r->mlx, &xpmWE->texture);
//     r->txtrs[SO].walltxt = mlx_texture_to_image(r->mlx, &xpmSO->texture);
//     if(!r->txtrs[NO].walltxt || !r->txtrs[EA].walltxt || !r->txtrs[WE].walltxt || !r->txtrs[SO].walltxt )
//         exit(printf("Error: Textures failed to load\n"));
// }       

// void  texture_to_image(t_runtime  *r, int txt, int texY, int texX, int xray, int startY)
// {
//   int   pixel;
//   int   color;


//   pixel = (texY * r->txtrs[txt].walltxt->width + texX) * sizeof(int32_t);
//   color = *(int32_t *)(r->txtrs[txt].walltxt->pixels + pixel);
//   //*(int32_t *)(r->txtrs[txt].walltxt->pixels + )
//   my_mlx_put_pixel(r->img, xray, startY, color);
// }

// void draw_textured_wall(t_runtime *r, int startY, int endY, int txt, float height, float xray)
// {
//   int texY;
//   int texX;
//   float wallX;

//   wallX = (int)r->line.end_fov.x % CASE_SIZE;
//   texX = r->txtrs[txt].walltxt->width * wallX;
//   texY = 0;
//   while (startY < endY && startY < HEIGHT && texY < (int)r->txtrs[txt].walltxt->height - 1)
//   {
//     texture_to_image(r, txt, texY, texX, xray, startY);
//     startY++;
//     texY += r->txtrs[txt].walltxt->height / (double)height;
//   }
// }