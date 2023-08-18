#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(){
    int sd;
    struct sockaddr_in address;
    sd=socket(AF_INET,SOCK_DGRAM,0);
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=inet_addr("127.0.0.1");
    address.sin_port=htons(8320);
    int len=sizeof(address);
    int m,n;
    printf("enter matrix dimensions:\n");
    scanf("%d %d", &m,&n);
    sendto(sd,&m,sizeof(m),0,(struct sockaddr *)&address, len);
    sendto(sd,&n,sizeof(n),0,(struct sockaddr *)&address, len);
    int row[n];
    printf("Enter matrix rows:\n");
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++)
            scanf("%d", &row[j]);
        sendto(sd,row,sizeof(row),0,(struct sockaddr *)&address, len);
    }
    close(sd);
    return 0;
}