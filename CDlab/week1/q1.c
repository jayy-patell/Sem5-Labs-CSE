#include <stdio.h>
#include <stdlib.h> // For exit()
int main()
{	
	int count=0;
	int countline=0;
	FILE *fptr1;
	char filename[100], c;
	printf("Enter the filename to open for reading: \n");
	scanf("%s", filename);
	fptr1 = fopen(filename, "r");  // Open one file for reading

	if (fptr1 == NULL)
	{
		printf("Cannot open file %s \n", filename);
		exit(0);
	}
	
	c = fgetc(fptr1);   // Read contents from file
	while (c != EOF)
	{	
		count++;
		if (c=='\n')
		{
			countline++;
		}
		c=getc(fptr1);

	}
		
	printf("\ncountline %d", countline);

	printf("\ncountchar %d\n", count);
	fclose(fptr1);
	
	return 0;
}