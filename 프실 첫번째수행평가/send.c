
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

#include <stdbool.h>


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
int cnt = 0;

unsigned short checksum(unsigned short* buff, int len_16)
{
   unsigned long sum = 0;

   for(int i = 0;i < len_16>0;i++)
      sum+=htons(*(buff)++);   
   do
   {
      sum = ((sum >> 16) + (sum & 0xFFFF));
   }
   while(sum & 0xFFFF0000);

   return (~sum);
}


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
   // Destination MAC Address
   sendbuff[0]  = 0xFC;
   sendbuff[1]  = 0xB3;
   sendbuff[2]  = 0xBC;
   sendbuff[3]  = 0x4B;
   sendbuff[4]  = 0xCC;
   sendbuff[5]  = 0x15;
   // Source MAC Address
   sendbuff[6]  = 0x06;
   sendbuff[7]  = 0x07;
   sendbuff[8]  = 0x08;
   sendbuff[9]  = 0x09;
   sendbuff[10]  = 0x0a;
   sendbuff[11]  = 4;

   // Type = ARP : 0x0806, IP : 0x0800
   sendbuff[12]  = 0x08;
   sendbuff[13]  = 0x00;

   // IP Packet
   sendbuff[14] = (4<<4) | (5);   // IPv4 + Header Length
   sendbuff[15] = 0x00;   // TOS
   // Total Lengh
   sendbuff[16] = 0;
   sendbuff[17] = 64 - 14;
   // ID
   sendbuff[18] = 0;
   sendbuff[19] = 0;
   
   // Flags + Fragment Offset
   sendbuff[20] = 0;
   sendbuff[21] = 0;

   // TTL
   sendbuff[22] = 255;
   
   // Protocal : TCP(6), udp = 17
   sendbuff[23] = 17;

   //Header checksum
   sendbuff[24] = 0;
   sendbuff[25] = 0;

   // source ip
   sendbuff[26] = 192;
   sendbuff[27] = 168;
   sendbuff[28] = 139;
   sendbuff[29] = 128;

   // Destination IP
   sendbuff[30] = 10;
   sendbuff[31] = 80;
   sendbuff[32] = 161;
   sendbuff[33] = 74;
   
   
   // after Header checksum 0 reset
   // insert value
   unsigned short header_checksum = checksum((unsigned short*)(&sendbuff[14]), 20/2);	// 20 bytes
   sendbuff[24] = (header_checksum & 0xff00) >> 8;
   sendbuff[25] = header_checksum & 0xff;


   sendbuff[34] = (10003 & 0xff00) >> 8;
   sendbuff[35] = 10003 & 0xff;
   sendbuff[36] = (10001 & 0xff00) >> 8;
   sendbuff[37] = 10001 & 0xff;
   sendbuff[38] = 0;
   sendbuff[39] = 64-14-20;
   sendbuff[40] = 0;
   sendbuff[41] = 0;

   //Data : "hehe"
   
   bool led1_flag = false;
   bool led2_flag = false;
   if (cnt == 0){
   	sendbuff[42] = '1';
   	sendbuff[43] = 'O';
   	sendbuff[44] = 'N';
   	sendbuff[45] = ' ';
   	led1_flag = true;
   } else if (cnt == 1) {
   	sendbuff[42] = '1';
	sendbuff[43] = 'O';
	sendbuff[44] = 'F';
	sendbuff[45] = 'F';
	led1_flag = false;
   } else if (cnt == 2) {
   	sendbuff[42] = '2';
   	sendbuff[43] = 'O';
   	sendbuff[44] = 'N';
   	sendbuff[45] = ' ';
   	led2_flag = true;
   } else if (cnt == 3) {
   	sendbuff[42] = '2';
   	sendbuff[43] = 'O';
   	sendbuff[44] = 'F';
   	sendbuff[45] = 'F';
   	led2_flag = false;
   	cnt = -1;
   }
   cnt++;
}
   
/*
   // extra data
   for(int i = 46; i < 64; i++) {
      sendbuff[i] = 'h';
   }
*/
   




void send_data_process()
{

   

   printf("sending...\n");
   while(1)
   {
      buff_init();
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