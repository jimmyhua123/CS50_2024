#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    double index, L = 0, S = 0, W = 0;
    string text = get_string("Text: ");
    for (int i = 0; i < strlen(text); i++)
    { // for how many letters

        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            L++;
        }
        //I don't how it works
        //  if (isalpha(text[i]))
        // {
        //     L++;
        // }
        // for how many sentences
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            S++;
        }
        // for how many words
        if (text[i] == ' ')
        {
            W++;
        }
        // For last char
        if ((text[i] == ',' || text[i] == '.' || text[i] == '?' || text[i] == '!') &&
            i == (strlen(text) - 1))
        {
            W++;
        }
    }

    L = (L / W) * 100 * 0.0588;
    S = (S / W) * 100 * 0.296;
    index = L - S - 15.8;
    index = round(index);
    if (index < 2)
    {
        printf("Before Grade 1");
    }
    else if (index > 16)
    {
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %d", (int) index);
    }

    printf("\n");
}
