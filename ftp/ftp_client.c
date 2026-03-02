 #include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

    struct sockaddr_in server;
    int s, count;

    char b1[200] = "", b2[200] = "";

    s = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(2000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(s, (struct sockaddr *)&server, sizeof(server));

    // Enter filename
    printf("Enter filename to request: ");
    scanf("%s", b1);

    // Send filename
    send(s, b1, sizeof(b1), 0);

    printf("\nReceiving file content...\n");

    // Receive file data
    while ((count = recv(s, b2, sizeof(b2), 0)) > 0) {

        if (strcmp(b2, "FILE_NOT_FOUND") == 0) {
            printf("\nFile not found on server.\n");
            break;
        }

        for (int i = 0; i < count; i++)
            printf("%c", b2[i]);
    }

    printf("\n\nFile transfer completed.\n");

    close(s);

    return 0;
}
