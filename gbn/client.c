#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define window 4
int main()
{
    	int n,sock,s,status,i,j,length,choice;
	struct sockaddr_in server,client;
	char buffer[120],frame[120],temp[120],ack[120],error[120];
	s=socket(AF_INET,SOCK_STREAM,0);

	server.sin_family=AF_INET;
	server.sin_port=3000;
    	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	n=sizeof(server);
	connect(s,(struct sockaddr *)&server,sizeof(server));
	while(1)
	{
		read(s,buffer,sizeof(buffer));
		if(strcmp(buffer,"exit")==0)
			break;
		printf("\nRecieved: %s",buffer);
		printf("\ndo you want to report an error yes-1 no-0");
		scanf("%d",&choice);
		if(choice==0)
			write(s,"-1",sizeof("-1"));
		else
		{
			printf("\nEnter the sequence where error has occured");
			scanf("%s",error);
			write(s,error,sizeof(error));
			read(s,buffer,sizeof(buffer));
			printf("\nRetransmitted frames: %s",buffer);
		}
	}
	return 0;
}