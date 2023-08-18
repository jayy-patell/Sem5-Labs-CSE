#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in addr, clientAddr;
    socklen_t addrSize = sizeof(clientAddr);
    pid_t childPid;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error creating socket");
        exit(1);
    }

    // Configure server address
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10200); // Choose any available port
    addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("Error binding");
        close(sockfd);
        exit(1);
    }

    // Listen for incoming connections
    if (listen(sockfd, 10) == -1) {
        perror("Error listening");
        close(sockfd);
        exit(1);
    }

    printf("Server is listening...\n");

    while (1) {
        // Accept incoming connection
        newsockfd = accept(sockfd, (struct sockaddr*)&clientAddr, &addrSize);
        if (newsockfd == -1) {
            perror("Error accepting connection");
            continue;
        }

        // Fork a child process to handle the client
        childPid = fork();
        if (childPid == -1) {
            perror("Error forking");
            close(newsockfd);
            continue;
        } 
        else if (childPid == 0) { 
            close(sockfd); 

            time_t currentTime;
            time(&currentTime);
            char *timeString = ctime(&currentTime);

            int processId = getpid();
            send(newsockfd, &processId, sizeof(processId),0);
            send(newsockfd, timeString, strlen(timeString) + 1,0);

            printf("Time sent to client from process %d\n", processId);

            close(newsockfd);
            exit(0);
        } else { // Parent process
            close(newsockfd); // Parent process doesn't need the client socket
        }
    }

    close(sockfd);

    return 0;
}
