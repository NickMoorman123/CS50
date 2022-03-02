#include <stdio.h>
#include <cs50.h>

void tower(int h);
void multi_print(string s, int n);

int main(void)
{
    // ask user for desired height
    int height;
    do
    {
        height = get_int("What height of tower? ");
    }
    while (height < 1 || height > 8);
    
    // print tower
    tower(height);
}

// function for creating the towers
void tower(int h)
{
    for (int i = 1; i < h; i++)
    {
        // print most lines
        multi_print(" ", h - i);
        multi_print("#", i);
        printf("  ");
        multi_print("#", i);
        printf("\n");
    }
    
    // print last line
    multi_print("#", h);
    printf("  ");
    multi_print("#", h);
    printf("\n");
}

// prints the same string s, n times
void multi_print(string s, int n)
{
    for (int j = 0; j < n; j++)
    {
        printf("%s", s);
    }
}