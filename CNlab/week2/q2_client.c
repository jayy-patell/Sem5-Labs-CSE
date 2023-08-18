#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int len,result,sockfd,n=1;
    struct sockaddr_in address;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(10200);
    len = sizeof(address);
    result=connect(sockfd,(struct sockaddr *)&address,len);
    if(result==-1){
		perror("\nCLIENT ERROR");
		exit(1);
	}
    int operand1, operand2;
    char operator;
    printf("Enter the first operand: ");
    scanf("%d", &operand1);
    printf("Enter the second operand: ");
    scanf("%d", &operand2);
    printf("Enter the operator (+, -, *, /): ");
    scanf(" %c", &operator);
    char data[1024];
    sprintf(data, "%d,%d %c", operand1, operand2, operator);
    write(sockfd, data, sizeof(data));
    char ans[10];
    read(sockfd, ans, sizeof(ans));
    printf("Answer: %s\n", ans);
    close(sockfd);
    return 0;
}