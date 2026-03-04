#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>

int main()
{
    int s, n;
    char b1[50], b2[50];
    struct sockaddr_in server, client;

    s = socket(AF_INET, SOCK_DGRAM, 0);   // UDP socket

    server.sin_family = AF_INET;
    server.sin_port = htons(2000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind server to IP & PORT
    bind(s, (struct sockaddr *)&server, sizeof(server));

    n = sizeof(client);

    printf("UDP Server Started...\n");

    while (1)
    {
        // Receive message from client
        recvfrom(s, b1, sizeof(b1), 0, (struct sockaddr *)&client, &n);

        if (strcmp(b1, "end") == 0)
            break;

        printf("\nClient: %s", b1);

        // Get server message
        printf("\nServer: ");
        scanf("%s", b2);

        // Send to client
        sendto(s, b2, sizeof(b2), 0, (struct sockaddr *)&client, n);

        if (strcmp(b2, "end") == 0)
            break;
    }

    close(s);
    return 0;
}

