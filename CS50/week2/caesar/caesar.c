#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> // 為了使用 atoi 函數
#include <string.h>

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage ./caesar key\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage ./caesar key\n");
            return 1;
        }
    }
    string pt;
    int input = atoi(argv[1]);
    pt = get_string("plaintext:  ");
    printf("ciphertext: ");
    for (int j = 0; j < strlen(pt); j++)
    {

        char c = pt[j];
        if (isupper(c))
        {
            c = ((c - 'A' + input) % 26) + 'A';
        }
        else if (islower(c))
        {
            c = ((c - 'a' + input) % 26) + 'a';
        }

        printf("%c", c);
    }
    printf("\n");
    return 0;
}
