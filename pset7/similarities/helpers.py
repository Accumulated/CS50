from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    first = a.splitlines()
   #print(f"{first}")
    second = b.splitlines()

    result = []
    out = []

    for a_line in first:
        for b_line in second:
            if(a_line == b_line and not a_line in result):
                result.append(a_line.strip())


    return result

def sentences(a, b):
    """Return sentences in both a and b"""

    first = sent_tokenize(a)
  #  print(f"{first}")
    second = sent_tokenize(b)

    result = []

    for a_line in first:
        for b_line in second:
            if(a_line == b_line and not a_line in result):
                result.append(a_line.strip())

    return result


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    first = string_help(a, n)
   # print(f"{first}")
    second = string_help(b, n)
  #  print(f"{second}")


    result = []

    for a_line in first:
        for b_line in second:
            if(a_line == b_line and not a_line in result):
                result.append(a_line.strip())

    return result


def string_help(string, n):

    fin = []
    y = n
    for c in range(len(string)-1):
        out = string[c:n]
        if(len(out) == y):
            fin.append(out)
        n += 1
    return fin