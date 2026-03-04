#include <stdio.h>
#include<unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int s, n;
    char b1[50], b2[50];
    struct sockaddr_in server;

    s = socket(AF_INET, SOCK_DGRAM, 0);  // UDP socket

    server.sin_family = AF_INET;
    server.sin_port = htons(2000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    n = sizeof(server);

    printf("UDP Client Started...\n");

    while (1)
    {
        // Enter client message
        printf("\nClient: ");
        scanf("%s", b2);

        // Send to server
        sendto(s, b2, sizeof(b2), 0, (struct sockaddr *)&server, n);

        if (strcmp(b2, "end") == 0)
            break;

        // Receive from server
        recvfrom(s, b1, sizeof(b1), 0, NULL, NULL);

        if (strcmp(b1, "end") == 0)
            break;

        printf("\nServer: %s", b1);
    }

    close(s);
    return 0;
}


