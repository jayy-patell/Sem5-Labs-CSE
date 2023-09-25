#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sd;
    char buf[25];
    struct sockaddr_in sadd, cadd;
    // Create a UDP socket
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    // Construct the address for use with sendto/recvfrom... */
    sadd.sin_family = AF_INET;
    sadd.sin_addr.s_addr = inet_addr("127.0.0.1");
    sadd.sin_port = htons(8320);
    int result = bind(sd, (struct sockaddr *)&sadd, sizeof(sadd));
    int len = sizeof(cadd);
    int numRows, numCol;
    recvfrom(sd, &numRows, sizeof(int), 0, (struct sockaddr *)&cadd, &len);
    recvfrom(sd, &numCol, sizeof(int), 0, (struct sockaddr *)&cadd, &len);
    int mat[numRows][numCol];
    for (int i = 0; i < numRows; i++)
    {
        int row[numCol];
        recvfrom(sd, row, sizeof(row), 0, (struct sockaddr *)&cadd, len);
        for (int j = 0; j < numCol; j++)
            mat[i][j] = row[j];
    }
    printf("Matrix:\n");
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCol; j++)
            printf("%d\t", mat[i][j]);
        printf("\n");
    }
    close(sd);
    return 0;
}