//Program to remove single and multiline comments from a given ‘C’ file.

#include <stdio.h>
#include <stdlib.h>
int main()
{
    FILE *fa, *fb;
    int ca, cb;
    fa = fopen("input.txt", "r");
    if(!fa)
    {
        printf("Cant Open File!\n");
        exit(0);
    }
    fb = fopen("output.txt", "w");
    ca = getc(fa);
    while(ca != EOF)
    {
        if(ca == ' ')
        {
            putc(ca, fb);
            while(ca == ' ')
                ca = getc(fa);
        }
        if(ca == '/')
        {
            cb = getc(fa);
            if(cb == '/')
            {
                while(ca != '\n')
                    ca = getc(fa);
            }
            else if(cb == '*')
            {
                do
                {
                    while(ca != '*')
                        ca = getc(fa);
                    ca = getc(fa);
                } while(ca != '/');
            }
            else
            {
                putc(ca, fb);
                putc(cb, fb);
            }
        }
        else
            putc(ca, fb);

        ca = getc(fa);
    }
    fclose(fa);
    fclose(fb);
    return 0;
}