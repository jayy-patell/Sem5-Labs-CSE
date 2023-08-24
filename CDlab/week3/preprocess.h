// int process()
// {
//     FILE *fin = fopen("inp3.c", "r");
//     FILE *fo = fopen("inp2.c", "w+");
//     char c = 0;
//     char buffer[100];
//     buffer[0] = '\0';
//     int i = 0;
//     char *includeStr = "include", *defineStr = "define";
//     //int mainFlag = 0;
//     c = fgetc(fin);
//     while (c != EOF)
//     {
//         if (c == '#')
//         {
//             while (c != ' ')
//             {
//                 c = fgetc(fin);
//                 buffer[i++] = c;
//             }
//             buffer[i] = '\0';
//             if (strstr(buffer, includeStr) != NULL || strstr(buffer, defineStr) != NULL)
//             {
//                 while (c != '\n')
//                 {
//                     c = fgetc(fin);
//                 }
//             }
//             else
//             {
//                 fputc('#', fo);
//                 for (int j = 0; j < i; j++)
//                 {
//                     fputc(buffer[j], fo);
//                 }
//                 while (c != '\n')
//                 {
//                     c = fgetc(fin);
//                     fputc(c, fo);
//                 }
//             }
//             i = 0;
//             buffer[0] = '\0';
//         }
//         else
//         {
//             if (c == ' ' || c == '\n')
//             {
//                 buffer[0] = '\0';
//                 i = 0;
//             }
//             fputc(c, fo);
//         }
//         c = fgetc(fin);
//     }
//     fclose(fin);
//     fclose(fo);
//     return 0;
// }


int is_directive(const char *str, const char **directives)
{
    for(int i = 0 ; i < sizeof(directives)/sizeof(char *); i++)
    {
        if(strncmp(str, directives[i], strlen(directives[i])) == 0)
            return 1;
    }
    return 0;
}
int process()
{
    FILE *fin = fopen("inp_space.c", "r");
    FILE *fo = fopen("inp_prepro.c", "w+");
    const char *directives[] = {"#include", "#define", "#if"};
    char buffers[2048];
    if(!fin || !fo)
    {
        perror("Cant Open File! preprocess\n");
        return 1;
    }
    // char c = 0;
    // char buffer[100];
    // buffer[0] = '\0';
    // int i = 0;
    // char *includeStr = "include", *defineStr = "define";
    // int mainFlag = 0;
    // c = fgetc(fin);
    
    while(fgets(buffers, 2048, fin) != NULL)
    {
        if(!is_directive(buffers, directives))
            fputs(buffers, fo);
    }

    fclose(fin);
    fclose(fo);
    return 0;
}