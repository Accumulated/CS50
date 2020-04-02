import sys
from sys import argv
import cs50


def main():

    # Checking for main argc to be 2
    if len(argv) == 2:
        # Checking over the input chars.
        c_flag = check(len(sys.argv[1]), sys.argv[1])

        # Sequence for valid input only
        if c_flag == True:
            # Shift amount transformed from String to int
            typed = sys.argv[1]
            key = []

            Dec = 0
            summation = 0
            n_shift = len(typed)
            multi = 0
            times = n_shift - 1

            for i in range(n_shift):

                multi = 0
                Dec = int(typed[i]) % 48

                if multi == times:
                    Dec = Dec * 1

                else:
                    while multi < times:

                        Dec = Dec * 10
                        multi += 1

                key.append(Dec)
                summation = summation + Dec
                times -= 1

            # Cipher Generation
            plain = cs50.get_string("plain text: ")
            s = []

            # Ciphertext generating
            for i in plain:

                if i >= 'A' and i <= 'Z':

                    if ord(i) + summation > 90:

                        while ord(i) + summation > 90:
                            i = chr((ord(i) + summation) % 91 + 65)
                            if i >= 'A' and i <= 'Z':
                                break
                            else:
                                i = chr(ord(i) % 123 + 97)

                        s.append(i)

                    else:
                        i = chr((ord(i) + summation) % 91)
                        s.append(i)

                # Small letters
                elif i >= 'a' and i <= 'z':

                    if (ord(i) + summation) > 122:

                        i = chr((ord(i) + summation) % 123 + 97)

                        while True:
                            if i >= 'a' and i <= 'z':
                                break
                            else:
                                i = chr(ord(i) % 123 + 97)

                        s.append(i)

                    else:
                        i = chr((ord(i) + summation) % 123)
                        s.append(i)

                else:
                    s.append(i)

            c = ''.join(s)
            print(f"ciphertext: {c}")

        else:
            print(" Usage: ./caesar key ")
            sys.exit(1)

    else:
        print(" Usage: ./caesar key ")
        sys.exit(1)


# Check for validation of input
def check(length, nano):

    check = 0
    for i in range(length):
        c = nano[i]

        # Checking for inputs rather than numbers
        if c >= '0' and c <= '9':
            continue
        else:

            i = length
            check = 1

    if check == 1:

        return False

    else:

        return True


if __name__ == "__main__":
    main()