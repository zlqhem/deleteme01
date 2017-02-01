#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include "common.h"

static uint16_t *frames = NULL;
static int max_frame = 5;
static int src_idx = 0;

void init(Argument *arg, int width, int height)
{
	arg->width = width;
	arg->height = height;
	arg->DstRGB = (uint8_t*)calloc(sizeof(uint8_t), width*height*3);
	
	uint16_t pixel = 0;
	frames = (uint16_t*)calloc(width*height*max_frame, sizeof(uint16_t));

	for (int f=0; f<max_frame; f++)
	{
		for (int i=0; i<width*height; i++)
		{
			 frames[f*width*height+i] = pixel++ % (1<<20-1);
		}
	}
	update_SrcRGB(arg);
}

void update_SrcRGB(Argument *arg)
{
	++src_idx;
	arg->SrcRGB = &frames[src_idx % max_frame];
}

void destroy(Argument *arg)
{
	free(frames);
	free(arg->DstRGB);
}

uint8_t do_useless(Argument *arg)
{
	uint8_t ret = 0;
	uint8_t *p = arg->DstRGB;
	for (int i=0; i<arg->height; i++)
	{
		for (int k=0; k<arg->width; k++)
		{
			for (int m=0; m<3; m++)
			{
				ret += *p++ % 256;
			}
		}
	}
	return ret;
}

// @param eq_gamma size should be 257 bytes
void get_eq_gamma(uint8_t *eq_gamma, Argument *arg)
{
	int i, j;
	
	uint16_t width = arg->width;
	uint16_t height = arg->height;
	int bin_width = 8;
	int hist_size = 256;
	uint16_t *pSrcRGB = arg->SrcRGB;
	
	uint32_t hist[256] = {0, };
	uint32_t cdf[256] = {0, };
	//uint8_t eq_gamma[257] = {0, };
	
	for(i=200; i<height; i+=2)
	{
		for(j=0; j<width; j+=2)
		{
			hist[pSrcRGB[(i*width+j)*3 + G_IDX]>>bin_width]++;
		}
	}
	
	uint32_t tmp_hist = 0;
	uint32_t hist_clip = 4000;
	
	for(i=0; i<hist_size; i++)
	{
		tmp_hist += (uint32_t)sqrt(std::min(hist[i], hist_clip));
		cdf[i] = tmp_hist;
	}

	for(i=0; i<hist_size; i++)
	{
		eq_gamma[i] = (uint8_t)(255*cdf[i]/cdf[hist_size-1]);
	}
	
	eq_gamma[0] = 0;
	eq_gamma[hist_size] = 255;
}


