#include <stdio.h>
#include <cs50.h>

bool check(long num);
int card_length(long num);
long power(int a, int b);

int main(void)
{
    // get card number from user, check for length
    long number;
    do
    {
        number = get_long("Credit card number: ");
    }
    while(number <= 999999999999 || (number >= 10000000000000 && number <= 99999999999999) || number >= 10000000000000000);
    
    // get first two to check provider
    int first_two = number / power(10, (card_length(number) - 2));
    
    // whether the card is valid by checksum
    bool Luhn = check(number);
    
    // if valid and a sensical pair of first numbers
    if (Luhn && (first_two == 34 || first_two == 37))
    {
        printf("AMEX\n");
    }
    else if (Luhn && first_two >= 51 && first_two <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if (Luhn && first_two / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// do checksum calculation
bool check(long num)
{
    // start checksum as last digit
    int checksum = num - (num / 10) * 10;
    
    for (int i = 1; i < card_length(num); i++)
    {
        // get (i + 1)-th digit from the end
        int digit = ((num % power(10, (i + 1))) - (num % power(10, i))) / power(10, i);
        
        // odd digit from end, add to checksum, otherwise add digits of double
        if  (i % 2 == 0)
        {
            checksum = checksum + digit;
        }
        else
        {
            // double and add digits inidividually
            digit = digit * 2;
            checksum = checksum + (digit % 10) + (digit / 10);
        }
    }
    
    // check the checksum
    if (checksum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// length to determine provider
int card_length(long num)
{
    // get length by dividing by ten until num is gone and using a counter
    int len = 0;
    do
    {
        num = num / 10;
        len++;
    }
    while (num > 0);
    
    return len;
}

// idk how else to do powers. only works for positive integers.
long power(int a, int b)
{
    long a2 = (long) a;
    for (int i = 1; i < b; i++)
    {
        a2 = a2 * (long) a;
    }
    return a2;
}