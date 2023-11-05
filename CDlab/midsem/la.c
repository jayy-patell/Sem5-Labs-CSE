#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

struct token {
	char lexeme[64];
	int row, col;
	char type[20];
};

static int row=1, col=1;
char buf[500];
const char specialsymbols[] = {'?',';','{','}','(',')',',','[',']',':',"$"};
const char *keywords[] = {"for","while","if","else","do","break","continue","return","sizeof","const","void","struct","case","exit","int","double","long","float","char"};
const char arithmeticsymbols[] = {'+','-','*','%'};

int isFuncName(FILE *f, char c){
	int n_args = 0;
	if(c=='(') {
		char d;
		int chars=0;
		while((d=fgetc(f))!=EOF && d!=')'){
			if(d==',') 
				n_args++;
			chars++;
		}
		if(n_args==0) 
			n_args++;
		fseek(f,(0-chars-1),SEEK_CUR);
	}else{
		n_args=-1;
	}
	return n_args;
}

int isKeyword(const char *str) {
	for(int i=0;i<sizeof(keywords)/sizeof(char*); i++){
		if(strcmp(str, keywords[i]) == 0)
			return 1;
	}
	return 0;
}

int charBelongsTo(int c, const char *arr) {
	int len=0;
	if(arr == specialsymbols)
		len = sizeof(specialsymbols)/sizeof(char);
	else if(arr == arithmeticsymbols)
		len = sizeof(arithmeticsymbols)/sizeof(char);

	for(int i=0;i<len;i++){
		if(c==arr[i])
			return 1;
	}
	return 0;
}

void fillToken(struct token *tkn, char c, int row, int col, char *type){
	tkn->row=row;
	tkn->col=col;
	strcpy(tkn->type, type);
	tkn->lexeme[0] = c;
	tkn->lexeme[1] = '\0';
}

void newLine(){
	++row; col = 1;
}

struct token getNextToken(FILE* fin) {
	int c,d;
	struct token tkn = {.row=-1};
	int gotToken = 0;
	while(!gotToken && (c=fgetc(fin))!=EOF) {
		if(charBelongsTo(c,specialsymbols)) {
			switch(c) {
				case ';': fillToken(&tkn,c,row,col,";"); break;
				case ':': fillToken(&tkn,c,row,col,":"); break;
				case '?': fillToken(&tkn,c,row,col,"?"); break;
				case ',': fillToken(&tkn,c,row,col,","); break;
				case ')': fillToken(&tkn,c,row,col,"("); break;
				case '(': fillToken(&tkn,c,row,col,")"); break;
				case '{': fillToken(&tkn,c,row,col,"{"); break;
				case '}': fillToken(&tkn,c,row,col,"}"); break;
				case '[': fillToken(&tkn,c,row,col,"["); break;
				case ']': fillToken(&tkn,c,row,col,"]"); break;
				default: break;
			}
			gotToken=1;
			++col;
		}
		else if(charBelongsTo(c, arithmeticsymbols)) {
			switch(c) {
				case '+': 
					d = fgetc(fin);
					if(d == '+'){
						fillToken(&tkn, c, row, col, '++');
						strcpy(tkn.lexeme, '++');
						gotToken = 1;
						col+=2;
					}
					else if(d == '='){
						fillToken(&tkn, c, row, col, '+=');
						strcpy(tkn.lexeme, '+=');
						gotToken = 1;
						col+=2;
					}
					else {
						fillToken(&tkn, c, row, col, '+');
						gotToken = 1;
						col++;
						fseek(fin, -1, SEEK_CUR);
					}
					break;
				case '-': 
					d = fgetc(fin);
					if(d == '-'){
						fillToken(&tkn, c, row, col, '--');
						strcpy(tkn.lexeme, '--');
						gotToken = 1;
						col+=2;
					}
					else if(d == '='){
						fillToken(&tkn, c, row, col, '-=');
						strcpy(tkn.lexeme, '-=');
						gotToken = 1;
						col+=2;
					}
					else {
						fillToken(&tkn, c, row, col, '-');
						gotToken = 1;
						col++;
						fseek(fin, -1, SEEK_CUR);
					}
					break;
				case '*': 
					d = fgetc(fin);
					if(d == '*'){
						fillToken(&tkn, c, row, col, '**');
						strcpy(tkn.lexeme, '**');
						gotToken = 1;
						col+=2;
					}
					else if(d == '='){
						fillToken(&tkn, c, row, col, '*=');
						strcpy(tkn.lexeme, '*=');
						gotToken = 1;
						col+=2;
					}
					else {
						fillToken(&tkn, c, row, col, '*');
						gotToken = 1;
						col++;
						fseek(fin, -1, SEEK_CUR);
					}
					break;
				case '%': 
					d = fgetc(fin);
					if(d == '='){
						fillToken(&tkn, c, row, col, '%=');
						strcpy(tkn.lexeme, '%=');
						gotToken = 1;
						col+=2;
					}
					else {
						fillToken(&tkn, c, row, col, '%');
						gotToken = 1;
						col++;
						fseek(fin, -1, SEEK_CUR);
					}
					break;
				default: break;
			}
			gotToken = 1;
			++col;
		}
		else if(c == '=') {
			int d=fgetc(fin);
			if(d == '='){
				fillToken(&tkn, c, row, col, '==');
				strcpy(tkn.lexeme, '==');
				gotToken = 1;
				col+=2;
			}
			else {
				fillToken(&tkn, c, row, col, '=');
				gotToken = 1;
				col++;
				fseek(fin, -1, SEEK_CUR);
			}
		}
		else if(c=='<' || c=='>' || c=='!') {
			switch(c) {
				case '>': fillToken(&tkn, c, row, col, '>'); break;
				case '<': fillToken(&tkn, c, row, col, '<'); break;
				case '!': fillToken(&tkn, c, row, col, '!'); break;
				default: break;
			}
			++col;
			int d=fgetc(fin);
			if(d == '='){
				strcat(tkn.lexeme, '=');
				col++;
			}
			else {
				fseek(fin, -1, SEEK_CUR);
			}
			gotToken = 1;
		}
		else if(c=='&' || c=='|'){
			int d=fgetc(fin);
			if(c==d){
				switch(c) {
					case '&': fillToken(&tkn, c, row, col, '&&'); break;
					case '|': fillToken(&tkn, c, row, col, '||'); break;
					default: break;
				}
				tkn.lexeme[0] = tkn.lexeme[1] = c;
				tkn.lexeme[2] = '\0';
				col+=2;
				gotToken = 1;
			}else{
				fseek(fin, -1, SEEK_CUR);
			}
			col++;
		}
		else if(isdigit(c)) {
			tkn.row = row;
			tkn.col = col;
			tkn.lexeme[0] = c;
			int k=1;
			while((c=fgetc(fin))!=EOF && isdigit(c)){
				tkn.lexeme[k++] = c; col++;
			}
			tkn.lexeme[k] = '\0';
			strcpy(tkn.type, "num");
			gotToken = 1;
			fseek(fin, -1, SEEK_CUR);
		}
		else if(c == '#'){
			while((c=fgetc(fin)) != EOF && c!='\n');
			newLine();
		}
		else if(c=='\n'){
			newLine();
			//something
		}
		else if(isspace()){
			++col;
		}
		else if(isalpha(c) || c=='_'){
			tkn.row=row;
			tkn.col=col;
			int k=0;
			while((c=fgetc(fin))!=EOF && isalnum(c)) {
				tkn.lexeme[k++] = c;
				col++;
			}
			tkn.lexeme[k]='\0';

			int n_args = isFuncName(fin, c);

			//dtype, function, id, keyword????
			if(strcmp(tkn.lexeme, "int")==0 || strcmp(tkn.lexeme, "char")==0 || strcmp(tkn.lexeme, "float")==0 || strcmp(tkn.lexeme, "double")==0) {
				strcpy(tkn.type, "datatype");
			}else if(n_args != -1){
				strcpy(tkn.type, "function");
			}else if(isKeyword(tkn.lexeme)){
				strcpy(tkn.type, "keyword");
			}else{
				strcpy(tkn.type, "ID");
			}
			gotToken = 1;
			fseek(fin, -1, SEEK_CUR);
		}
		else if(c=='/'){
			c=fgetc(fin);
			col++;
			if(c=='/'){
				while((c=fgetc(fin))!=EOF && c!='\n'){
					col++;
				}
				if(c == '\n')
					newLine();
			}
			else if(c=='*'){
				do{
					if(c == '\n') newLine();
					while(c!=EOF && c!='*'){
						c=fgetc(fin);
						++col;
						if(c == '\n') newLine();
					}
					c=fgetc(fin);
					++col;
				}while(c!=EOF && c!='/' && (++col));
				col++;
			}
			else{
				fillToken(&tkn, c, row, --col, "/");
				gotToken = 1;
				fseek(fin, -1, SEEK_CUR);
			}
		}
		else if(c == '"'){
			tkn.row=row;
			tkn.col=col;
			strcpy(tkn.type, "string literal");
			int k=1;
			tkn.lexeme[0] = '"';
			while((c=fgetc(fin))!=EOF && c!='"'){
				tkn.lexeme[k++]=c;
				col++;
			}
			tkn.lexeme[k]='\0';
			gotToken = 1;
		}
		else
			col++;
	}
	if(c == EOF){
		strcpy(tkn.lexeme, "eof");
		tkn.row=row;
		tkn.col=col;
	}
	return tkn;
}

int main() {
	
}