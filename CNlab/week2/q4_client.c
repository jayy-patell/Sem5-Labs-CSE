#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(1);
    }

    // Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Use the same port as the server
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use server IP

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting");
        close(clientSocket);
        exit(1);
    }

    char sentence[MAX_BUFFER_SIZE];

    while (1) {
        printf("Enter a sentence (or 'Stop' to terminate): ");
        fgets(sentence, sizeof(sentence), stdin);
        sentence[strcspn(sentence, "\n")] = '\0'; // Remove trailing newline

        send(clientSocket, sentence, strlen(sentence) + 1, 0);

        if (strcmp(sentence, "Stop") == 0) {
            printf("Client process terminated.\n");
            break;
        }

        char modifiedSentence[MAX_BUFFER_SIZE];
        recv(clientSocket, modifiedSentence, sizeof(modifiedSentence), 0);

        printf("Modified sentence received from server: %s\n", modifiedSentence);
    }

    close(clientSocket);

    return 0;
}
