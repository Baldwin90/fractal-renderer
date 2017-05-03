#include <mlx.h>
#include <fractal.h>

void	draw_pixel(t_windata *data, int x, int y, int color)
{
	if (x < 0 || x >= SCREENSIZE || y < 0 || y >= SCREENSIZE)
		return ;
	*((int *)(data->pixel + ((x + y * SCREENSIZE) * data->bpp))) = color;
}

int	draw_image(t_mapdata *data)
{
	mlx_clear_window(data->window->mlx, data->window->win);
	mlx_put_image_to_window(data->window->mlx, data->window->win, data->window->img, 0, 0);
	return (0);
}

int draw_fractal(t_mapdata *data)
{
	switch (data->type) {
		case 0:
			draw_mandlebrot(data);
			return(0);
		case 1:
			draw_julia(data);
			return(0);
		case 2:
			draw_burningship(data);
			return(0);
		default:
			draw_mandlebrot(data);
			return(0);
	}
}
