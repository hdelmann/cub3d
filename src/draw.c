#include "../includes/Cub3D.h"

void my_mlx_draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}



int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_line_r(t_runtime *game, int x0, int y0, double angle) {
    int x1 = x0 + (int)(60 * cos(angle) * WIDTH);
    int y1 = y0 + (int)(60 * sin(angle) * HEIGHT);
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
		if (x0 < 0 || x0 >= WIDTH || y0 < 0 || y0 >= HEIGHT) {
            break;
        }
			// my_mlx_put_pixel(game->img, game->player.Prevx, game->player.Prevy, get_rgba(0, 0, 0, 0));
      		my_mlx_put_pixel(game->img, x0, y0, get_rgba(0, 255, 0, 255));
			// game->player.Prevx = x0;
			// game->player.Prevy = 
        if (x0 == x1 && y0 == y1) break;

        e2 = err;

        if (e2 > -dx) {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dy) {
            err += dx;
            y0 += sy;
        }
    }
}

void draw_line(mlx_image_t *img, int x0, int y0, double angle) {
    int x1 = x0 + (int)(60 * cos(angle) * 100);
    int y1 = y0 + (int)(60 * sin(angle) * 100);

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int error = dx - dy;
    int current_x = x0;
    int current_y = y0;

    while (1) {
       	my_mlx_put_pixel(img, current_x, current_y, get_rgba(255, 0, 0, 255));

        if (current_x == x1 && current_y == y1) {
            break;
        }

        int error2 = error * 2;

        if (error2 > -dy) {
            error -= dy;
            current_x += sx;
        }

        if (error2 < dx) {
            error += dx;
            current_y += sy;
        }
    }
}

int my_mlx_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if(!img || x > img->width || y > img->height)
	{
        printf("x = %d > %d\ny = %d > %d\n", x, 320, y, 200);
		printf("Error:  gros con POB!\n");
		exit (-1);
	}
	uint8_t *pixelbuff = &img->pixels[(y * img->width + x) * 4];
	my_mlx_draw_pixel(pixelbuff, color);
	return (0);
}