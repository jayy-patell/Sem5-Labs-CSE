#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msg_st{
	long int my_msg_type;
	int num;
};

int reverse(int t){
	int y=0;
	while(t > 0){
		y *= 10;
		y += t%10;
		t /= 10;
	}
	return y;
}

int main(){
	int running = 1;
	int msgid;
	struct my_msg_st some_data;
	long int msg_to_receive = 0;

	//We create and access a message queue using the msgget function
	//The msgget function returns a positive number, the queue identifier, on success or –1 on failure
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
	if(msgid == -1){
		perror("msgget failed");
		exit(EXIT_FAILURE);
	}
	while (running){
		if(msgrcv(msgid, (void *)&some_data, sizeof(msgid), msg_to_receive, 0) == -1){
			perror("msgrcv failed");
			exit(EXIT_FAILURE);
		}
		if(some_data.num == -1){
			running = 0;
		} 
		else if(some_data.num == reverse(some_data.num)){
			printf("%d is a palindrome\n", some_data.num);
		}
		else{
			printf("%d is not a palindrome\n", some_data.num);
		}
	}
	if(msgctl(msgid, IPC_RMID, 0) == -1){
		perror("msgctl failed");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}