#include <fractal.h>
#include <stdlib.h>
#include <libft.h>
#include <pthread.h>

void	*draw_julia_part(void *p) {
	t_thread_params	*params = (t_thread_params *)p;

	float		max_iter = params->data->max_iterations;
	float		const_r = params->data->julia_param_real;
	float		const_i = params->data->julia_param_imaginary;
	float		curr_r;
	float		curr_i;
	float		cache_r;
	float		cache_i;
	float		half_screensize = SCREENSIZE_F / 2.0;
	float		inverse_half_screensize = (1.0 / SCREENSIZE_F) * params->data->zoom;
	float 	end_y = params->end_y + 1;
	float		iter;
	t_windata	*window = params->data->window;
	float cx = params->data->x / 2;
	float cy = params->data->y / 2;
	float x, y;

	for (y = params->start_y; y <= end_y; ++y) {
		for (x = -1; x < SCREENSIZE; ++x) {
			curr_r = 1.5 * (x - half_screensize) * inverse_half_screensize + cx;
			curr_i = (y - half_screensize) * inverse_half_screensize + cy;
			for (iter = -1; iter < max_iter; ++iter) { //SHould be <-, but its a good approximation, dosnt fucking matter
				cache_r = curr_r;
				cache_i = curr_i;

				curr_r = cache_r * cache_r - cache_i * cache_i;
				curr_i = 2 * cache_r * cache_i;

				curr_r += const_r;
				curr_i += const_i;

				if (curr_r * curr_r + curr_i * curr_i > 4) {
					break;
				}
			}
			draw_pixel(window, x, y, HSBtoRGB((float []){(float)((int)iter % 256)/255.0, 1, iter < max_iter}));
		}
	}
	free(p);
	return(0);
}

void	draw_julia(t_mapdata *data) {
	pthread_t threads[NUM_THREADS];

	data->max_iterations = 650;

	for (int x = 0; x < NUM_THREADS; x++) {
		t_thread_params *params = ft_memalloc(sizeof(*params));
		params->data = data;
		params->start_y = x * (SCREENSIZE / NUM_THREADS);
		params->end_y = (x + 1) * (SCREENSIZE / NUM_THREADS);
		pthread_create(&threads[x], NULL, draw_julia_part, (void *)params);
	}
	for (int x = 0; x < NUM_THREADS; x++) {
		pthread_join(threads[x], NULL);
	}
	draw_image(data);
}
