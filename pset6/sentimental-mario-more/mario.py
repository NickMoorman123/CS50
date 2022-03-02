while True:
    try:
        height = int(input("Height: "))
        if height > 0 and height <= 8:
            break
    except:
        continue
    

for i in range(0, height):
    print(" " * (height - i - 1) + "#" * (i + 1) + "  " + "#" * (i + 1))