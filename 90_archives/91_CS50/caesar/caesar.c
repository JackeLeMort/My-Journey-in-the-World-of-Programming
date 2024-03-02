#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_key(char *key);
int cryptage_low(int key, int plaintext);
int cryptage_up(int key, int plaintext);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("T'as oublié la clé gogole\n");
        return 1;
    }
    else if (argc > 2)
    {
        printf("y a trop de trucs là\n");
        return 1;
    }

    int key = atoi(argv[1]);
    if (key < 1 || check_key(argv[1]) == 0)
    {
        printf("Usage: ./ceasar key\n");
        return 1;
    }

    string plaintext = get_string("plaintext:  ");
    char ciphertext[strlen(plaintext)];

    //   printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            ciphertext[i] = cryptage_low(key, plaintext[i]);
        }
        else if (plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            ciphertext[i] = cryptage_up(key, plaintext[i]);
        }
        else
        {
            ciphertext[i] = plaintext[i];
        }
        //        printf("%c", ciphertext[i]);
    }
    //    printf("\n");
    ciphertext[strlen(plaintext)] = '\0';
    printf("ciphertext: %s\n", ciphertext);
}

int check_key(char *key)
{
    for (int i = 0; i < strlen(key); i++)
    {
        if (key[i] >= 48 && key[i] <= 57) { return 0;}
    }
    return 1;
}

int cryptage_low(int key, int plaintext)
{
    int ciphertext = plaintext + key % 26;
    if (ciphertext > 122)
    {
        ciphertext -= 26;
    }
    return ciphertext;
}

int cryptage_up(int key, int plaintext)
{
    int ciphertext = plaintext + key % 26;
    if (ciphertext > 90)
    {
        ciphertext -= 26;
    }
    return ciphertext;
}
