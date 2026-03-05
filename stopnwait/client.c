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
    struct sockaddr_in servaddr;

    // Create UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Clear memory
    memset(&servaddr, 0, sizeof(servaddr));

    // Server details
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n = -1;

    // Send initial request to server
    sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("\nServer connected successfully\n");

    // Enter number of frames to send
    printf("\nEnter the total number of frames: ");
    scanf("%d", &n);

    // Send number of frames
    sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

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
            sendto(sockfd, &i, sizeof(n), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

            printf("\nWaiting for ACK...\n");

            // Receive ACK from server
            recvfrom(sockfd, &ack, sizeof(n), 0, (struct sockaddr *)&servaddr, &len);

            if (ack == -1)
            {
                // Negative ACK → resend frame
                printf("\nNegative ACK received... Resending\n");
            }

        } while (ack == -1);
    }

    // Send -99 to indicate end of transmission
    n = -99;
    sendto(sockfd, &n, sizeof(n), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    printf("\nSuccessfully sent all the frames\n");

    close(sockfd);

    return 0;
}