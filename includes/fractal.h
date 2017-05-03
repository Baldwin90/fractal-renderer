#ifndef FRACTAL_H
# define FRACTAL_H

#define SCREENSIZE 840
#define SCREENSIZE_F 840.0

#define LERP(a, b, t) (a + (b - a) * (t - (int)t))
#define ABS(x) (x) > 0 ? (x) : -(x)

#define NUM_THREADS 30

typedef struct	s_windata
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*pixel;
	int			bpp;
	int			line_size;
	int			endian;
}				t_windata;

typedef struct	s_mapdata
{
	char		draw_stats;
	char		type;
	float		x;
	float		y;
	float		zoom;
	int			max_iterations;
	float		julia_param_real;
	float		julia_param_imaginary;
	char		mouse_clicked;
	short		mouse_x_last;
	short		mouse_y_last;
	t_windata	*window;
}				t_mapdata;

typedef struct	s_thread_params
{
	t_mapdata	*data;
	float		start_y;
	float		end_y;
}				t_thread_params;

float			lerp_angle(float a, float b, float t);
void			HSBLerp(float a[], float b[], float t, float *vals);
int				HSBtoRGB(float hsbvals[]);
void			RGBtoHSB(int r, int g, int b, float *vals);
void			draw_mandlebrot(t_mapdata *data);
void			draw_burningship(t_mapdata *data);
void			draw_julia(t_mapdata *data);

void			draw_pixel(t_windata *data, int x, int y, int color);
int				draw_image(t_mapdata *data);
int				draw_fractal(t_mapdata *data);

#endif