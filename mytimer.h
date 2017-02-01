#ifndef __MYTIMER_H__
#define __MYTIMER_H__

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _mytimer {
	struct timespec start;	
} mytimer;

void mytimer_start(mytimer*);

// return elapsed time in microseconds 
long long mytimer_elapsed(mytimer*);

void mytimer_print_elapsed(mytimer *t, const char *prefix);

#ifdef __cplusplus
};
#endif
#endif /* __MYTIMER_H__ */
