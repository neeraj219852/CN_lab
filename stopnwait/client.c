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
    printf("\nSearching for server...\n");

    // Structure to store server address
    struct sockaddr_in server;

    // Create UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    
   

    server.sin_family = AF_INET;        // IPv4
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); // Accept connection from any IP
    server.sin_port = htons(2000);       // Port number
    int n = -1;

    // Send initial request to server
  //  sendto(sock, &n, sizeof(n), 0, (struct sockaddr *)&server, sizeof(server));

    printf("\nServer connected successfully\n");

    // Enter number of frames to send
    printf("\nEnter the total number of frames: ");
    scanf("%d", &n);

    // Send number of frames
    sendto(sock, &n, sizeof(n), 0, (struct sockaddr *)&server, sizeof(server));

    int len, ack;

    // Send frames one by one
    for (int i = 1; i <= n; i++)
    {
        ack = -1;

        // Repeat until positive ACK received
        do
        {
            printf("\nSending frame - %d", i);

            // Send frame number
            sendto(sock, &i, sizeof(n), 0, (struct sockaddr *)&server, sizeof(server));

            printf("\nWaiting for ACK...\n");

            // Receive ACK from server
            recvfrom(sock, &ack, sizeof(n), 0, (struct sockaddr *)&server, &len);

            if (ack == -1)
            {
                // Negative ACK → resend frame
                printf("\nNegative ACK received... Resending\n");
            }

        } while (ack == -1);
    }

    // Send -99 to indicate end of transmission
    n = -99;
    sendto(sock, &n, sizeof(n), 0, (const struct sockaddr *)&server, sizeof(server));

    printf("\nSuccessfully sent all the frames\n");

    close(sock);

    return 0;
}
