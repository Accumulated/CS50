import cs50
import sys


def main():

    # Check for argv
    if not len(sys.argv) == 2:
        print("Usage: python bleep.py dictionary")
        sys.exit(1)

    else:
        # Open file with read
        ban = open(sys.argv[1], "r")

        # Making a set of banned words
        a = {xxx.strip() for xxx in ban}
        print(f"{a}")

        # Prompt user for input
        question = cs50.get_string("What message would you like to censor?\n")

        # Input list
        string = question.split()

        # List buffer for output final result
        final = list()
        flag = 0

        #  Initializing checking on string process

        # Input string
        for squestion in string:
            # Banned text
            for sbanned in a:
                # Checking for banned words
                if (squestion).lower() == (sbanned).lower():
                    flag = 1
                    buff = stars(len(sbanned))
                    final.append(buff)

            # Flag to indicate if i already wrote in the buffer list
            if not flag == 1:
                final.append(squestion)
            else:
                flag = 0

    # Join all the list in one string with spaces imbetween each
    out = ' '.join(final)
    print(f"{out}")


def stars(length):
    buff = '*'
    for i in range(length-1):
        buff = buff + '*'
    return buff


if __name__ == "__main__":
    main()
