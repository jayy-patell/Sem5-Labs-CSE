#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "spaces.h"
#include "preprocess.h"

struct token
{
    char token_name[50];
    int row, col;
};
static int row = 1, col = 1;

char specialsymbols[] = {'?', ';', ':', ','};
char relop[] = {'>', '<', '='};
char operators[] = {'+', '-', '*', '/', '%'};
char brackets[] = {'{', '}', '[', ']', '(', ')'};
char *Keywords[] = {"const", "char", "int", "return", "for", "while", "do", "switch", "if", "else", "unsigned", "case", "break"};

int isKeyword(char *str)
{
    for (int i = 0; i < sizeof(Keywords) / sizeof(char *); i++)
    {
        if (strcmp(str, Keywords[i]) == 0)
            return 1;
    }
    return 0;
}
int isOperator(char ch)
{

    for (int i = 0; i < sizeof(operators) / sizeof(char*); i++)
    {
        if (ch == operators[i])
            return 1;
    }
    return 0;
}
int isSpecialSymbol(char ch)
{

    for (int i = 0; i < sizeof(specialsymbols) / sizeof(char*); i++)
    {
        if (ch == specialsymbols[i])
            return 1;
    }
    return 0;
}
int isRelop(char ch)
{

    for (int i = 0; i < sizeof(relop) / sizeof(char*); i++)
    {
        if (ch == relop[i])
            return 1;
    }
    return 0;
}
int isBracket(char ch)
{

    for (int i = 0; i < sizeof(brackets) / sizeof(char*); i++)
    {
        if (ch == brackets[i])
            return 1;
    }
    return 0;
}

void CreateToken(struct token *tkn, char *c, int row, int col)
{
    tkn->row = row;
    tkn->col = col;
    tkn->token_name[0] = c;
}

void newLine()
{
    ++row;
    col = 1;
}

struct token getNextToken(FILE *fin)
{
    char c;
    char buff[100];
    struct token tkn = {.row = -1}; // for EOF file case
    int gotToken = 0;

    while (!gotToken && (c = fgetc(fin)) != EOF)
    {
        // special symbols
        if (isSpecialSymbol(c))
        {

            CreateToken(&tkn, c, row, col);
            gotToken = 1;
            ++col;
        }

        else if (isOperator(c))
        {
            //++ ,+ , -,--, =,==
            if (c == '+')
            {
                int d = fgetc(fin);
                if (d != '+')
                {
                    CreateToken(&tkn, "+", row, col);
                    gotToken = 1;
                    ++col;
                    fseek(fin, -1, SEEK_CUR);
                }
                else
                {
                    CreateToken(&tkn, "++", row, col);
                    gotToken = 1;
                    col += 2;
                }
            }
            else if (c == '-')
            {
                int d = fgetc(fin);
                if (d != '-')
                {
                    CreateToken(&tkn, "-", row, col);
                    gotToken = 1;
                    ++col;
                    fseek(fin, -1, SEEK_CUR);
                }
                else
                {
                    CreateToken(&tkn, "--", row, col);
                    gotToken = 1;
                    col += 2;
                }
            }
            else if (c == '=')
            {
                int d = fgetc(fin);
                if (d != '=')
                {
                    CreateToken(&tkn, "=", row, col);
                    gotToken = 1;
                    ++col;
                    fseek(fin, -1, SEEK_CUR);
                }
                else
                {
                    CreateToken(&tkn, "==", row, col);
                    gotToken = 1;
                    col += 2;
                }
            }
            else
            {
                CreateToken(&tkn, c, row, col);
                gotToken = 1;
                ++col;
            }
        }

        else if (isdigit(c))
        {
            tkn.row = row;
            tkn.col = col++;
            tkn.token_name[0] = c;
            int k = 1;
            while ((c = fgetc(fin)) != EOF && isdigit(c))
            {
                tkn.token_name[k++] = c;
                col++;
            }
            tkn.token_name[k] = '\0';
            gotToken = 1;
            fseek(fin, -1, SEEK_CUR);
        }

        else if (c == '\n')
        {
            newLine();
            c = fgetc(fin);
            if (c == '#')
            {
                while ((c = fgetc(fin)) != EOF && c != '\n')
                    ;
                newLine();
            }
            else if (c != EOF)
                fseek(fin, -1, SEEK_CUR);
        }

        else if (isspace(c))
            ++col;

        else if (isalpha(c) || c == '_')
        {
            tkn.row = row;
            tkn.col = col++;
            buff[0] = c;
            int k = 1;
            while ((c = fgetc(fin)) != EOF && isalnum(c))
            {
                buff[k++] = c;
                ++col;
            }
            buff[k] = '\0';
            if (isKeyword(buff))
                strcpy(tkn.token_name, buff);
            else
                strcpy(tkn.token_name, buff);
            gotToken = 1;
            fseek(fin, -1, SEEK_CUR);
        }

        else if (c == '"')
        {
            tkn.row = row;
            tkn.col = col;
            strcpy(tkn.token_name, "StringLiteral");
            int k = 1;
            while ((c = fgetc(fin)) != EOF && c != '"')
            {
                k++;
                ++col;
            }
            gotToken = 1;
        }

        else if (c == '<' || c == '>' || c == '!')
        {
            switch (c)
            {
            case '>':

                CreateToken(&tkn, ">", row, col);
                break;
            case '<':

                CreateToken(&tkn, "<", row, col);
                break;
            case '!':

                CreateToken(&tkn, "!", row, col);
                break;
            default:
                break;
            }
            ++col;
            int d = fgetc(fin);
            if (d == '=')
            {
                ++col;
                strcat(tkn.token_name, "=");
            }
            else
            {
                if (c == '!')
                    strcpy(tkn.token_name, "!=");
                fseek(fin, -1, SEEK_CUR);
            }
            gotToken = 1;
        }
        else if (isBracket(c))
        {
            CreateToken(&tkn, c, row, col);
            gotToken = 1;
            ++col;
        }
        else
            ++col;
    }
    return tkn;
}
int main()
{
    FILE *fin = fopen("inp_prepro.c", "r");
    FILE *fo = fopen("output.txt", "w+");

    space();
    process();

    if (!fin)
    {
        printf("Error! File cannot be opened main!\n");
        exit(1);
    }

    struct token tkn;
    while ((tkn = getNextToken(fin)).row != -1) // EOF File case for row -1
        fprintf(fo, "<%s, %d, %d>\n", tkn.token_name, tkn.row, tkn.col);
    fclose(fin);
}