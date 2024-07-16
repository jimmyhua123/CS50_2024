#include <cs50.h>
#include <stdio.h>

int main(void)
{
    char *s = "HI!";
    string c = "HI!";
    string *p = &c;
    printf("%c\n", *s);
    printf("%c\n", s[0]);
    printf("%s\n", s);
    printf("%s\n", c);
    printf("%p\n", p);
}
