#ifndef __COMMON_H__
#define __COMMON_H__

#define HEIGHT 720
#define WIDTH 1280
#define BRIGHTNESS 120
#define R_IDX	2
#define G_IDX	1
#define B_IDX	0

#include <unistd.h>
#include <stdint.h>

typedef struct _argument {
	uint16_t width;
	uint16_t height;
	uint16_t *SrcRGB;
	uint8_t *DstRGB;
} Argument;

#ifdef __cplusplus
extern "C" {
#endif
extern void init(Argument *arg, int width, int height);
extern void update_SrcRGB(Argument *arg);
extern void destroy(Argument *arg);
extern uint8_t do_useless(Argument *arg);

extern void get_eq_gamma(uint8_t *eq_gamma, Argument *arg);
#ifdef __cplusplus
}
#endif

#endif
