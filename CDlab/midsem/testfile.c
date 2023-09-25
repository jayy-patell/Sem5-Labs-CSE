#include <stdio.h>
#include <conio.h>
int func(int a, int b)
{
    int c = a + b;
    return c;
}
int main()
{
    int a = 5;
    int b = 6;
    int c = func(a, b);
    printf("%d", c);
}