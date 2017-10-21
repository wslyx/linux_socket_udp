#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>


#define REMOTEPORT 4567
#define REMOTEIP "192.168.0.104"


int main(int argc,char *argv[])
{
	int s,len;
	struct sockaddr_in addr;
	int addr_len;
	char msg[256];
	int i=1;
	/*定义相关的变量。*/
	/*定义一个数组发送与接收数据。*/


	if (( s= socket(AF_INET, SOCK_DGRAM, 0) )<0)
	/*建立一个 socket。*/
	{
		perror("error");
		/*输出错误。*/
		exit(1);
	}
	else
	{
		printf("socket created .\n");
		printf("socked id: %d \n");
		printf("remote ip: %s \n",REMOTEIP);
		printf("remote port: %d \n",REMOTEPORT);
	}
	addr_len=sizeof(struct sockaddr_in);
	/*长度。*/
	bzero(&addr,sizeof(addr));
	/*空间地址结构体所在的内存空间。*/
	addr.sin_family=AF_INET;
	/*填充地址与端口的信息。*/
	addr.sin_port=htons(REMOTEPORT);
	/*端口。*/
	addr.sin_addr.s_addr=inet_addr(REMOTEIP);
	while (1)
	/*循环。*/
	{
	bzero(msg,sizeof(msg));
	/*清空 msg 所在的内存。*/
	len = read(STDIN_FILENO,msg,sizeof(msg));
	/*接收信息。*/
	sendto(s,msg,len,0,&addr,addr_len);
	/*发送信息。*/
	printf("\nInput message: %s \n",msg);
	/*输出结果。*/
	len= recvfrom (s,msg,sizeof(msg),0,&addr,&addr_len);
	/*这是接收到的信息。*/
	printf("%d :",i);
	/*输出计数。*/
	i++;
	/*计数自加。*/
	printf("Received message: %s \n",msg);
	/*这是服务器返回的信息。*/
	}
}
