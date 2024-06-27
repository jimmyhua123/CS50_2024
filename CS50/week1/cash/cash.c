#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int num, c25 = 0, c10 = 0, c5 = 0, c1 = 0, total = 0;
    while (true)
    {
        num = get_int("Change owed: ");
        if (num >= 0)
        {
            break;
        }
    }
    if (num > 0)
    {
        if (num >= 25)
        {
            c25 = num / 25;
            num = num % 25;
        }
        if (num >= 10)
        {
            c10 = num / 10;
            num = num % 10;
        }
        if (num >= 5)
        {
            c5 = num / 5;
            num = num % 5;
        }
        if (num >= 1)
        {
            c1 = num;
        }
        total = c25 + c10 + c5 + c1;
        printf("%d\n", total);
    }
    else if (num == 0)
    {
        printf("%d\n", num);
    }
}
