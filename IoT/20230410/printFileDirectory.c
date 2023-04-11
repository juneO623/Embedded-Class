#include <stdio.h>
#include <unistd.h>

#define PATH_MAX 4096

int main(int argc, char* argv[])
{
		
	char *curr_dir = getcwd(NULL, 0);
	
	int isExist = access(argv[1], 0);
	
	if (isExist == -1) {
		printf("해당 파일/폴더가 존재하지 않습니다.\n");
		exit(1);
	}
	
	printf("%s/%s\n", curr_dir, argv[1]);
	free(curr_dir);
	
	return 0;
}
