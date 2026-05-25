#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    printf("\nWaiting for client...\n");

    // Structure to store server and client address
    struct sockaddr_in server, client;

    // Create UDP socket
    int  s = socket(AF_INET, SOCK_DGRAM, 0);

    // Clear memory of structures
    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    // Set server address details
    server.sin_family = AF_INET;        // IPv4
    server.sin_addr.s_addr = INADDR_ANY; // Accept connection from any IP
    server.sin_port = htons(8080);       // Port number

    // Bind socket with server address
    bind( s, (const struct sockaddr *)&server, sizeof(server));

    int len = sizeof(client);

    int frames[100], n;

    // Receive total number of frames from client
    recvfrom( s, &n, sizeof(n), 0, (struct sockaddr *)&client, &len);

    int p, ack;

    while (1)
    {
        // Receive frame number
        recvfrom( s, &p, sizeof(n), 0, (struct sockaddr *)&client, &len);

        // If client sends -99 transmission ends
        if (p == -99)
            return 0;

        // Print received frame
        printf("\nReceived frame - %d", p);

        // Ask user to send ACK
        printf("\nEnter 1 for +ve ack and -1 for -ve ack\n");
        scanf("%d", &ack);

        // Send ACK back to client
        sendto( s, &ack, sizeof(n), 0, (struct sockaddr *)&client, sizeof(client));
    }

    return 0;
}
