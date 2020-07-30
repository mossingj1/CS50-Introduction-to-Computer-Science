// Function to check if a credit card number is (syntactically) valid
// AMEX: 15 digit cc numbers. Number starts with 34 or 37
// VISA: 13 or 16 digit cc numbers. Number starts with 4
// MASTERCARD: 16 digit cc numbers. Number starts with 51,52,53,54,or 55

#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>

long checksum1(long n,int l);
int check_num(long n,int l);
void print_ans(long x,long n,int l,int y);

int main(void)
{
    long x=0;
    int y=0;
    long n=get_long("Number: ");
    int l = floor(log10(n)) + 1;    //Computes length of n
    x = checksum1(n,l);
    y = check_num(n,l);
    // printf("L = %i Sum = %li First Dig = %i\n",l,x,y);
    print_ans(x,n,l,y);
}

// Calcs the sum of even number digits (after x2) + sum of odd number digits.
// Also records the first two digits (to be used as input for the print_ans function)
long checksum1(long n,int l)
{
    long x=0;
    for (int i=1;i<=l;i++)
    {
        long r=n%10;     //Gets last didig (r)
        long z=2*r;
        n=(n-r)/10;     //Removes last digit so that next loop last digit will indix
        if (i%2==0)     //If ditig position is even. Based on if the loop cycle is even
        {
            if(z>=10)   //Function needs to sum digits post multiplication. If the digit (r) is >=5, then will be a two digit number after multiplying by 2. Need to seperate any number >= 10 into seperate digits.
            {
                long a=z%10;
                long b=(z-a)/10;
                z=a+b;
            }
            x=x+z;
        }
        else
        {
            x=x+r;
        }
    }
    return x;
}

// Gets the first two digits of the cc # (to be used as input for the print_ans function)
int check_num(long n,int l)
{
    int y1=0;
    int y2=0;
    int y;
    for (int i=1;i<=l;i++)
    {
        long r=n%10;     //Gets last didig (r)
        n=(n-r)/10;     //Removes last digit so that next loop last digit will indix
        if (l-i==2)     //Records first two digits for later use
        {
            y1=n;
        }
        if (l-i==1)     //Records first digit (Single) for later use
        {
            y2=n;
        }
    }
    if (y2==4)
    {
        y=y2;
    }
    else
    {
        y=y1;
    }
    return y;
}

void print_ans(long x,long n,int l,int y)
{
    x = x%10;
    string a = "INVALID\n";
    if (l==13 || l==15 || l==16)    //Check CC# Length
    {
        if (x==0)                 // Special check
        {
            if (y==34 || y==37)     //AMEX
            {
                a="AMEX\n";
            }
            if (y==4)               //VISA
            {
                a="VISA\n";
            }
            if (y>=51 && y<=55)     //MASETERCARD
            {
                a="MASTERCARD\n";
            }

        }
        else
        {
            a="INVALID\n";
        }
    }
    printf("%s",a);
}

