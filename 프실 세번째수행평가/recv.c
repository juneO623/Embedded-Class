
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<signal.h>
#include<stdbool.h>
#include<sys/socket.h>
#include<sys/types.h>

#include<linux/if_packet.h>
#include<netinet/in.h>		 
#include<netinet/if_ether.h>    // for ethernet header
#include<netinet/ip.h>		// for ip header
#include<netinet/udp.h>		// for udp header
#include<netinet/tcp.h>
#include<arpa/inet.h>           // to avoid warning at inet_ntoa

#include <wiringPi.h>
#include <errno.h>

#include <wiringSerial.h>

struct sockaddr saddr;
struct sockaddr_in source,dest;

void recv_data_process(unsigned char* buffer,int buflen);

unsigned long baudrate = 9600;
char device[] = "/dev/ttyACM0";
	int fd;


int main()
{
	wiringPiSetup();
	pinMode(0, OUTPUT);
	pinMode(2, OUTPUT);
	
	
	fflush(stdout);
	if ((fd = serialOpen(device, baudrate)) < 0){
		fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
		exit(1); // error
	}

	int sock_recv,saddr_len,buflen;

	unsigned char* buffer = (unsigned char *)malloc(65536); 
	memset(buffer,0,65536);

	printf("starting .... \n");

	sock_recv=socket(AF_PACKET,SOCK_RAW,htons(ETH_P_ALL)); 
	if(sock_recv<0)
	{
		printf("error in socket\n");
		return -1;
	}

	while(1)
	{
		saddr_len=sizeof saddr;
		buflen=recvfrom(sock_recv,buffer,65536,0,&saddr,(socklen_t *)&saddr_len);

		if(buflen<0)
		{
			printf("error in reading recvfrom function\n");
			return -1;
		}

		//---------------------------------------
		recv_data_process(buffer,buflen);
		//---------------------------------------
	}

	close(sock_recv);// use signals to close socket 
	printf("DONE!!!!\n");
}


//================================================================


void recv_data_process(unsigned char* buffer,int buflen)
{
	/*
	int fd;
	if ((fd = serialOpen("/dev/ttyACM0", 9600)) < 0)
	{
		printf("file open error");
		return 1;
	}*/

	char str[6];
	int j=0;
	
	if(buffer[0] == 0xe4 && buffer[1] == 0x5f && buffer[2] == 0x01 && buffer[3] == 0x8e && buffer[4] == 0x98 && buffer[5] == 0xc6 && (buffer[36]<<8)|(buffer[37]) == 10004) 
	{
		j = 0;
		
		
		printf("Data : ");
		for(int i=42;i<49;i++){
			printf("%c ", buffer[i]);
			str[j] = buffer[i];
			j++;
		}
		printf(" ");
		printf("%s", str);
		
			printf("gdgdgdgdgdgdgdgdgdgd");
			if (strcmp(str, "led1on")==0){
				printf("1on");
				serialPuts(fd, "1");
				//digitalWrite(0, HIGH);
			} else if (strcmp(str, "led1of")==0){
				printf("1of");
				serialPuts(fd, "2");
				//digitalWrite(0, LOW);
			} else if (strcmp(str, "led2on")==0){
				printf("2on");
				serialPuts(fd, "3");
				//digitalWrite(2, HIGH);
			} else if (strcmp(str, "led2of")==0){
				printf("2of");
				serialPuts(fd, "4");
				//digitalWrite(2, LOW);
			} else if (strcmp(str, "smolef")==0){
				printf("servo left");
				serialPuts(fd, "5");
				//softPwmCreate(1, 0, 200);
				//softPwmWrite(1, 25);
			} else if (strcmp(str, "smorit")==0){
				printf("servo right");
				serialPuts(fd, "6");
				//softPwmCreate(1, 0, 200);
				//softPwmWrite(1, 5);
			}
		
		/*
		serialPuts(fd, str);
		serialFlush(str);
		*/
		
		/*
		printf(" ");
		printf(str);
		*/
		
		printf("\n");
	}
}
