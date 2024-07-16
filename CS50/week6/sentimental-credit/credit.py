def count(cnum):
    c1 = 0
    c2 = 0
    c3 = 0
    c4 = 0
    while cnum != 0:
        c3 = cnum % 10
        cnum = cnum // 10
        c2 = (cnum % 10) * 2
        if c2 >= 10:
            c4 = c2 % 10
            c2 = c2 // 10
        c1 = c1 + c2 + c3 + c4
        cnum = cnum // 10
        c4 = 0
    return c1 % 10 == 0

def main():
    num = int(input("Number:  "))
    length = len(str(num))

    if count(num):
        if length == 16:
            d2 = num // 100000000000000
            if 40 <= d2 < 50:
                print("VISA")
            elif 51 <= d2 <= 55:
                print("MASTERCARD")
            else:
                print("INVALID")
        elif length == 15:
            d2 = num // 10000000000000
            if d2 == 34 or d2 == 37:
                print("AMEX")
            else:
                print("INVALID")
        elif length == 13:
            d2 = num // 100000000000
            if 40 <= d2 < 50:
                print("VISA")
            else:
                print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")

if __name__ == "__main__":
    main()
