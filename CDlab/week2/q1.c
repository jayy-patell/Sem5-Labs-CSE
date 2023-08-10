#include <stdio.h>
#include <stdlib.h>
int main()
{
    int flag = 0;
    char c;
    FILE *fa, *fb;
    fa = fopen("input.txt", "r");
    fb = fopen("q1out.txt", "w+");
    if(!fa || !fb)
    {
        perror("Cant Open File!\n");
        return 1;
    } 

    c = fgetc(fa);
    while(c!=EOF)
    {
        
        if(!flag && (c == ' ' || c == '\t'))
        {
            fputc(' ', fb);
            flag = 1;
        }
        else if(!(c == ' ' || c == '\t'))
        {
            flag = 0;
            fputc(c, fb);
        }
        c = fgetc(fa);
    }
    fclose(fa);
    fclose(fb);
}