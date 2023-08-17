#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct token{
	char token_name[];
	unsigned int row,col;
}

const char specialsymbols[] = {'?', ';', ':', ','};
const char *Keywords[] = {"const", "char", "int", "return", "for", "while", "do", "switch", "if", "else", "unsigned", "case", "break"};
const char arithmeticsymbols[] = {'*'};

int main(){
	return 0;
}