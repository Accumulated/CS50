import cs50


def main():

    cc_number = cs50.get_int("Number: ")

    ccc_number = cc_number
    count = 0

    while not ccc_number == 0:
        count += 1
        ccc_number //= 10

    if count == 13:
        visa(cc_number)

    elif count == 15:
        check(cc_number, count)

    elif count == 16:
        check(cc_number, count)

    else:
        print("INVALID")


# Check for length 16 and AMEX
def check(number_c, count):

    b_l = 0
    i = 0
    number = number_c
    if count == 16:
        number_c //= 100000000000000
    else:
        number_c //= 10000000000000

    if b_l == 0 and i == 0:

        b_l = number_c % 10
        i += 1

    l = number_c % 10
    number_c //= 10

    while number_c:

        if b_l == 0 and i == 0:
            b_l = number_c % 10
            i += 1
        l = number_c % 10
        number_c //= 10

    if l == 4:
        visa(number)

    elif l == 5:
        mastercard(number, l, b_l)

    else:
        amex(number, l, b_l)


# MASTERCARD initialization
def mastercard(number_m, l_m, b_l_m):
    if l_m == 5:

        if b_l_m == 1 or b_l_m == 2 or b_l_m == 3 or b_l_m == 4 or b_l_m == 5:
            x = l12digit(number_m)
            y = l22digit(number_m)
            z = x + y
            b_l = z % 10
            if b_l == 0:
                print("MASTERCARD")

        else:
            print("INVALID")

    else:
        print("INVALID")


# VISA initialization
def visa(number_v):
    x = l12digit(number_v)
    y = l22digit(number_v)
    z = x + y
    b_l = z % 10
    if b_l == 0:
        print("VISA")
    else:
        print("INVALID")


# AMERICAN EXPRESS initialization
def amex(number_a, l_a, b_l_a):

    if l_a == 3:

        if b_l_a == 4 or b_l_a == 7:

            x = l12digit(number_a)
            y = l22digit(number_a)
            z = x + y
            b_l = z % 10
            if b_l == 0:
                print("AMEX")

        else:
            print("INVALID")

    else:
        print("INVALID")


# Checksum initialization
# 1st to last digits summation
def l12digit(number1):

    sum = 0
    sum = sum + number1 % 10
    number1 //= 100

    while number1:
        sum = sum + number1 % 10
        number1 //= 100

    return (sum)


# Doubled 2nd to last digits summation
def l22digit(number2):
    sum = 0
    number2 //= 10

    if 2 * (number2 % 10) > 9:
        score_x = 2 * (number2 % 10)
        for i in range(2):
            sum = sum + score_x % 10
            score_x //= 10

    else:
        sum = sum + 2 * (number2 % 10)

    number2 //= 100

    while number2:
        if 2 * (number2 % 10) > 9:
            score_x = 2 * (number2 % 10)
            for i in range(2):

                sum = sum + score_x % 10
                score_x //= 10

        else:

            sum = sum + 2 * (number2 % 10)

        number2 //= 100

    return (sum)


if __name__ == "__main__":
    main()