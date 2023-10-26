%{
    int cp = 0;
    int cn = 0;
    int cpf = 0;
    int cnf = 0;
%}
%%
[-][0-9]+[.][0-9]+ {cnf++;}
[0-9]+[.][0-9]+ {cpf++;}
[-][0-9]+ {cn++;}
[0-9]+ {cp++;}
%%
int yywrap(){return 1;}
int main()
{
    printf("Enter the numbers:\n");
    yylex();
    printf("Number of +ve integers are:  %d\n", cp);
    printf("Number of -ve integers are:  %d\n", cn);
    printf("Number of +ve floating are:  %d\n", cpf);
    printf("Number of -ve floating are:  %d\n", cnf);
    return 0;
} 