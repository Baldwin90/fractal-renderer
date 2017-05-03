#include <fractal.h>
#include <mlx.h>
#include <libft.h>

t_mapdata		*data_create(void)
{
	t_mapdata *data;

	data = ft_memalloc(sizeof(*data));
	data->draw_stats = 1;
	data->window = ft_memalloc(sizeof(*(data->window)));
	data->zoom = 1;
	data->julia_param_real = -0.8;
	data->julia_param_imaginary = 0.156;
	return (data);
}

void			window_free(t_windata *w) {
	mlx_destroy_image(w->mlx, w->img);
	mlx_destroy_window(w->mlx, w->win);
	free(w);
}

void			data_free(t_mapdata *data) {
	window_free(data->window);
	free(data);
}


void	create_mlx(t_mapdata *data)
{
	data->window->mlx = mlx_init();
	data->window->win = mlx_new_window(data->window->mlx, SCREENSIZE, SCREENSIZE, "Fract'ol");
	data->window->img = mlx_new_image(data->window->mlx, SCREENSIZE, SCREENSIZE);
	data->window->pixel = mlx_get_data_addr(data->window->img, &(data->window->bpp), &(data->window->line_size), &(data->window->endian));
	data->window->bpp /= 8;
	mlx_expose_hook(data->window->win, &draw_image, data);
}

void balance_center(t_mapdata *data) {
	if (data->x > 2) {
		data->x = 2;
	} else if (data->x < -2) {
		data->x = -2;
	}
	if (data->y > 2) {
		data->y = 2;
	} else if (data->y < -2) {
		data->y = -2;
	}
}

int key_hook(int key_code, t_mapdata *data)
{
	if (key_code == 53) {
		data_free(data);
		exit(1);
	} else if (key_code == 15) {
		data->zoom = 1;
		data->x = 0;
		data->y = 0;
		data->julia_param_real = -0.8;
		data->julia_param_imaginary = 0.156;
		draw_fractal(data);
	} else if (key_code == 126) {
		data->y -= data->zoom * 0.1;
		balance_center(data);
		draw_fractal(data);
	} else if (key_code == 125) {
		data->y += data->zoom * 0.1;
		balance_center(data);
		draw_fractal(data);
	} else if (key_code == 123) {
		data->x -= data->zoom * 0.1;
		balance_center(data);
		draw_fractal(data);
	} else if (key_code == 124) {
		data->x += data->zoom * 0.1;
		balance_center(data);
		draw_fractal(data);
	} else if (key_code == 13) {
		data->julia_param_imaginary += 0.01;
		draw_fractal(data);
	} else if (key_code == 1) {
		data->julia_param_imaginary -= 0.01;
		draw_fractal(data);
	} else if (key_code == 0) {
		data->julia_param_real -= 0.01;
		draw_fractal(data);
	} else if (key_code == 2) {
		data->julia_param_real += 0.01;
		draw_fractal(data);
	}
	return(0);
}

int mouse_hook(int button, int x, int y, t_mapdata *data) {
	if (button == 4) {
		data->zoom *= 0.9;
		data->x += ((double)x / SCREENSIZE - 0.5) * data->zoom;
		data->y += ((double)y / SCREENSIZE - 0.5) * data->zoom;
		balance_center(data);
		draw_fractal(data);
	} else if (button == 5) {
		data->zoom *= 1.11;
		data->x += ((double)x / SCREENSIZE - 0.5) * data->zoom;
		data->y += ((double)y / SCREENSIZE - 0.5) * data->zoom;
		switch (data->type) {
			case 0:
				if (data->zoom > 1) {
					data->zoom = 1;
				}
				break;
			case 1:
				if (data->zoom > 3) {
					data->zoom = 3;
				}
				break;
		}
		balance_center(data);
		draw_fractal(data);
	} else if (button == 1) {
		data->mouse_clicked = 1;
		data->mouse_x_last = x;
		data->mouse_y_last = y;
	}
	return (0);
}

int mouse_release_hook(int button, int x, int y, t_mapdata *data) {
	(void)x;
	(void)y;
	if (button == 1) {
		data->mouse_clicked = 0;
	}
	return (0);
}

int motion_hook(int x, int y, t_mapdata *data) {
	if (data->type == 1) {
		if (data->mouse_clicked) {
			int dx = x - data->mouse_x_last;
			int dy = y - data->mouse_y_last;

			data->julia_param_real += (float)dx / SCREENSIZE * 0.1;
			data->julia_param_imaginary += (float)dy / SCREENSIZE * 0.1;
			draw_fractal(data);


			data->mouse_x_last = x;
			data->mouse_y_last = y;
		}
	}
	return (0);
}

int main(int argc, char *argv[])
{
	if (argc == 1) {
		ft_printf("Usage: %s [mandlebrot, julia, burningship]\n", argv[0]);
		return (1);
	}
	int type = -1;
	ft_strlowcase(&(argv[1][0]));
	if (!ft_strcmp(argv[1], "mandlebrot")) {
		type = 0;
	} else if (!ft_strcmp(argv[1], "julia")) {
		type = 1;
	} else if (!ft_strcmp(argv[1], "burningship")) {
		type = 2;
	} else {
		ft_printf("Usage: %s [mandlebrot, julia, burningship]\n", argv[0]);
		return (1);
	}
	t_mapdata *data = data_create();
	data->type = type;

	create_mlx(data);

	draw_fractal(data);

	mlx_mouse_hook(data->window->win, &mouse_hook, data);
	mlx_key_hook(data->window->win, &key_hook, data);
	mlx_hook(data->window->win, 6, 0, motion_hook, data);
	mlx_hook(data->window->win, 5, 0, mouse_release_hook, data);

	mlx_loop(data->window->mlx);
	return (0);
}