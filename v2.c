#include <stdio.h>
#include "common.h"
#include "mytimer.h"

static uint8_t gamma_correction(int pixel, uint8_t *eq_gamma, int bin_width);
uint8_t loop4_v2(Argument *arg);

int main(int argc, char* argv[])
{
	Argument arg;
	mytimer timer;
	// microseconds
	long long duration_us = 0;
	// default time range: 10 sec
	long long until = 1000 * 1000 * 10;

	init(&arg, HEIGHT, WIDTH);

	mytimer_start(&timer);
	while (duration_us < until)
	{
		printf("%0x\n", loop4_v2(&arg));
		update_SrcRGB(&arg);
		duration_us = mytimer_elapsed(&timer);
	}

	destroy(&arg);
	return 0;

}

uint8_t loop4_v2(Argument *arg)
{
	uint16_t * __restrict pSrcRGB = arg->SrcRGB;
	uint8_t *__restrict pDstRGB = arg->DstRGB;
	uint16_t height = arg->height;
	uint16_t width = arg->width;
	uint8_t bin_width = 8;
	uint8_t eq_gamma[257] = {0, };

	mytimer timer;

	get_eq_gamma(eq_gamma, arg);

	// for identifying loop execution in timeline view of DS-5 
	// sleep 10 ms
	usleep(10*1000);

	mytimer_start(&timer);
	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			uint16_t r, g, b;
			uint8_t  *out_r, *out_g, *out_b;
			r = pSrcRGB[(i*width+j)*3 + R_IDX];
			g = pSrcRGB[(i*width+j)*3 + G_IDX];
			b = pSrcRGB[(i*width+j)*3 + B_IDX];

			r = ((r * BRIGHTNESS) >> 7);
			g = ( g * BRIGHTNESS) >> 7;
			b = ((b * BRIGHTNESS) >> 7);


			out_r = &pDstRGB[(i*width+j)*3 + R_IDX];
			out_g = &pDstRGB[(i*width+j)*3 + G_IDX];
			out_b = &pDstRGB[(i*width+j)*3 + B_IDX];
		
			*out_r = gamma_correction(r, eq_gamma, bin_width);
			*out_g = gamma_correction(g, eq_gamma, bin_width);
			*out_b = gamma_correction(b, eq_gamma, bin_width);
		}
	}
	mytimer_print_elapsed(&timer, "loop in v2");

	// sleep 10 ms
	usleep(10*1000);

	return do_useless(arg);
}

static uint8_t gamma_correction(int pixel, uint8_t *eq_gamma, int bin_width)
{
	int idx;
	uint8_t out;
	
	idx = pixel >> bin_width;
	out = (((eq_gamma[idx+1] - eq_gamma[idx]) * (pixel&255)) >> bin_width) + eq_gamma[idx];
	return out;
}
