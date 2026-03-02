#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

int main() {

    struct sockaddr_in client, server;
    int s, sock;
    int file, count;

    char b1[200] = "", b2[200] = "";

    // Create socket
    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(2000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind socket
    bind(s, (struct sockaddr *)&server, sizeof(server));

    // Listen
    listen(s, 1);

    int len = sizeof(client);

    // Accept connection
    sock = accept(s, (struct sockaddr *)&client, &len);
    printf("\n Client connected...\n");

    // Close listening socket
    close(s);

    // Receive filename
    recv(sock, b1, sizeof(b1), 0);
    printf("\nFilename received: %s\n", b1);

    // Try to open the file
    file = open(b1, O_RDONLY);

    if (file < 0) {
        // File not found
        strcpy(b2, "FILE_NOT_FOUND");
        send(sock, b2, sizeof(b2), 0);
        printf("\nRequested file is not present...\n");
        close(sock);
        return 0;
    }

    printf("\nFile opened...\n");

    // Read and send file content
    while ((count = read(file, b2, sizeof(b2))) > 0) {

        printf("\nSending file data...\n");

        send(sock, b2, count, 0);

        // Print file content on server screen
        printf("Server printing file content:\n");
        for (int i = 0; i < count; i++)
            printf("%c", b2[i]);
        printf("\n");
    }

    close(file);
    close(sock);

    return 0;
}
