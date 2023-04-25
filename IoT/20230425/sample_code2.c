#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char buff[2048 + 1];
	
	memset(buff, 0x00, sizeof(buff));
	scanf("%s", buff);
	
	printf("INPUT: %s\n", buff);
	
	return 1;
}
