#include <stdio.h>
#include <cs50.h>

int main(void)

{
    float c;
    int i;
// Getting input
    do
    {
        c = get_float("Change owed: ");
    }
    while (c < 0);

    i = 0;
// 25 cents
    if (c >= 0.2495)
    {
        do
        {
            c = c - 0.25;
            i++;
        }
        while (c >= 0.2495);
    }
// 10 cents
    if (c >= 0.0995)
    {
        do
        {
            c = c - 0.10;
            i++;
        }
        while (c >= 0.0995);
    }
// 5 cents
    if (c >= 0.0495)
    {
        do
        {
            c = c - 0.05;
            i++;
        }
        while (c >= 0.0495);
    }
// 1 cent
    if (c >= 0.009)
    {
        do
        {
            c = c - 0.01;
            i++;
        }
        while (c >= 0.009);
    }
// Displaying result
    printf("%i\n", i);
}