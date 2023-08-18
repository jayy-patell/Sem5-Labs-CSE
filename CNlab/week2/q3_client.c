#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int newsockfd;
    struct sockaddr_in seraddr;

    // Create socket
    newsockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (newsockfd == -1) {
        perror("Error creating socket");
        exit(1);
    }

    // Configure server address
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(10200); // Use the same port as the server
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Use server IP

    // Connect to the server
    if (connect(newsockfd, (struct sockaddr*)&seraddr, sizeof(seraddr)) == -1) {
        perror("Error connecting");
        close(newsockfd);
        exit(1);
    }

    int processId;
    read(newsockfd, &processId, sizeof(processId));

    char timeString[1024];
    read(newsockfd, timeString, sizeof(timeString));

    printf("Time received from server (process %d): %s\n", processId, timeString);

    close(newsockfd);

    return 0;
}
