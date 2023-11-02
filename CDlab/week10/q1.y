%{
#include<stdio.h>
#include<stdlib.h>
int yylex();
int yyerror();
int yyparse();
%}

//INT - data-TYPE
//ID  - identifier
//SC  - Semi-Colon
//CM  - Comma
//NL  - NewLine
//DC  - Declaration
//IDL - Identifier List

%token INT ID SC CM NL
%%
stmt : DC NL
;
DC : DT IDL SC { printf("Valid declaration statement!\n"); exit(0);}
;
DT : INT
;
IDL: ID |ID CM IDL 
;
%%
int yyerror(char *msg)
{
printf("Invalid declaration statement!\n");
exit(0);
}
void main ()
{
printf("Enter the declaration statement:\n");
yyparse();
}