#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string encrypt(string txt, string key);
string string_to_digits(string str);
int is_duplicate(string str);

int main(int argc, string argv[])
{
    string key=argv[1];
    // Check that program was ran with one command-line argument
    if (argc!=2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check that key is 26 characters.
    if (strlen(key)!=26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Iterate over the provided argument to make sure all characters are Alphabetic
    for (int i=0, n=strlen(key); i<n; i++)
    {
        if (isalpha(key[i])==0)
        {
            printf("Key must contain alphabetic characters only.\n");
            return 1;
        }
    }
    // Check key does not contain duplicate letters. Case insensitive.
    if (is_duplicate(key)>=1)
    {
        printf("Key contains duplicate letters\n.");
        return 1;
    }
    key=string_to_digits(key);
    // Prompt user for plaintext
    string ptxt=get_string("plaintext: ");
    string ctxt=encrypt(ptxt,key);
    printf("ciphertext: %s\n",ptxt);
    return 0;
}

// Converts letters in Key to position in alphabet. ie A/a = 0, B/b = 1, C/c = 2 ...
string string_to_digits(string str)
{
    for (int i=0, n=strlen(str); i<n; i++)
    {
        if (isupper(str[i]))
        {
            str[i]=str[i]-65;
        }
        else
        {
            str[i]=str[i]-97;
        }
    }
    return str;
}

// Encrypts the plaintext
string encrypt(string txt, string key)
{
    for (int i=0, n=strlen(txt); i<n; i++)
    {
        int x;
        if (isalpha(txt[i]))
        {
            if (isupper(txt[i]))
            {
                x=txt[i]-65;        // Calcs the postition of txt[i] letter in the alphabet.
                txt[i]=key[x]+65;   // Encrypts the letter and converts to Uppercase ASCII
            }
            else
            {
                x=txt[i]-97;
                txt[i]=key[x]+97;   // Encrypts the letter and converts to Lowercase ASCII
            }
        }
    }
    return txt;
}

// Scans the input key for duplicat characters.
int is_duplicate(string str)
{
    int n=0;
    //Counts each character present in the string
    for (int i=0; i<strlen(str); i++)
    {
        for (int j=i+1; j<strlen(str); j++)
        {
            if (str[i] == str[j])
            {
                n++;
            }
        }
    }
    return n;
}