while (True):
    try:
        height = int(input("Height: "))
        if height in range(1, 9, 1):
            for i in range(height):
                print(" " * (height - i - 1) + "#" * (i + 1) + "  " + "#" * (i + 1))
            break
    except ValueError:
        print("Oops!  That was no valid number between 1 and 8.  Try again...")
