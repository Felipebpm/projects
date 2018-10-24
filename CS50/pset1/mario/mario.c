#include <stdio.h>
#include <cs50.h>

int main(void)

{
    // Asks height from user
    int k;
    int h;
    do
    {
        h = get_int("Height: ");
    }
    while (h < 0 | h > 23);

    // Builds pyramid
    for (k = 0; k < h; k++)
    {
        //add \n h-k+2 times
        for (int i = 0; i < (h - k - 1); i++)
        {
            printf(" ");
        }
        for (int j = 0; j < (k + 2); j++)
        {
            printf("#");
        }

        printf("\n");
    }
}
