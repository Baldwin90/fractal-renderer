/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:49:40 by achi              #+#    #+#             */
/*   Updated: 2017/01/30 15:49:42 by achi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Math.h>
#include <stdio.h>
#include <libft.h>
#include <fractal.h>

#define SET_RGB(r,rv,g,gv,b,bv) *(r)=(rv);*(g)=(gv);*(b)=(bv)
#define CONVERT(c) ((int)((c) * 255.0f + 0.5f))
void set_rgb_vals(int *r, int *g, int *b, float x[])
{
	if ((int)x[0] == 0)
	{
		SET_RGB(r, CONVERT(x[4]), g, CONVERT(x[3]), b, CONVERT(x[1]));
	}
	else if ((int)x[0] == 1)
	{
		SET_RGB(r, CONVERT(x[2]), g, CONVERT(x[4]), b, CONVERT(x[1]));
	}
	else if ((int)x[0] == 2)
	{
		SET_RGB(r, CONVERT(x[1]), g, CONVERT(x[4]), b, CONVERT(x[3]));
	}
	else if ((int)x[0] == 3)
	{
		SET_RGB(r, CONVERT(x[1]), g, CONVERT(x[2]), b, CONVERT(x[4]));
	}
	else if ((int)x[0] == 4)
	{
		SET_RGB(r, CONVERT(x[3]), g, CONVERT(x[1]), b, CONVERT(x[4]));
	}
	else if ((int)x[0] == 5)
	{
		SET_RGB(r, CONVERT(x[4]), g, CONVERT(x[1]), b, CONVERT(x[2]));
	}
}

#define RETURN_RGB(r,g,b) return (((r)<<16)|((g)<<8)|(b));
#define RETURN_RGBS(rgb) RETURN_RGB(rgb,rgb,rgb);

int HSBtoRGB(float hsb[])
{
	int rgb[3];
	int h;
	int f;

	if (hsb[1] == 0)
		RETURN_RGBS((int)(hsb[2] * 255.0f + 0.5f));
	h = (hsb[0] - floor(hsb[0])) * 6.0f;
	f = h - floor(h);
	set_rgb_vals(&rgb[0], &rgb[1], &rgb[2], (float[]) \
		{h, hsb[2] * (1.0f - hsb[1]), hsb[2] * (1.0f - hsb[1] * f), \
			hsb[2] * (1.0f - (hsb[1] * (1.0f - f))), hsb[2]});
	RETURN_RGB(rgb[0], rgb[1], rgb[2]);
}

typedef union	u_dat
{
	int		i;
	float	f;
	char	*str;
} 				t_dat;  

#define SET_RGBC(r,rv,g,gv,b,bv) SET_RGBV(r,rv);SET_RGBV(g,gv);SET_RGBV(b,bv);
#define SET_RGBV(idx,vc) (v[idx].f)=((float)(v[0].i-(vc)))/((float)(v[0].i-v[1].i))

void RGBtoHSB(int r, int g, int b, float *hsb)
{
	t_dat	v[5];

	v[0].i = (r > g) ? r : g;
	if (b > v[0].i)
		v[0].i = b;
	v[1].i = (r < g) ? r : g;
	if (b < v[1].i)
		v[1].i = b;
	hsb[2] = ((float)v[0].i) / 255.0f;
	if (v[0].i != 0)
		hsb[1] = ((float)(v[0].i - v[1].i)) / ((float)v[0].i);
	else
		hsb[1] = 0;
	if (hsb[1] == 0)
		hsb[0] = 0;
	else
	{
		SET_RGBC(2, r, 3, g, 4, b);
		if (r == v[0].i)
			hsb[0] = v[4].f - v[3].f;
		else if (g == v[0].i)
			hsb[0] = 2.0f + v[2].f - v[4].f;
		else
			hsb[0] = 4s.0f + v[3].f - v[2].f;
		hsb[0] = hsb[0] / 6.0f;
		if (hsb[0] < 0)
			hsb[0] = hsb[0] + 1.0f;
	}
}
