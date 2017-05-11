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

void RGBtoHSB(int r, int g, int b, float *vals)
{
	float hue, saturation, brightness;
	int cmax = (r > g) ? r : g;
	if (b > cmax)
		cmax = b;
	int cmin = (r < g) ? r : g;
	if (b < cmin)
		cmin = b;

	brightness = ((float) cmax) / 255.0f;
	if (cmax != 0)
		saturation = ((float) (cmax - cmin)) / ((float) cmax);
	else
		saturation = 0;
	if (saturation == 0)
		hue = 0;
	else {
		float redc = ((float) (cmax - r)) / ((float) (cmax - cmin));
		float greenc = ((float) (cmax - g)) / ((float) (cmax - cmin));
		float bluec = ((float) (cmax - b)) / ((float) (cmax - cmin));
		if (r == cmax)
			hue = bluec - greenc;
		else if (g == cmax)
			hue = 2.0f + redc - bluec;
		else
			hue = 4.0f + greenc - redc;
		hue = hue / 6.0f;
		if (hue < 0)
			hue = hue + 1.0f;
	}
	vals[0] = hue;
	vals[1] = saturation;
	vals[2] = brightness;
}
