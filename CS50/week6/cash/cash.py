while True:
    try:
        x = float(input("Change: "))
        if x > 0:
            x = round(x, 2)
            break
        else:
            print("Please enter a positive amount.")
    except ValueError:
        print("Invalid input. Please enter a number.")

count = 0

# 使用一個列表來表示硬幣的值
coins = [0.25, 0.10, 0.05, 0.01]

for coin in coins:
    while x >= coin:
        x = round(x - coin, 2)  # 減去硬幣的值並更新 x，四捨五入到兩位小數
        count += 1

print(count)
