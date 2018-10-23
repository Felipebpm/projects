#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])

{
    if (argc == 2)
    {
        string f = argv[1];
        int al = strlen(f);
        int z;
        for (z = 0; z < al; z++)
        {
            if (f[z] >= 'A' && f[z] <= 'Z')
            {
                f[z] = f[z] - 'A';
            }
            else if (f[z] >= 'a' && f[z] <= 'z')
            {
                f[z] = f[z] - 'a';
            }
            else
            {
                printf("Usage: ./vigenere k");
                return 1;
            }

        }
        string s = get_string("plaintext: ");
        int i = strlen(s);
        int k;
        int n = 0;

        if (al >= i)
        {
            for (k = 0; k < i; k++)
            {
                //Making sure caption is ok
                if (s[k] >= 'A' && s[k] <= 'Z')
                {
                    s[k] = ((s[k] - 'A' + f[n]) % 26) + 'A';
                    n++;
                }
                else if (s[k] >= 'a' && s[k] <= 'z')
                {
                    s[k] = ((s[k] - 'a' + f[n]) % 26) + 'a';
                    n++;
                }
                else
                {
                    s[k];
                }
            }
        }
        else
        {
            for (k = 0; k < i; k++)
            {
                {
                    //Making sure caption is ok
                    if (s[k] >= 'A' && s[k] <= 'Z')
                    {
                        s[k] = ((s[k] - 'A' + f[n % al]) % ('Z' - 'A' + 1)) + 'A';
                        n++;
                    }
                    else if (s[k] >= 'a' && s[k] <= 'z')
                    {
                        s[k] = ((s[k] - 'a' + f[n % al]) % ('z' - 'a' + 1)) + 'a';
                        n++;
                    }
                    else
                    {
                        s[k];
                    }
                }
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
