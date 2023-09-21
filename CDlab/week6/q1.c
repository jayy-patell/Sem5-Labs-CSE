#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int curr=0;
char str[100];

void invalid() {
	printf("ERROR!"); exit(0);
}

void valid() {
	printf("SUCCESS!"); exit(0);
}

void S();
void T();
void Tprime();

void S(){
	if(str[curr] == 'a')
		curr++;
	else if(str[curr] == '>')
		curr++;
	else if(str[curr] == '('){
		curr++;
		T();
		if(str[curr] == ')'){
			curr++;
		}else{
			invalid();
		}
	}else{
		invalid();
	}	
}

//dont do curr++ when non-terminal present
void Tprime(){
	if(str[curr] == ','){
		curr++;
		S();
		Tprime();
	}
	// else{
	// 	invalid();
	// }
}

void T(){
	S();
	Tprime();
}


int main(){
	printf("Enter String: ");
	scanf("%s", str);
	S();
	if(str[curr] == '$')
		valid();
	else
	{
		// printf("%c\n", str[curr]);
		invalid();
	}
}