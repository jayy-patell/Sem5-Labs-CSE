#include<stdio.h>
#include<stdlib.h>

int main(){
	int i=0;
	FILE *fptr1, *fptr2;
	char filename[100],c;
	printf("Enter the filename which you have to reverse: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");
	fptr2 = fopen("rev.txt", "w+");

	if(fptr1 == NULL){
		printf("File cannot be opened.\n");
		exit(0);
	}

	fseek(fptr1,0,SEEK_END);
	int pos = ftell(fptr1);
	while(i<pos){
		i++;
		fseek(fptr1,-i,SEEK_END);
		c = fgetc(fptr1);
		fputc(c,fptr2);
	}
	printf("Successfully reversed the entire text file. \n");
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}