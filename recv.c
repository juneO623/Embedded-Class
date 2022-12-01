
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

int main()
{

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

	char str[23];
	int j=0;
	
//	if(buffer[0] == 0xFC && buffer[1] == 0xB3 && buffer[2] == 0xBC && buffer[3] == 0x4B && buffer[4] == 0xCC && buffer[5] == 0x15)
	if(buffer[0] == 0x00 && buffer[1] == 0x0C && buffer[2] == 0x29 && buffer[3] == 0x0F && buffer[4] == 0xC5 && buffer[5] == 0xF3) 
//		&& (buffer[6] == 0xFC && buffer[7] == 0xB3 && buffer[8] == 0xBC && buffer[9] == 0x4B && buffer[10] == 0xCC && buffer[11] == 0x15))
	{
		j = 0;
		
		printf("Ip Address : ");
		for (int i=26; i<30; i++) {
			printf("%d", buffer[i]);
			if (i != 29) printf(".");
		}
		
		printf("\n");
		
		printf("Port : ");
		printf("%d", buffer[36]<<8 | buffer[37]);
		printf("\n");
		
		printf("Data : ");
		for(int i=42;i<47;i++){
			printf("%c ", buffer[i]);
			str[j] = buffer[i];
			j++;
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
