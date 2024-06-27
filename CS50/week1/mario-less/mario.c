#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int num;
    while (true)
    {
        num = get_int("Height: ");
        if (num >= 1 && num <= 8)
        {
            break;
        }
    }
    if (num > 0)
    {
        for (int i = 1; i <= num; i++)
        {
            for (int j = num - i; j > 0; j--)
            {
                printf(" ");
            };
            for (int k = 0; k < i; k++)
            {
                printf("#");
            };
            printf("\n");
        }
    }
}
