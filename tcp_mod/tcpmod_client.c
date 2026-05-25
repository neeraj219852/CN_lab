#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main() {
    struct sockaddr_in server;
    int s;
    char word[200], response[300];

    s = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created successfully...\n");

    server.sin_family = AF_INET;
    server.sin_port = htons(2000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr *)&server, sizeof(server));

    while(1) {
        printf("Enter a word: ");
        scanf("%s", word);

        send(s, word, sizeof(word), 0);

        if(strcmp(word, "end") == 0) {
            printf("Connection ended.\n");
            break;
        }

        recv(s, response, sizeof(response), 0);
        printf("Server Response: %s\n", response);
    }

    close(s);

    return 0;
}