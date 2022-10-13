
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<errno.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<sys/ioctl.h>

#include<net/if.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<netinet/if_ether.h>
#include<netinet/udp.h>

#include<linux/if_packet.h>

#include<arpa/inet.h>

#include<unistd.h>


struct ifreq ifreq_i;
int sock_raw;
unsigned char *sendbuff;
int total_len=0,send_len;

struct sockaddr_ll sadr_ll;

void send_data_process();

//--------------------------------
char *eth_dev_name = "ens33";
int buff_len = 64;
//--------------------------------

void get_eth_index()
{
	memset(&ifreq_i,0,sizeof(ifreq_i));
	strncpy(ifreq_i.ifr_name,eth_dev_name,IFNAMSIZ-1);

	if((ioctl(sock_raw,SIOCGIFINDEX,&ifreq_i))<0)
		printf("error in index ioctl reading");

	printf("index=%d\n",ifreq_i.ifr_ifindex);
}

int send_net(unsigned char *sendbuff, int buff_len)
{
	int send_len = 0;
	send_len = sendto(sock_raw,sendbuff,buff_len,0,(const struct sockaddr*)&sadr_ll,sizeof(struct sockaddr_ll));
	return send_len;
}


int count = 0;

int main()
{
	sock_raw=socket(AF_PACKET,SOCK_RAW,IPPROTO_RAW);
	if(sock_raw == -1)
		printf("error in socket");

	sendbuff=(unsigned char*)malloc(buff_len); // increase in case of large data.Here data is --> AA  BB  CC  DD  EE
	memset(sendbuff,0,buff_len);

	get_eth_index();  // interface number

	sadr_ll.sll_ifindex = ifreq_i.ifr_ifindex;
	sadr_ll.sll_halen   = ETH_ALEN;

	send_data_process();
}

//===========================================================


void buff_init()
{
	// Destination MAC Address : 00:01:02:03:04:05
	sendbuff[0]  = 0x00;
	sendbuff[1]  = 0x01;
	sendbuff[2]  = 0x02;
	sendbuff[3]  = 0x03;
	sendbuff[4]  = 0x04;
	sendbuff[5]  = 0x05;	
	// Source MAC Address : 00:0c:29:92:6a:6c
	sendbuff[6]  = 0x06;
	sendbuff[7]  = 0x07;
	sendbuff[8]  = 0x08;
	sendbuff[9]  = 0x09;
	sendbuff[10]  = 0x0a;
	sendbuff[11]  = 0x0b;
	// Type = ARP : 0x0806, IP : 0x0800
	sendbuff[12]  = 0x08;
	sendbuff[13]  = 0x00;
}



void send_data_process()
{

	buff_init();

	printf("sending...\n");
	while(1)
	{
		send_len = send_net(sendbuff, buff_len);
		if(send_len<0)
		{
			printf("sendlen=%d....errno=%d\n",send_len,errno);
			return -1;
		}

		printf("count = %d\n", count++);
		usleep(1000000);
	}
}
