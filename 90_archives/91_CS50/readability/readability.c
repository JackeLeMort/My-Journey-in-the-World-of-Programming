#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int find_grade(string text);

int main(void)
{
    string text = get_string("Text: ");
    int grade = find_grade(text);
    if (grade < 1) {printf("Before Grade 1");}
    if (grade >= 1 && grade <= 16) { printf("Grade %i", grade);}
    if (grade > 16) { printf("Grade 16+");}
    printf("\n");
}

int find_grade(string text)
{
    float words_number = 1;
    float letters_number = 0;
    float sentences_number = 0;
    for (int i=0; i <= strlen(text); i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z')) { letters_number += 1; }
        else if (text[i] == ' ') { words_number += 1; }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?') { sentences_number += 1; }
    }
//    printf ("%f ",0.0588 * (letters_number / words_number * 100) - 0.296 * (sentences_number / words_number * 100) - 15.8);
//    return (0.0588 * (letters_number / words_number * 100) - 0.296 * (sentences_number / words_number * 100) - 15.8);
    float L = letters_number / words_number * 100;
    printf("%f \n",L);
    float S = sentences_number/  words_number * 100;
    printf("%f \n",S);
    printf ("%f \n",0.0588 * L - 0.296 * S - 15.8);
    printf ("%f \n",round(0.0588 * L - 0.296 * S - 15.8));
    return round(0.0588 * L - 0.296 * S - 15.8);
}
