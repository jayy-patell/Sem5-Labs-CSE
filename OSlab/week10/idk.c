#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct token{
	char lexeme[30];
	int row, col;
};

struct table_entry{
	char lexeme_name[40];
	int sno;
	char dtype[30],retype[30],type[30];
	int num_args;
}Table[100];

const char *keywords[] = {"const","return","if","else","for","while"};
const char operator[] = {'+','-','*','%'};
const char specialsymbols[] = {'(',')','{','}','[',']',';',','};
const char *datatypes[] = {"int","char","float","double"};

static int row=1,col=1;
static int ind=1;
char dbuf[200];

int isDatatype(const char* str){
	for(int i=0;i<4;i++){
		if(!strcmp(str,datatypes[i])) return 1;
	}
	return 0;
}
int isKeyword(const char* str){
	for(int i=0;i<6;i++){
		if(!strcmp(str,keywords[i])) return 1;
	}
	return 0;
}
int isOperator(const char c){
	for(int i=0;i<4;i++){
		if(c == operator[i]) return 1;
	}
	return 0;
}
int isSpecialSymbol(const char c){
	for(int i=0;i<8;i++){
		if(c == specialsymbols[i]) return 1;
	}
	return 0;
}

void newLine(){
	row++; col=1;
}

void fillToken(struct token* tkn, char c, int row, int col){
	tkn->row=row;
	tkn->col=col;
	tkn->lexeme[0]=c;
	tkn->lexeme[1]='\n';
}

int searchTable(const char* lexeme){
	if(ind==1) return 0;
	int i=0;
	while(i<ind){
		if(strcmp(Table[i].lexeme_name, lexeme) == 0)
			return 1;
		i++;
	}
	return 0;
}

void insertIntoTable(struct token* tkn, int n_args, const char* type){
	printf("hello");
	if(strcmp(type, "variable")){
		Table[ind-1].sno=ind;
		strcpy(Table[ind-1].lexeme_name, tkn->lexeme);
		strcpy(Table[ind-1].type, "var");
		strcpy(Table[ind-1].dtype, dbuf);
		strcpy(Table[ind-1].retype, "NULL");
		Table[ind-1].num_args = -1;
		++ind;
	}
	else if(strcmp(type, "function")){
		Table[ind-1].sno=ind;
		strcpy(Table[ind-1].lexeme_name, tkn->lexeme);
		strcpy(Table[ind-1].type, "func");
		strcpy(Table[ind-1].dtype, "NULL");
		strcpy(Table[ind-1].retype, dbuf);
		Table[ind-1].num_args = n_args;
		++ind;
	}
}

void printTable(int n){
	for(int i=0;i<n;i++){
		printf("%d\t\t\t%s\t\t%s\t\t%s\t\t%d\t\t\t%s\n", Table[i].sno, Table[i].lexeme_name, Table[i].dtype ,Table[i].retype, Table[i].num_args, Table[i].type);
	}
}

int isFunc(FILE* f, char c){
	int n_args=0;
	if(c=='('){
		char d;
		int chars=0;
		while((d=fgetc(f))!=EOF && d!=')'){
			if(d==',')
				n_args++;
			chars++;
		}
		if(n_args==0) n_args++;
		fseek(f,(0-chars-1),SEEK_CUR);
	}
	return n_args;
}

struct token getNextToken(FILE *fin){
	char c;
	struct token tkn = {.row=-1};
	int gotToken=1;
	while(!gotToken && (c=fgetc(fin))!=EOF){
		if(isSpecialSymbol(c)){
			fillToken(&tkn,c,row,col);
			gotToken=1;
			col++;
		}
		else if(isOperator(c)){
			if(c=='+'){
				int d=fgetc(fin);
				if(d!='+'){
					fillToken(&tkn,'+',row,col);
					col++;
					gotToken=1;
					fseek(fin,-1,SEEK_CUR);
				}else{
					strcpy(tkn.lexeme,'++');
					tkn.row=row;
					tkn.col=col;
					col+=2;
					gotToken=1;
				}
			}
			//else if() for - * %
		}
		else if(c=='='){
			int d=fgetc(fin);
			if(d!='='){
				fillToken(&tkn,'=',row,col);
				col++;
				gotToken=1;
				fseek(fin,-1,SEEK_CUR);
			}else{
				strcpy(tkn.lexeme,'==');
				tkn.row=row;
				tkn.col=col;
				col+=2;
				gotToken=1;
			}
		}
		else if(isdigit(c)){
			tkn.row=row;
			tkn.col=col;
			tkn.lexeme[0]=c;

			int k=1;
			while((c=fgetc(fin))!=EOF && isdigit(c)){
				col++;
			}

			strcpy(tkn.lexeme, 'num');
			gotToken=1;
			fseek(fin,-1,SEEK_CUR);
		}
		else if(c=='#'){
			while((c=fgetc(fin))!=EOF && c!='\n') ;
			newLine();
		}
		else if(isalpha(c)){
			tkn.row=row;
			tkn.col=col;

			int k=1;
			while((c=fgetc(fin))!=EOF && isalnum(c)){
				tkn.lexeme[k++]=c;
				col++;
			}
			tkn.lexeme[k]='\0';

			if(!isKeyword(tkn.lexeme)){
				if(!searchTable(tkn.lexeme)){
					int n_args = isFunc(fin,c);
					if(n_args == -1){
						insertIntoTable(&tkn, n_args, "variable");
					}else{
						insertIntoTable(&tkn, n_args, "function");
					}
				}
			}
			if(isDatatype(tkn.lexeme)){
				strcpy(dbuf,tkn.lexeme);
			}
			gotToken=1;
			fseek(fin,-1,SEEK_CUR);
		}
		//else if(c=='/')
		else if(c=='>'){

		}
		else if(c=='\n'){
			newLine();
		}
		else
			col++;
	}
	return tkn;
}

int main(){
	FILE* f1 = fopen("input.c","r");
	if(!f1){
		printf("doesnt open.");exit(0);
	}

	struct token tkn;
 	while ((tkn = getNextToken(f1)).row != -1)
    {
        printf("<%s, %d, %d>\n", tkn.lexeme, tkn.row, tkn.col);
    }
    printf("S.No.\t\t   LexemeName\t\t DataType\t ReturnType\t\tNumArgs\t\tTokenName\n");
    int num_entries = ind;
    printTable(num_entries);
    fclose(f1);
}