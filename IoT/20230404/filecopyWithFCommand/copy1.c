#include <stdio.h>
#define BUFFER 1024

int main(int argc, char *argv[])
{
	
	if (argc != 3)
	{
		printf("사용법\n");
		printf("copyfile [source filename] [output filename]\n");
		return 0;
	}
	
	FILE* fpr = fopen(argv[1], "rb");
	FILE* fpw = fopen(argv[2], "wb");
	
	if (fpr == NULL || fpw == NULL) return 0;
	
	char file;
	
	while (!feof(fpr))
	{
		fread(&file, sizeof(char), 1, fpr);
		fwrite(&file, sizeof(char), 1, fpw);
	}
	
	fclose(fpr);
	fclose(fpw);
	
	return 0;	
	
}

