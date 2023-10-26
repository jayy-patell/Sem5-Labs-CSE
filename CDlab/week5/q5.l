%{ 
    /* Definition section */
    #include<stdio.h> 
    int num, r, digit=0, count, pcount=0, i; 
    char a[20]; 
%} 

DIGIT [0-9] 
/* Rule Section */
%% 

{DIGIT}+ { num=atoi(yytext); 

        while(num!=0) 
        { 

            r=num%16; 
            digit='0'+r; 
            if(digit>'9') 
            digit+=7; 
            a[count++]=digit; 
            num=num/16; 

        } 

        for(i=count-1;i>=pcount;--i) 
                printf("%c", a[i]); 
                pcount=count; 
        } 

.|\n ECHO; 
        
%% 

int yywrap() {
    return 1;
}

// driver code 
int main() 
{ 
    yylex(); 
    return 0; 
}     