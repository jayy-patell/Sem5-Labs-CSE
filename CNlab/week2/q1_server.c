#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void sortArray(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int sockfd, newsockfd;
    struct sockaddr_in seraddr, clientAddr;
    socklen_t addrSize = sizeof(clientAddr);
    pid_t childPid;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("Error creating socket");
        exit(1);
    }

    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(10200); // Choose any available port
    seraddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr)) == -1) {
        perror("Error binding");
        close(sockfd);
        exit(1);
    }

    if (listen(sockfd, 10) == -1) {
        perror("Error listening");
        close(sockfd);
        exit(1);
    }

    printf("Server is listening...\n");

    while (1) {
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

            int arrSize;
            read(newsockfd, &arrSize, sizeof(arrSize));

            int arr[arrSize];
            read(newsockfd, arr, sizeof(arr));

            sortArray(arr, arrSize);

            int processId = getpid();
            write(newsockfd, &processId, sizeof(processId));
            write(newsockfd, arr, sizeof(arr));

            printf("Sorted array sent to client from process %d\n", processId);

            close(newsockfd);
            exit(0);
        } 
        else 
            close(newsockfd); 
        
    }

    close(sockfd);

    return 0;
}
