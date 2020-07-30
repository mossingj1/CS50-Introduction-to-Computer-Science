#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
// Check that program was run with one command-line argument
    if (argc!=2)
    {
        printf("Usage: ./ceasar key.\nNo inputs or to many inouts. Onlt a single input is expected.\n");
        return 1;
    }

// Iterate over the provided argument to make sure all characters are digits
    for (int i=0, n=strlen(argv[1]); i<n; i++)
    {
        if (isdigit(argv[1][i])==0)
        {
            printf("Key is not a positive intiger\n");
            return 1;
        }
    }
// Convert command-line argument from a string to an int
    int key=atoi(argv[1]);


// Prompt user for plaintext
    string ptxt=get_string("plaintext: ");


// Encrypt plaintext
// If it is an uppercase letter, rotate it, preserving case, then print out the rotated character
    for (int i=0,n=strlen(ptxt);i<n;i++)
    {
        if (isalpha(ptxt[i]))
        {
            if (isupper(ptxt[i]))
            {
                ptxt[i]=(ptxt[i]+key-65)%26+65;
            }
            else
            {
                ptxt[i]=(ptxt[i]+key-97)%26+97;
            }
        }
    }
    printf("ciphertext: %s\n",ptxt);
}