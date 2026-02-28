#include<stdio.h>  
#include<stdlib.h>  
#include<sys/stat.h>  
#include<netinet/in.h>  
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>


int main(){

	struct sockaddr_in client,server ;
	int n ,sock,s ;
	
	char b1[200]="",b2[20]="hello",b3[200] ;

	s=socket(AF_INET,SOCK_STREAM,0);
	
	server.sin_family = AF_INET ;
	server.sin_port = htons(2000);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	

	bind(s,(struct sockaddr *)&server ,sizeof(server));
	
	listen(s,1);
	
	n=sizeof(client);
	
	sock = accept(s,(struct sockaddr *)&client,(socklen_t *)&n);
	
	while(1){
		
		recv(sock,b1,sizeof(b1),0);
		
		if(strcmp(b1 ,"end")==0){
			
			break;
		}
		
		printf("\n Client :%s ",b1);
		
		printf("\nserver :");
		scanf("%s",b3);
		
		send(sock,b3,sizeof(b3),0);
		
		if(strcmp(b3,"end")==0){
			break ;
		}
		
		 
		}	

	close(sock);
	close(s);	
	return 0;
	
}
  
