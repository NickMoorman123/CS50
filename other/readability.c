#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string paragraph = get_string("Text: ");
    int num_lett = 0;
    int num_word = 1;
    int num_sen = 0;
    int trail_space = 0;

    for (int i = strlen(paragraph) - 1; paragraph[i] == ' '; i--)
    {
        trail_space++;
    }

    for (int i = 0, n = strlen(paragraph); i < n - trail_space; i++)
    {
        if ((paragraph[i] >= 'a' && paragraph[i] <= 'z') || (paragraph[i] >= 'A' && paragraph[i] <= 'Z'))
        {
            num_lett++;
        }
        else if (paragraph[i] == ' ')
        {
            num_word++;
        }
        else if (paragraph[i] == '.' || paragraph[i] == '!' || paragraph[i] == '\?')
        {
            num_sen++;
        }
    }

    int grade = (int) (5.88 * ((float) num_lett / (float) num_word) - 29.6 * ((float) num_sen / (float) num_word) - 15.3);


    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}