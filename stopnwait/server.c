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
    struct sockaddr_in servaddr, cliaddr;

    // Create UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Clear memory of structures
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Set server address details
    servaddr.sin_family = AF_INET;        // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY; // Accept connection from any IP
    servaddr.sin_port = htons(8080);       // Port number

    // Bind socket with server address
    bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    int len = sizeof(cliaddr);

    int frames[100], n;

    // Receive total number of frames from client
    recvfrom(sockfd, &n, sizeof(n), 0, (struct sockaddr *)&cliaddr, &len);

    int p, ack;

    while (1)
    {
        // Receive frame number
        recvfrom(sockfd, &p, sizeof(n), 0, (struct sockaddr *)&cliaddr, &len);

        // If client sends -99 transmission ends
        if (p == -99)
            return 0;

        // Print received frame
        printf("\nReceived frame - %d", p);

        // Ask user to send ACK
        printf("\nEnter 1 for +ve ack and -1 for -ve ack\n");
        scanf("%d", &ack);

        // Send ACK back to client
        sendto(sockfd, &ack, sizeof(n), 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    }

    return 0;
}