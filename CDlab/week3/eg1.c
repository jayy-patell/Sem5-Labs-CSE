// Identification of arithmetic and relational operators from the given input file.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
	char c, buf[100];
	FILE *fp = fopen("eg1.c", "r");
	c = fgetc(fp);
	if (fp == NULL)
	{
		printf("Cannot open file \n");
		exit(0);
	}

	while (c != EOF)
	{
		int i = 0;
		buf[0] = '\0';
		if (c == '=')
		{
			buf[i++] = c;
			c = fgetc(fp);
			if (c == '=')
			{
				buf[i++] = c;
				buf[i] = '\0';
				printf("\n Relational operator : %s", buf);
			}
			else
			{
				buf[i] = '\0';
				printf("\n Assignment operator: %s", buf);
			}
		}
		else
		{
			if (c == '<' || c == '>' || c == '!')
			{
				buf[i++] = c;
				c = fgetc(fp);
				if (c == '=')
				{
					buf[i++] = c;
				}
				buf[i] = '\0';
				printf("\n Relational operator : %s", buf);
			}
			else
			{
				buf[i] = '\0';
			}
		}
		c = fgetc(fp);
	}

	fclose(fp);

	for (int j = 0; j < sizeof(buf) / sizeof(buf[0]); j++)
	{
		printf("%c ", buf[j]);
	}
}
