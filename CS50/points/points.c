#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int const MINE = 2;
    int points = get_int("How many points did you lose? ");

    if (points < MINE)
    {
        printf("You lost more point than me.\n");
    }
    else if (points > MINE)
    {
        printf("nul");
    }
    else
    {
        printf("same");
    }
}