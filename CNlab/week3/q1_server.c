#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
	int sd;
	struct sockaddr_in sadd,cadd;

	//Create a UDP socket
	sd=socket(AF_INET,SOCK_DGRAM,0);

	//Construct the address for use with sendto/recvfrom... */
	sadd.sin_family=AF_INET;
	sadd.sin_addr.s_addr=inet_addr("172.16.58.96");//**
	sadd.sin_port=htons(9704);
	int result=bind(sd,(struct sockaddr *)&sadd,sizeof(sadd));
	int len=sizeof(cadd);

	int arrSize;
    recvfrom(sd,&arrSize,sizeof(arrSize),0,(struct sockaddr *)&cadd, len);
    int rows;
    recvfrom(sd,&rows,sizeof(rows),0,(struct sockaddr *)&cadd, len);

    int arr[rows][arrSize];

    for(int i=0;i<rows;i++){
        int row[arrSize];
        recvfrom(sd,row,sizeof(row),0,(struct sockaddr *)&cadd, len);
        for(int j=0;j<arrSize;j++)
            arr[i][j]=row[j];
    }
    printf("Combined Matrix:\n");
    for(int i=0;i<rows;i++){
        for(int j=0;j<arrSize;j++)
            printf("%d\t",arr[i][j]);
        printf("\n");
    }

    printf("HI");
    close(sd);
	//int n=sendto(sd,buf,sizeof(buf),0,(struct sockaddr *)&cadd,len);
	return 0;
}