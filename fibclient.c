#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define MAX_NUM_DIGITS 10
int main()
{
	int client_socket;
	struct sockaddr_in server_addr;
	char buffer[MAX_NUM_DIGITS];
	int n;
	if((client_socket=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=inet_addr(SERVER_IP);
	server_addr.sin_port=htons(SERVER_PORT);
	printf("Enter the value of n: ");
	scanf("%d",&n);
	printf(buffer,"%d",n);
	if(sendto(client_socket,buffer,strlen(buffer),0,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
	{
		perror("Send failed");
		exit(EXIT_FAILURE);
	}
	if(recvfrom(client_socket,buffer,sizeof(buffer),0,NULL,NULL)==-1)
	{
		{
			perror("Received failed");
			exit(EXIT_FAILURE);
		}
		printf("The %dth Fibonacci term %s\n",n,buffer);
	}
	close(client_socket);
	return 0;
}
