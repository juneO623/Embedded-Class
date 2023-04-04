#include <stdio.h>		// puts()
#include <string.h>		// strlen()
#include <fcntl.h>		// O_RDONLY
#include <unistd.h>		// write(), close()

#define BUFF_SIZE 1024

int main(int argc, char* argv[])
{
	char buff[BUFF_SIZE];
	int fd1, fd2;
	
	printf("원본 파일 이름 : %s\n", argv[1]);
	
	printf("복사할 파일 이름 : %s\n", argv[2]);
	
	if (0 < (fd1 = open(argv[1], O_RDONLY))){
		read(fd1, buff, BUFF_SIZE);
		puts(buff);
		close(fd1);
		
		if (0 < (fd2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0644))){
			write(fd2, buff, strlen(buff));
			close(fd2);
		} else {
			printf("파일 열기에 실패했습니다.\n");
		}
	} else {
		printf("파일 열기에 실패했습니다.\n");
	}
	
	return 0;
	
}
