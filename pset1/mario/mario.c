#include <stdio.h>
#include <cs50.h>

void print_space(int i, int h);
void print_hash(int i);
int get_positive_int(string prompt);

int main(void)
{
    int h = get_positive_int("Height: ");
    for (int i=1; i<=h; i++)
    {
        print_space(i,h);
        print_hash(i);
        printf("  ");
        print_hash(i);
//        print_space(i,h);
        printf("\n");
    }

}

// Prompt user for positive integer
int get_positive_int(string prompt)
{
    int n;
    do
    {
        n = get_int("%s", prompt);
    }
    while (n < 1 || n > 8);
    return n;
}


// Funciton to calc. spaces for row i. Only calcs number of spaces per L/R side.
void print_space(int i, int h)
{
    for (int j=0; j<h-i; j++)
    {
        printf(" ");
    }
}

// Funciton to calc. ## for row i. Only calcs number of spaces per L/Rside.
void print_hash(int i)
{
    for (int j=0; j<i; j++)
    {
        printf("#");
    }
}
