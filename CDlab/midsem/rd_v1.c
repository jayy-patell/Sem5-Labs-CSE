//1.after if always have cur = getNextToken();
//2.for epsilon check if desired value is there or not ..if not just return ..else go to func and check again
//3.there are cases where even after checking if we dont 
//do getNextToken immediately.. is done in subsequent production

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "la.h"

struct token cur;
FILE *fp;

void program();
void declarations();
void datatype();
void identifier_list();
void A();
void B();
void statement_list();
void statement();
void assignstat();
void expn();
void simple_expn();
void eprime();
void term();
void seprime();
void tprime();
void factor();
void relop();
void addop();
void mulop();

void program(){
	if(strcmp(cur.lexeme, "main")==0){
		cur = getNextToken(fp);
		printf("%s\n",cur.lexeme);
		if(strcmp(cur.lexeme, "(")==0){
			cur = getNextToken(fp);
			printf("%s\n",cur.lexeme);
			if(strcmp(cur.lexeme, ")")==0){
				cur = getNextToken(fp);
				printf("%s\n",cur.lexeme);
				if(strcmp(cur.lexeme, "{")==0){
					cur = getNextToken(fp);
					printf("%s\n",cur.lexeme);
					declarations();
					statement_list();
					if(!strcmp(cur.lexeme,"}")){
						return;
					}else{
						printf("Missing } on row%d col%d", cur.row, cur.col);
						exit(1);
					}
				}else{
					printf("Missing { on row%d col%d", cur.row, cur.col);
					exit(1);
				}
			}else{
				printf("Missing ) on row%d col%d", cur.row, cur.col);
				exit(1);
			}
		}else{
			printf("Missing ( on row%d col%d", cur.row, cur.col);
			exit(1);
		}
	}else{
		printf("Missing main on row%d col%d", cur.row, cur.col);
		exit(1);
	}
}

void declarations(){
	if(strcmp(cur.lexeme,"int")!=0 && strcmp(cur.lexeme,"char")!=0){
		return;   //EPSILON case
	}
	datatype();
	identifier_list();
	if(strcmp(cur.lexeme,";")==0){
		cur = getNextToken(fp);
		printf("%s\n",cur.lexeme);
		declarations();
	}else{
		printf("Missing ; on row %d, col %d",cur.row,cur.col);
		exit(1);
	}
}

void datatype(){
	if(strcmp(cur.lexeme,"int") || strcmp(cur.lexeme,"char")){
		cur = getNextToken(fp);
		printf("%s\n",cur.lexeme);
		//PLS DONT FORGET TO RETURN CAUSE TERMINAL REACHED
		return;  //IMP next token selected for identifier_list
	}else{
		printf("Missing datatype on row %d, col %d",cur.row,cur.col);
		exit(1);
	}
}

void identifier_list(){
	if(!strcmp(cur.lexeme,"id")){
		cur = getNextToken(fp);
		printf("%s\n",cur.lexeme);
		A();
	}else{
		printf("Missing id on row %d, col %d",cur.row,cur.col);
		exit(1);
	}
}

void A(){
	if(!strcmp(cur.lexeme, ",")){
		cur = getNextToken(fp);
		printf("%s\n",cur.lexeme);
		identifier_list();
	}else if(!strcmp(cur.lexeme, "[")){
		cur = getNextToken(fp);
		printf("%s\n",cur.lexeme);
		if(!strcmp(cur.lexeme, "num")){
			cur = getNextToken(fp);
			printf("%s\n",cur.lexeme);
			if(!strcmp(cur.lexeme, "]")){
				cur = getNextToken(fp);
				B();
			}else{
				printf("Missing ] on row %d, col %d",cur.row,cur.col);
				exit(1);
			}
		}else{
			printf("Missing num on row %d, col %d",cur.row,cur.col);
			exit(1);
		}
	}else{
		return;   //EPSILON
	}
}

void B(){
	if(!strcmp(cur.lexeme,",")){
		cur = getNextToken(fp);
		printf("%s\n",cur.lexeme);
		identifier_list();
	}
	else
		return;
}

void statement_list(){
	if(!strcmp(cur.lexeme,"id")){  //or "if","while","for"
		// cur = getNextToken(fp);  WRONGG!!!!
		//We are getting token in statement() or uska next function
		statement();
		statement_list();
	}
	else
		return;
}

void statement(){
	assignstat();
	if(!strcmp(cur.lexeme,";")){
		cur = getNextToken(fp);  //YAHA PE KYU HAI??
		printf("%s\n",cur.lexeme);
	}else{
		printf("Missing ; on row %d, col %d",cur.row,cur.col);
		exit(1);
	}
}

void assignstat(){
	if(!strcmp(cur.lexeme,"id")){
		cur = getNextToken(fp);
		printf("%s\n",cur.lexeme);
		if(!strcmp(cur.lexeme,"=")){
			cur = getNextToken(fp);
			printf("%s\n",cur.lexeme);
			expn();
		}else{
			printf("Missing = on row %d, col %d",cur.row,cur.col);
			exit(1);
		}
	}else{
		printf("Missing id on row %d, col %d",cur.row,cur.col);
		exit(1);
	}
}

void expn(){
	simple_expn(); eprime();
}

void eprime(){
	if(!strcmp(cur.lexeme, "==")||!strcmp(cur.lexeme, "!=")||!strcmp(cur.lexeme, "<=")||!strcmp(cur.lexeme, ">=")){
		// dont do getNextToken here, done in relop
		relop();
		simple_expn();
	}else{
		return;
	}
}

void simple_expn(){
	term(); seprime();
}

void seprime(){
	if(!strcmp(cur.lexeme, "+")||!strcmp(cur.lexeme, "-")){
		addop();
		term();
		seprime();
	}else
		return;  //EPSILON
}

void term(){
	factor(); tprime();
}

void tprime(){
	if(!strcmp(cur.lexeme, "*")||!strcmp(cur.lexeme, "/")||!strcmp(cur.lexeme, "%")){
		mulop();
		factor();
		tprime();
	}
	else
		return;  //EPSILON
}

void factor(){
	if(!strcmp(cur.lexeme, "id")||!strcmp(cur.lexeme, "num")){
		cur = getNextToken(fp);
		printf("%s\n", cur.lexeme);
		//return; ????
	}else{
		printf("Missing id or num on row %d, col %d",cur.row,cur.col);
		exit(1);
	}
}

void relop(){
	if(!strcmp(cur.lexeme, "==")||!strcmp(cur.lexeme, "!=")||!strcmp(cur.lexeme, ">=")||!strcmp(cur.lexeme, "<=")){
		cur = getNextToken(fp);
		printf("%s\n", cur.lexeme);
		//return; ????
	}else{
		printf("Missing relop on row %d, col %d",cur.row,cur.col);
		exit(1);
	}
}

void addop(){
	if(!strcmp(cur.lexeme, "+")||!strcmp(cur.lexeme, "-")){
		cur = getNextToken(fp);
		printf("%s\n", cur.lexeme);
		//return; ????
	}else{
		printf("Missing addop on row %d, col %d",cur.row,cur.col);
		exit(1);
	}
}

void mulop(){
	if(!strcmp(cur.lexeme, "*")||!strcmp(cur.lexeme, "/")){
		cur = getNextToken(fp);
		printf("%s\n", cur.lexeme);
		//return; ????
	}else{
		printf("Missing mulop on row %d, col %d",cur.row,cur.col);
		exit(1);
	}
}

int main(){
	fp = fopen("input.c", "r");

	cur = getNextToken(fp);
	printf("%s\n", cur.lexeme);
	program();

	printf("ACCEPTED!!!");
	fclose(fp);
}