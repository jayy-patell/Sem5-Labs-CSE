#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    struct sockaddr_in address;
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("Error creating socket");
        exit(1);
    }

    // Configure server address
    address.sin_family = AF_INET;
    address.sin_port = htons(10200);                     // Use the same port as the server
    address.sin_addr.s_addr = inet_addr("172.16.58.96"); // Use server IP

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        perror("Error connecting");
        close(sockfd);
        exit(1);
    }

    int arrSize;
    printf("Enter the size of the array: ");
    scanf("%d", &arrSize);

    int arr[arrSize];
    printf("Enter %d integers: ", arrSize);
    for (int i = 0; i < arrSize; i++)
    {
        scanf("%d", &arr[i]);
    }

    write(sockfd, &arrSize, sizeof(arrSize));
    write(sockfd, arr, sizeof(arr));

    int processId;
    read(sockfd, &processId, sizeof(processId));
    read(sockfd, arr, sizeof(arr));

    printf("Sorted array received from server (process %d): ", processId);
    for (int i = 0; i < arrSize; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");

    close(sockfd);

    return 0;
}
