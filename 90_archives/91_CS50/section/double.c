#include <cs50.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int size = 5;
    int incr[size];
    incr[0] = 1;
    printf("%i\n",incr[0]);
    for (int i = 1; i<1; i++)
    {
        incr[i] = incr[i-1] * 2;
        printf("%i\n", incr[i]);
    }
}
