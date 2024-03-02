#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

char key[26];

int main(int argc, char **argv)
{
    if (argc != 2) {printf("Usage: ./substition key\n"); return 1;}
    if (strlen(argv[1]) != 26) { printf("Il faut 26 lettres.\n");  return 1;}

    for (int i=0; i<26; i++)
    {
        if (isalpha(argv[1][i])==0) { printf("Utilez des characteres alphabetiques.\n"); return 1;}
        key[i] = toupper(argv[1][i]);
        printf("%i : %i\n", i, key[i]);
    }
    for (int i = 0; i<26; i++)
    {
        for (int j=i+1; j<26; j++)
        {
            if (key[i] == key[j]) { printf("All letters must be present, you cannot have \"%c\" twice.\n", key[i]); return 1;}
        }
    }
    char* plaintext = get_string("plaintext: ");

    char ciphertext[strlen(plaintext)];
    for (int i=0; i<strlen(plaintext); i++)
    {
        if (islower(plaintext[i])!=0) {
            ciphertext[i] = tolower(key[plaintext[i]-97]);}
        else if (isupper(plaintext[i])!=0) {
            ciphertext[i] = toupper(key[plaintext[i]-65]);}
        else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
    printf("ciphertext: %s\n", ciphertext);
}
