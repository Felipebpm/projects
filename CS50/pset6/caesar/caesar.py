import sys
from cs50 import get_string


def main():
    if len(sys.argv) == 2:
        n = int(sys.argv[1])
        s = get_string("plaintext: ")
        caesar = []
        # Encrypting
        for k in s:
            # Making sure caption is ok
            if k.isupper():
                c = ((ord(k) - ord("A") + n) % 26) + ord("A")
                caesar.append(chr(c))
            elif k.islower():
                c = ((ord(k) - ord("a") + n) % 26) + ord("a")
                caesar.append(chr(c))
            else:
                caesar.append(k)
        print("ciphertext: ", end='')
        print("".join(caesar))
        exit(0)
    else:
        print("Usage: ./caesar k")
        exit(1)


if __name__ == "__main__":
    main()