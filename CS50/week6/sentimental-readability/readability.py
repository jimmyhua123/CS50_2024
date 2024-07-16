import math

def main():
    L = 0
    S = 0
    W = 1  # 初始設為1，因為最後一個單詞不會被空格計數

    text = input("Text: ")

    for i in range(len(text)):
        # 計算字母數
        if text[i].isalpha():
            L += 1

        # 計算句子數
        if text[i] in ['.', '?', '!']:
            S += 1

        # 計算單詞數
        if text[i] == ' ':
            W += 1

    L = (L / W) * 100 * 0.0588
    S = (S / W) * 100 * 0.296
    index = L - S - 15.8
    index = round(index)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")

if __name__ == "__main__":
    main()
