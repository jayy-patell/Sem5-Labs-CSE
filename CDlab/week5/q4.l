%{
#include<stdio.h>
int sf=0,pf=0;
%}

/* defined section */

%%
"scanf"    { sf++; fprintf(yyout,"READ");}           // replace scanf  with readf
"printf" { pf++; fprintf(yyout,"WRITE");}            // replace printf  with writef


%%

int yywrap() {
    return 1;
}

 

int main()
{
    yyin=fopen("open.c","r");                            // input file open.c
    yyout=fopen("new.c","w");                           // output file new.c with replace 
    yylex();

     //no of printf and scanf in the file
    printf("Number of scanfs=%d\nNumber of Printf's=%d\n",sf,pf);

return 0;

}