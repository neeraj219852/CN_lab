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
    	int n,sock,s,status,i,j,length;
	struct sockaddr_in server,client;
	char buffer[120],frame[120],temp[120],ack[120];
	s=socket(AF_INET,SOCK_STREAM,0);

	server.sin_family=AF_INET;
	server.sin_port=3000;
    	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	n=sizeof(client);
	bind(s,(struct sockaddr *)&server,sizeof(server));
	listen(s,1);
	sock=accept(s,(struct sockaddr *)&client,&n);
	printf("\nEnter the text");
	scanf("%s",buffer);
	i=0;
	while(i<strlen(buffer))
	{
		memset(frame,0,120);
		strncpy(frame,buffer+i,window);
		printf("\nTransmitting frames");
		length=strlen(frame);
		for(int j=0;j<length;j++)
		{
			printf("%d",i+j);
			sprintf(temp,"%d",i+j);
			strcat(frame,temp);
		}
		printf("\n");
		write(sock,frame,sizeof(frame));
		read(sock,ack,sizeof(ack));
		sscanf(ack,"%d",&status);
		if(status==-1)
			printf("\nTransmission Successfull");
		else
		{
			printf("\nRetransmitting frames");
			for(j=0;;)
			{
				frame[j]=buffer[j+status];
				printf("%d",j+status);
				j++;
				if((j+status)%window==0)
					break;
			}
			printf("\n");
			frame[j]='\0';
			length=strlen(frame);
			for(int j=0;j<length;j++)
			{
				sprintf(temp,"%d",j+status);
				strcat(frame,temp);
			}
			write(sock,frame,sizeof(frame));
		}
		i+=window;
	}
	write(sock,"exit",sizeof("exit"));
	return 0;
}