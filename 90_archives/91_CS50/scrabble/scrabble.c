#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int pl(string word);
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");
    if(pl(word1) > pl(word2)) {printf("Player 1 wins!");}
    else if(pl(word1) < pl(word2)) {printf("Player 2 wins!");}
    else if(pl(word1) == pl(word2)){printf("Tie!");}
    printf("\n");
}


int pl(string word)
{
    int sum = 0;
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        char c = toupper(word[i]);
        if((int)c >= 'A' && (int)c<='Z'){sum = sum + POINTS[c - 'A'];}
    }
    return sum;
}
