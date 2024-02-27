#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define MAX_NUM_DIGITS 10
#define SERVER_PORT 8888
int fibonacci(int n)
{
	if(n<=1)
	{
		return n;
	}
	return fibonacci(n-1)+fibonacci(n-2);
}
int main()
{
	int server_socket;
	struct sockaddr_in server_addr,client_addr;
	char buffer[MAX_NUM_DIGITS];
	int n,fib;
	if((server_socket=socket(AF_INET,SOCK_DGRAM,0))==-1)
	{
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(SERVER_PORT);
	if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
	{
		perror("Binding failed");
		exit(EXIT_FAILURE);
	}
	printf("Server waiting for client...\n");
	while(1)
	{
		socklen_t client_len=sizeof(client_addr);
		if(recvfrom(server_socket,buffer,sizeof(buffer),0,(struct sockaddr*)&client_addr,&client_len)==-1)
		{
			perror("Receive failed");
			exit(EXIT_FAILURE);
		}
		n=atoi(buffer);
		printf("Received number from client: %d\n",n);
		fib=fibonacci(n);
		sprintf(buffer,"%d",fib);
		if(sendto(server_socket,buffer,strlen(buffer),0,(struct sockaddr*)&client_addr,client_len)==-1)
		{
			perror("Send failed");
			exit(EXIT_FAILURE);
		}
		printf("Fibonacci term %d sent to client\n",fib);
	}
	close(server_socket);
	return 0;
}
