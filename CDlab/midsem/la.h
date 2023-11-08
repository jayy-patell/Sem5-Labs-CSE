#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<ctype.h>

struct token{
	char lexeme[64];
	int row;
	int col;
};

int row = 1 ;
int col = 1;

char buff[1024];

const char specialsymbols[] = {'&',':',';','?',',','(',')','{','}','$','[',']'};
const char *keywords[] = {"for","if","else","printf","scanf","int","char","main"};
const char operator[] = {'+','-','*','%'}; //no /


int isKeyword(char *str)
{
	for(int i=0;i<8;i++)
	{
		if(strcmp(str,keywords[i]) == 0)
			return 1;
	}
	return 0;
}

int isSpecialSymbol(char str)
{
	for(int i=0;i<12;i++)
	{
		if(str == specialsymbols[i])
			return 1;

	}
	return 0;
}
int isOperator(char str)
{
	for(int i=0;i<4;i++)
	{
		if(str == operator[i])
			return 1;

	}
	return 0;
}


void fillToken(struct token *tkn, char c, int row, int col)
{
	tkn->row = row;
	tkn->col = col;
	tkn->lexeme[0] = c;
	tkn->lexeme[1] = '\0';    //IMP

}

void newLine(){
	++row;
	col = 1;
}


struct token getNextToken(FILE *fin) //File pointer coming from RD Parser
{

	char c;
	struct token tkn = {.row = -1};
	int gotToken = 0; //stops function when we have token

	while(!gotToken && (c = fgetc(fin))!= EOF)
	{
			if(isSpecialSymbol(c))
			{
				fillToken(&tkn, c, row, col);
				gotToken = 1;
				++col;
			}
			else if(isOperator(c))
			{
				if(c == '+')
				{
					int d = fgetc(fin);
					if(d != '+')
					{
						fillToken(&tkn,'+', row, col);
						gotToken = 1;
						++col;
						fseek(fin, -1, SEEK_CUR);
					}
					else
					{
						strcpy(tkn.lexeme,"++");
						tkn.row = row;
						tkn.col = col;
						gotToken = 1;
						col += 2;
					}
				}
				else
				{
					fillToken(&tkn, c, row, col);
					gotToken = 1;
					++col;
				}

			}
			else if(c == '=')
			{	
				int d = fgetc(fin);
					if(d != '=')
					{
						fillToken(&tkn,'=', row, col);
						gotToken = 1;
						++col;
						fseek(fin, -1, SEEK_CUR);
					}
					else
					{
						strcpy(tkn.lexeme,"==");
						tkn.row = row;
						tkn.col = col;
						gotToken = 1;
						col += 2;
					}

			}

			else if(isdigit(c))
			{
				
			    tkn.row = row;
			    tkn.col = ++col;
			    tkn.lexeme[0] = c;
			    int k = 1;

			    while((c = fgetc(fin))!= EOF && isdigit(c)){
			        col ++;
			    }
			    strcpy(tkn.lexeme,"num");
			    gotToken = 1;
			    fseek(fin, -1, SEEK_CUR);
			}
			
			else if(c == '#')
			{
				while((c = fgetc(fin))!=EOF && c!='\n');
				newLine(); //IMPPPPPPPP
			}

			else if(isalpha(c))
			{
				tkn.row = row;
				tkn.col = ++col;
				buff[0] = c;
				int k = 1;

				while((c = fgetc(fin))!=EOF && isalnum(c))
				{
					buff[k++] = c;
					++col;
				}
				buff[k] = '\0';
				
				if(isKeyword(buff))
				{
					strcpy(tkn.lexeme,buff);
				}

				else
				{
					strcpy(tkn.lexeme,"id");
				}
					
					gotToken = 1;
					fseek(fin, -1 ,SEEK_CUR);
			}
			else if ( c== '>' | c=='<' | c=='!')
			{
				switch(c)
				{

					case '>' :
						fillToken(&tkn,'>',row,col);
					break;
					case '<' :
						fillToken(&tkn,'<',row,col);
					break;
					case '!' :
						fillToken(&tkn,'!',row,col);
					break;

				}

					++col;
					int d = fgetc(fin);
					if (d == '=')
					{
						++col;
						strcat(tkn.lexeme,"=");
						fseek(fin, -1 ,SEEK_CUR); //?
					}

					gotToken = 1;

			}
			else if(c == '\n')
			{
				newLine();
			}
			else{
				++col;
			}
			
	}
	return tkn ;
}
