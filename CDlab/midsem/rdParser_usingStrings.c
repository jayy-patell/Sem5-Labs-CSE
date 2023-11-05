#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int curr=0;
char str[100];

void invalid(){
	printf("ERROR!"); exit(1);
}
void valid(){
	printf("SUCCESS!"); exit(0);
}

int isID(){
	if(isalpha(str[curr]) || str[curr]=='_'){
		curr++;
		while(isalnum(str[curr])){
			curr++;
		}
		return 1;
	}else{
		return 0;
	}
}

void E();
void eprime();
void T();
void tprime();
void F();

void E(){
	T();
	eprime();
}

void eprime(){
	if(str[curr] == '+'){
		curr++; T();eprime();
	}else if(str[curr] == '-'){
		curr++; T();eprime();
	}else{
		return;
	}
}

void T(){
	F(); 
	tprime();
}

void tprime(){
	if(str[curr] == '*'){
		curr++; F();tprime();
	}else if(str[curr] == '/'){
		curr++; F();tprime();
	}else{
		return;
	}
}

void F(){
	if(str[curr]=='('){
		curr++;
		E();
		if(str[curr]==')'){
			curr++; return; 
		}else{
			invalid();
		}
	}
	else if(isID()){
		return;
	}
	else{
		invalid();
	}
}

int main() {
	printf("Enter a string: ");
	scanf("%s", str);
	E();
	if(str[curr] == '$')
		valid();
	else
		invalid();
	return 0;
}