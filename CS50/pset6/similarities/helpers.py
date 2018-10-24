from cs50 import get_string
from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    lsa = set()
    lsb = set()
    for i in a.splitlines():
        lsa.add(i)
    for j in b.splitlines():
        lsb.add(j)
    return list(lsa & lsb)


def sentences(a, b):
    """Return sentences in both a and b"""
    lsa = set(sent_tokenize(a))
    lsb = set(sent_tokenize(b))
    return list(lsa & lsb)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    lsa = set()
    lsb = set()
    for i in range(len(a) - n + 1):
        lsa.add(a[i:(i + n)])
    for j in range(len(b) - n + 1):
        lsb.add(b[j:(j + n)])
    return list(lsa & lsb)