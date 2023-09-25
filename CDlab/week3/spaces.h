// Removes multiple spaces and comments from a C program

int space()
{
    FILE *fin, *fo;
    int ca, cb;
    fin = fopen("inp.c", "r");
    if (fin == NULL)
    {
        printf("Cannot open file! space\n");
        exit(0);
    }
    fo = fopen("inp_space.c", "w+");
    ca = getc(fin);
    while (ca != EOF)
    {
        if (ca == ' ' || ca == '\t')
        {
            putc(' ', fo);
            while (ca == ' ' || ca == '\t')
                ca = getc(fin);
        }
        if (ca == '/')
        {
            // can also be done using ca and fseek(-1, SEEK_CUR)
            ca = getc(fin);
            if (ca == '/')
            {
                while (ca != '\n')
                    ca = getc(fin);
            }
            else if (ca == '*')
            {
                do
                {
                    while (ca != '*')
                        ca = getc(fin);
                    ca = getc(fin);
                } while (ca != '/');
            }
            else
            {
                putc(ca, fo);
                // putc(cb, fo);
            }
        }
        else
            putc(ca, fo);
        ca = getc(fin);
    }
    fclose(fin);
    fclose(fo);
    return 0;
}