import sys

while True:
    try:
        number = int(input("Number: "))
        break
    except:
        continue

if number <= 999999999999 or (number >= 10000000000000 and number <= 99999999999999) or number >= 10000000000000000:
    print("INVALID")
    sys.exit()

def main():
    # get first two to check provider
    first_two = number // power(10, (card_length(number) - 2))
    
    Luhn = check(number)
    
    # if valid and a sensical pair of first numbers
    if Luhn and (first_two == 34 or first_two == 37):
        print("AMEX")
    elif Luhn and first_two >= 51 and first_two <= 55:
        print("MASTERCARD")
    elif Luhn and first_two // 10 == 4:
        print("VISA")
    else:
        print("INVALID")
        
def check(num):
    # start checksum as last digit
    checksum = num - (num // 10) * 10
    
    for i in range(1, card_length(num)):
        # get (i + 1)-th digit from the end
        digit = ((num % power(10, (i + 1))) - (num % power(10, i))) // power(10, i)
        
        # odd digit from end, add to checksum, otherwise add digits of double
        if  i % 2 == 0:
            checksum = checksum + digit
        else:
            # double and add digits inidividually
            digit = digit * 2
            checksum = checksum + (digit % 10) + (digit // 10)
    
    # check the checksum
    if checksum % 10 == 0:
        return True
    else:
        return False

def card_length(num):
    # get length by dividing by ten until num is gone and using a counter
    length = 0
    while True:
        num = num // 10
        length += 1
        if num < 1:
            break
    
    return length

def power(a, b):
    a2 = a;
    for i in range(1, b):
        a2 = a2 * a
    return a2

if __name__ == "__main__":
    main()