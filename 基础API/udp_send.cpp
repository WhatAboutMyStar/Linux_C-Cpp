#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc,char *argv[])
{
	unsigned short port = 8080;
	char *server_ip = NULL;
    if(argc < 2)
    {
        exit(-1);
    }
	server_ip = argv[1];
    if(argc > 2)   
        port = atoi(argv[2]);
	
	/*创建UDP套接字*/
	int sockfd;
	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	if(sockfd < 0)
	{
		perror("socket");
		exit(-1);
	}

	/*填充目的server socket地址*/
	struct sockaddr_in dest_addr;
	bzero(&dest_addr,sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;//目的套接字地址的协议家族赋值
	dest_addr.sin_port = htons(port);//目的套接字地址的端口号赋值
	inet_pton(AF_INET,server_ip,&dest_addr.sin_addr);//目的套接字地址的ip地址赋值

	printf("send data to UDP server %s:%d!\n",server_ip,port);
	
	/*发送数据到目的server*/
	while(1)
	{
		char send_buf[512];
		fgets(send_buf,sizeof(send_buf),stdin);
		send_buf[strlen(send_buf)-1] = '\0';//字符串最后一个'\n'变成'\0'
		sendto(sockfd,send_buf,strlen(send_buf),0,(struct sockaddr *)&dest_addr,sizeof(dest_addr));
	}
	close(sockfd);
	return 0;
}
