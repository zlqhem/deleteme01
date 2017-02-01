#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mytimer.h"

// return microseconds
static long long mydifftime(struct timespec end, struct timespec start)
{
	double diff_in_nano = 1000000000L * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	return diff_in_nano * 0.001;
}

void mytimer_start(mytimer* t)
{
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &t->start);
}

// return elapsed time in microseconds 
long long mytimer_elapsed(mytimer* t)
{
	struct timespec now;
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &now);
	return mydifftime(now, t->start);
}

void mytimer_print_elapsed(mytimer *t, const char *prefix)
{
	printf ("%s: %llu\n", prefix, mytimer_elapsed(t));
}
