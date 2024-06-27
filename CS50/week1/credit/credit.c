#include <cs50.h>
#include <stdio.h>

long count(long cnum)
{
    long c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    while (cnum != 0)
    {
        c3 = cnum % 10;
        cnum = cnum / 10;
        c2 = cnum % 10 * 2;
        if (c2 >= 10)
        {
            c4 = c2 % 10;
            c2 = c2 / 10;
        }
        c1 = c1 + c2 + c3 + c4;
        cnum = cnum / 10;
        c4 = 0;
    }
    if (c1 % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(void)
{
    long num = get_long("Number:  ");
    long ans = 0, length = 0, nl;
    nl = num;
    while (nl != 0)
    {
        length++;
        nl /= 10;
    }

    if (count(num) == true)
    {

        if (length == 16)
        {
            int d2 = num / 100000000000000;
            if (d2 >= 40 && d2 < 50)
            {
                printf("VISA\n");
            }
            else if (d2 == 51 || d2 == 52 || d2 == 53 || d2 == 54 || d2 == 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        else if (length == 15)
        {
            int d2 = num / 10000000000000;
            if (d2 == 34 || d2 == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (length == 13)
        {
            int d2 = num / 100000000000;
            if (d2 >= 40 && d2 < 50)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
