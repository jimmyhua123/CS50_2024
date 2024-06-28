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
        printf("Usage ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.n");
        return 1;
    }
    int letter_count[26] = {0};
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        int letter_num = tolower(argv[1][i]) - 'a';
        letter_count[letter_num]++;
        if (letter_count[letter_num] > 1)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }

    string pt, key = argv[1];
    pt = get_string("plaintext:  ");
    printf("ciphertext: ");
    for (int j = 0; j < strlen(pt); j++)
    {

        if (isalpha(pt[j]))
        {
            if (isupper(pt[j]))
            {
                printf("%c", toupper(key[pt[j] - 'A']));
            }
            else if (islower(pt[j]))
            {
                printf("%c", tolower(key[pt[j] - 'a']));
            }
        }
        else
        {
            printf("%c", pt[j]);
        }
    }
    printf("\n");
    return 0;
}
