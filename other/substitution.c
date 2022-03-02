#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 2;
    }
    
    string key = argv[1];
    
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        key[i] = toupper(key[i]);
    }
    
    string text = get_string("plaintext: ");
    
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            text[i] = key[text[i] - 'A'];
        }
        else if (text[i] >= 'a' && text[i] <= 'z')
        {
            text[i] = tolower(key[text[i] - 'a']);
        }
    }
    
    printf("ciphertext: %s\n", text);
}