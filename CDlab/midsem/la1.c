#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct token{
	char lexeme[50];
	int row;
	int col;
};

int row = 1;
int col = 1;

char buff[40];

const char *keywords[] = {"for","while","if","else","continue","sizeof","int","char","main"};
const char specialsymbols[] = {';',',','?','(',')','{','}','[',']'};
const char operators[] = {'+','-','*','%','='};

int isKeyword(char *str)
{
	for(int i = 0;i<9;i++)
	{
		 if(strcmp(str,keywords[i]) == 0)
		 {
		 	return 1;
		 }
    }
    return 0;
}

int isSpecialSymbol(char str)
{
	for(int i = 0;i<9;i++)
	{
		 if(str == specialsymbols[i])
		 {
		 	return 1;
		 }
    }
    return 0;
}

int isOperator(char str)
{
	for(int i = 0;i<5;i++)
	{
		 if(str == operators[i])
		 {
		 	return 1;
		 }
    }
    return 0;
}


void fillToken(struct token *tkn, char c, int row, int col)
{
	tkn->row = row;
	tkn->col = col;
	tkn->lexeme[0] = c;
	tkn->lexeme[1] = '\0';
}

void newLine()
{
	++row;
	col = 1;
}

struct token getNextToken(FILE *fp)
{
	char c;
	struct token tkn = {.row = -1};
	int gotToken = 0;

	while(!gotToken && (c = fgetc(fp))!= EOF)
	{
		if(isSpecialSymbol(c))
		{
			fillToken(&tkn, c, row, col);
			gotToken = 1;
			++col;
		}
		else if (isOperator(c))
		{
			if (c == '+')
			{
				int d;
				d = fgetc(fp);
				if(d != '+')
				{
					fillToken(&tkn, '+', row, col);
					gotToken = 1;
					++col;
					fseek(fp, -1, SEEK_CUR);
				}
				else
				{
					strcpy(tkn.lexeme, "++");
					tkn.row = row;
					tkn.col = col;
					gotToken = 1;
					col = col + 2;
				}
			}
			else
			{
				fillToken(&tkn, c, row, col);
				gotToken = 1;
				++col;
			}
		}
		else if(c == '"')
		{
			tkn.row = row;
			tkn.col = col;

			while ((c = fgetc(fp))!=EOF && c!='"')
			{
				++col;
			}

			strcpy(tkn.lexeme,"String Literal");
			gotToken = 1;
			fseek(fp,-1,SEEK_CUR);

		}
		else if(isdigit(c))
		{
			tkn.row = row;
			tkn.col = ++col;

			while ((c = fgetc(fp))!=EOF && isdigit(c))
			{
				++col;
			}

			strcpy(tkn.lexeme,"num");
			gotToken = 1;
			fseek(fp,-1,SEEK_CUR);


		}
		else if(isalpha(c) || c == '_')
		{
			tkn.row = row;
			tkn.col = ++col;
			tkn.lexeme[0] = c;

			int k = 1;

			while ((c = fgetc(fp))!=EOF && isalnum(c))
			{
				buff[k++] = c;
				++col;
			}

			if(isKeyword(buff))
			{
				strcpy(tkn.lexeme,buff);
			}
			else
			{
				strcpy(tkn.lexeme,"id");
			}
			gotToken = 1;
			fseek(fp,-1,SEEK_CUR);
			
		}
		else if(c == '\n')
		{
			newLine();
		}
		else
			++col;
	}
}
int main()
{
	FILE *fp;
	fp = fopen("input.c","r");
	if(!fp){
		printf("Not able to open file"); exit(1);
	}
	else
		printf("file opened");

	struct token tkn;
	while((tkn = getNextToken(fp)).row != -1)
		printf("<%s, %d, %d>\n",tkn.lexeme,tkn.row,tkn.col);

	fclose(fp);
	return 0;
}
