#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int palindrome(char str[]) {
    int i, len = strlen(str);
    for(i = 0; i < len / 2; i++) {
        if(str[i] != str[len - i - 1])
            return 0;
    }
    return 1;
}

int countVowels(char str[]) {
    int i, count = 0;
    for(i = 0; str[i] != '\0'; i++) {
        char ch = str[i];
        if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
           ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
            count++;
        }
    }
    return count;
}

int main() {
    struct sockaddr_in server, client;
    int s, n, sock;
    char word[200], result[300];

    FILE *fp;

    s = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket created successfully...\n");

    server.sin_family = AF_INET;
    server.sin_port = htons(2000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(s, (struct sockaddr *)&server, sizeof(server));

    listen(s, 1);
    printf("Server listening on port 2000...\n");

    n = sizeof(client);

    sock = accept(s, (struct sockaddr *)&client, (socklen_t *)&n);

    while(1) {
        recv(sock, word, sizeof(word), 0);

        if(strcmp(word, "end") == 0) {
            printf("Connection ended.\n");
            break;
        }

        printf("Received from client: %s\n", word);

        fp = fopen("log.txt", "a");
        if(fp != NULL) {
            fprintf(fp, "%s\n", word);
            fclose(fp);
        }

        int vowels = countVowels(word);

        if(palindrome(word))
            sprintf(result, "%s is a palindrome. Vowels = %d", word, vowels);
        else
            sprintf(result, "%s is NOT a palindrome. Vowels = %d", word, vowels);

        send(sock, result, sizeof(result), 0);
    }

    close(sock);
    close(s);

    return 0;
}