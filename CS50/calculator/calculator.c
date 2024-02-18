#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x = get_int("x: ");
    int y = get_int("y: ");
    float z = (float) x / y;
    printf("%.50f\n", z);
}