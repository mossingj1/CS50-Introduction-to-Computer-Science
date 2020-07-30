#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int count_letters(string input);
int count_words(string s);
int count_sentances(string s);

int main(void)
{
    string text = get_string("Text: ");
    int l=count_letters(text);
    int w=count_words(text);
    int s=count_sentances(text);
    float l100=(float)l*100/w;                  // Average number of letters per 100 words
    float s100=(float)s*100/w;                  // Average number of sentances per 100 words
    float index=0.0588*l100-0.296*s100-15.8;    // Coleman-Liau Index
    int level=round(index);                     // Rounds index to nearest integer
    if (level<1)
    {
        printf("Before Grade 1\n");
    }
    else if (level>=16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n",level);
    }

// Uncomment below lines for debugging purposes
    // printf("\nLetters = %i\n",l);
    // printf("Sentances = %i\n",s);
    // printf("Words = %i\n",w);
    // printf("Avg Letters per 100 Words= %f\n",l100);
    // printf("Avg Sentances per 100 Words= %f\n",s100);
}

// Counts the number (n) of Letters in the text input.
int count_letters(string s)
{
    int n=0;
    for (int i=0,l=strlen(s); i<l+1; i++)
    {
        int z=isalpha(s[i]);
        if (isalpha(s[i])!=0)
        {
            n++;
        }
    }
    return n;
}

// Counts the number (n) of Words in the text input.
// Counts the number of spaces. Since last word will not have a following space
// return value is n+1, not n
int count_words(string s)
{
    int n=0;
    for (int i=0,l=strlen(s); i<l+1; i++)
    {
        if (s[i]==' ')
        {
            n++;
        }
    }
    return n+1;
}

// Counts the number (n) of Sentances in the text input.
// Counts the number of . ! and ?
int count_sentances(string s)
{
    int n=0;
    for (int i=0,l=strlen(s); i<l+1; i++)
    {
        if (s[i]=='.' || s[i]=='!' || s[i]=='?')
        {
            n++;
        }
    }
    return n;
}

