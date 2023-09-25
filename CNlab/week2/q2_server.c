#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORTNO 10200
int calculate(int op1, int op2, char op)
{
    switch (op)
    {
    case '+':
        return op1 + op2;
    case '-':
        return op1 - op2;
    case '*':
        return op1 * op2;
    case '/':
        return op1 / op2;
    }
}

int main()
{
    int sockfd, newsockfd, portno, clilen, n = 1;
    char buf[256];
    struct sockaddr_in seraddr, cliaddr;
    int i, value;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);
    while (1)
    {
        clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &clilen);
        if (fork() == 0)
        {
            char buffer[1024];
            read(newsockfd, buffer, sizeof(buffer));
            int operand1, operand2;
            char operator;
            sscanf(buffer, "%d,%d %c", &operand1, &operand2, &operator);
            int ans = calculate(operand1, operand2, operator);
            char result_str[10];
            sprintf(result_str, "%d", ans);
            write(newsockfd, result_str, sizeof(result_str));
            close(newsockfd);
        }
        else
            close(newsockfd);
    }
    close(sockfd);
    return 0;
}