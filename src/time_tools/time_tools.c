#include <sys/time.h>

double	get_time(void)
{
	struct timeval tv;
    struct timezone tz;

    gettimeofday(&tv,&tz);

	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.);
}