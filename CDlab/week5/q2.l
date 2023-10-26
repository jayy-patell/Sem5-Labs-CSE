%{
int wordCount = 0;
int charCount = 0;
int blankCount = 0;
int lineCount = 0;
%}

%%
[a-zA-Z]+ { wordCount++; charCount += yyleng; }
[ \t] { blankCount++; charCount++; }
\n { lineCount++; charCount++; }


%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    printf("Number of words: %d\n", wordCount);
    printf("Number of characters: %d\n", charCount);
    printf("Number of blanks: %d\n", blankCount);
    printf("Number of lines: %d\n", lineCount);
    return 0;
}