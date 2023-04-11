#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	time_t t;
	
	time_t temp;
	
	temp = time(&t);
	
	printf("%u\n", (unsigned)t);
	printf("%ld\n", temp);
		
	return 0;
}
