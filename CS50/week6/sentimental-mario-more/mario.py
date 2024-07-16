while True:
    try:
        x = int(input("Height: "))
        if 1 <= x <= 8:
            break
        else:
            print("Please enter an integer between 1 and 8.")
    except ValueError:
        print("Invalid input. Please enter an integer.")

for i in range(x):
    # 打印空格
    for j in range(x - i - 1):
        print(" ", end="")
    # 打印 #
    for k in range(i + 1):
        print("#", end="")
    # 每行結束後換行
    print("  ",end="")
    for z in range(i + 1):
        print("#", end="")
    print()
