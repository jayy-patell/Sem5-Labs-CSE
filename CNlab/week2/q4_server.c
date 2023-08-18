#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

// Function to remove duplicate words from a sentence
void removeDuplicates(char *sentence) {
    char *word;
    char *delim = " ";
    char temp[MAX_BUFFER_SIZE];
    strcpy(temp, sentence);
    
    sentence[0] = '\0';

    word = strtok(temp, delim);
    strcat(sentence, word);

    while ((word = strtok(NULL, delim)) != NULL) {
        if (strstr(sentence, word) == NULL) {
            strcat(sentence, " ");
            strcat(sentence, word);
        }
    }
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(clientAddr);
    pid_t childPid;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); 
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding");
        close(serverSocket);
        exit(1);
    }

    if (listen(serverSocket, 10) == -1) {
        perror("Error listening");
        close(serverSocket);
        exit(1);
    }

    printf("Server is listening...\n");

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
        if (clientSocket == -1) {
            perror("Error accepting connection");
            continue;
        }

        childPid = fork();
        if (childPid == -1) {
            perror("Error forking");
            close(clientSocket);
            continue;
        } else if (childPid == 0) { 
            close(serverSocket); 

            char sentence[MAX_BUFFER_SIZE];
            int bytesReceived = recv(clientSocket, sentence, sizeof(sentence), 0);
            if (bytesReceived < 0) {
                perror("Error receiving data");
                close(clientSocket);
                exit(1);
            }

            sentence[bytesReceived] = '\0';
            
            if (strcmp(sentence, "Stop") == 0) {
                printf("Server process terminated.\n");
                close(clientSocket);
                exit(0);
            }

            printf("Received sentence from client: %s\n", sentence);

            removeDuplicates(sentence);

            send(clientSocket, sentence, strlen(sentence) + 1, 0);

            printf("Processed sentence sent back to client.\n");

            close(clientSocket);
            exit(0);
        } 
        else
            close(clientSocket); 
        
    }

    close(serverSocket);

    return 0;
}
