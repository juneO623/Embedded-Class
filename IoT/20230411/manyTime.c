#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
	char buf[256];
	
	time_t timetime;
	time(&timetime);
	
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	
	struct tm *t;
	time_t now = time(NULL);
	t = localtime(&now);
	
	strftime(buf, sizeof(buf), "strftime : %c", t);
	
	printf("time : %u\n", timetime);
	printf("gettimeofday : %ld/%ld\n", currentTime.tv_sec, currentTime.tv_usec);
	printf("ctime : %s", ctime(&timetime));
	printf("asctime : %s", asctime(t));
	puts(buf);

	
	return 0;
}
