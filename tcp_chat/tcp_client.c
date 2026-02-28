#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>

int main(){

	struct sockaddr_in client,server ;
	int s, sock;
	
	char b1[200]="" ,b2[200]="hello server ";
	
	s=socket(AF_INET,SOCK_STREAM,0);
	
	server.sin_family =AF_INET ;
	server.sin_port =htons(2000);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	connect(s,(struct sockaddr *)&server,sizeof(server));
	
	while(1) {
	
		printf("\n client : ");
		scanf("%s",b2);
		send(s,b2,sizeof(b2),0);
	
		if(strcmp(b2,"end")==0){
			break ;
		}
		
		recv(s,b1,sizeof(b1),0);
		
		if(strcmp(b1,"end")==0){
			break ;
		}
		
		printf("\nserver : %s",b1);
	
	}
	
	close(s);
}

