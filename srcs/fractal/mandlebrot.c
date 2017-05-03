#include <fractal.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>
#include <libft.h>

void *draw_mandlebrot_part(void *p) {
	t_thread_params	*params = (t_thread_params *)p;
	int max_itr = params->data->max_iterations;
	float x0;
	float y0;
	float x;
	float y;
	float z;
	float color_hue;
	float cache;
	float inverse_color = 1.0 / max_itr;
	float inverse_screen = 1.0 / SCREENSIZE;
	float cx = params->data->x;
	float cy = params->data->y;
	float zoom = params->data->zoom;
	float end_y = params->end_y + 1;
	int iteration;
	int color;
	t_windata *window = params->data->window;
	float sy, sx;

	for (sy = params->start_y - 1; sy < end_y; ++sy) {
		for (sx = -1; sx <= SCREENSIZE; ++sx) {
			x0 = cx + LERP(-2.5, 1.5,(sx * inverse_screen)) * zoom;
			y0 = cy + LERP(-2.0, 2.0,(sy * inverse_screen)) * zoom;
			x = 0;
			y = 0;
			iteration = 0;
			while ((z = (x * x + y * y)) <= 4 && iteration < max_itr)
			{
				cache = x * x - y * y + x0;
				y = x * y;
				y = y + y + y0;
				x = cache;
				++iteration;
			}
			if (iteration == max_itr) {
				color = 0;
			}
			else {
				color_hue = (iteration + 1 - log2(log2(ABS(z)))) * inverse_color;
				color = HSBtoRGB((float []){0.72 + color_hue, 1, 1});
			}
			draw_pixel(window, sx, sy, color);
		}
	}
	free(p);
	return(0);
}

void draw_mandlebrot(t_mapdata *data) {
	pthread_t threads[NUM_THREADS];

	data->max_iterations = 500;
	for (int x = 0; x < NUM_THREADS; x++) {
		t_thread_params *params = ft_memalloc(sizeof(*params));
		params->data = data;
		params->start_y = x * (SCREENSIZE / NUM_THREADS);
		params->end_y = (x + 1) * (SCREENSIZE / NUM_THREADS);
		pthread_create(&threads[x], NULL, draw_mandlebrot_part, (void *)params);
	}

	for (int x = 0; x < NUM_THREADS; x++) {
		pthread_join(threads[x], NULL);
	}
	draw_image(data);
}
