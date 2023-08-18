#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
	int sd;
	struct sockaddr_in address;
	sd=socket(AF_INET,SOCK_DGRAM,0);
	address.sin_family=AF_INET;
	address.sin_addr.s_addr=inet_addr("172.16.58.96");  //**
	address.sin_port=htons(9704);
	char buf[25];
	int len=sizeof(address);

	int arrSize;
    printf("Enter the size of the array: ");
    scanf("%d", &arrSize);
    sendto(sd,arrSize,sizeof(arrSize),0,(struct sockaddr *)&address, len);

	int rows;
	printf("Enter no. of rows: ");
	scanf("%d", &rows);
	int a[arrSize]; int i = 1;
	sendto(sd,rows,sizeof(rows),0,(struct sockaddr *)&address, len);

	while(i <= rows){
		printf("Enter array %d: ", i);
		for(int j=0; j<arrSize; j++){
			scanf("%d", &a[j]);
		}
		printf("Sending array %d\n", i++);

		sendto(sd,a,sizeof(a),0,(struct sockaddr *)&address, len);

		// write(sockfd, &arrSize, sizeof(arrSize));
		// write(sockfd, a, sizeof(a));

		// if(send(sd, a, 5, 0) < 0)    
	    // {
	    //     printf("\nArray is not successfully sent\n");
	    // }
	    // else
	    // {
	    //     printf("\nArray is sent\n");
	    // }
	}
	return 0;
}
