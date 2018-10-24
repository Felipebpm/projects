#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])

{
    if (argc == 2)
    {
        string str = argv[1];
        int n = atoi(str);
        string s = get_string("plaintext: ");
        //Encrypting
        int i = strlen(s);
        int k;
        for (k = 0; k < i; k++)
        {
            //Making sure caption is ok
            if (s[k] >= 'A' && s[k] <= 'Z')
            {
                s[k] = ((s[k] - 'A' + n) % 26) + 'A';
            }
            else if (s[k] >= 'a' && s[k] <= 'z')
            {
                s[k] = ((s[k] - 'a' + n) % 26) + 'a';
            }
            else
            {
                s[k] = s[k];
            }
        }

        printf("ciphertext: %s\n", s);
    }
    else
    {
        printf("Usage: ./caesar k");
        return 1;
    }
}