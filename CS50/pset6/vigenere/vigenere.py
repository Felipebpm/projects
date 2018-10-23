from cs50 import get_string
import sys


def main():
    if len(sys.argv) == 2:
        f = sys.argv[1]
        strlen = len(sys.argv[1])
        key = []

        for k in f:
            if k.isupper():
                t = ord(k) - ord('A')
                key.append(t)
            elif k.islower():
                t = ord(k) - ord('a')
                key.append(t)
            else:
                print("Usage: ./vigenere k")
                exit(1)
        s = get_string("plaintext: ")
        n = 0
        vigenere = []

        for w in range(len(s)):
            # Making sure caption is ok
            if s[w].isupper():
                o = chr(((ord(s[w]) - ord('A') + key[n % strlen]) % 26) + ord('A'))
                n += 1
                vigenere.append(o)
            elif s[w].islower():
                o = chr(((ord(s[w]) - ord('a') + key[n % strlen]) % 26) + ord('a'))
                n += 1
                vigenere.append(o)
            else:
                vigenere.append(s[w])
        print("ciphertext: ", end='')
        print("".join(vigenere))
        exit(0)
    else:
        print("Usage: python vigenere.py [key]")
        exit(1)


if __name__ == "__main__":
    main()