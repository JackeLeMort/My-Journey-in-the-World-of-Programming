#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int i[3];
    float f[6];   
    i[0] = get_int("Combien as tu d'UE ? ");
    for (i[1]=0; i[1]<i[0]; i[1]++)
    {
        i[2] = get_int("combien y a-t-il de matières dans l'UE %i ? ", i[1]+1);
        for (i[3]=0; i[3]<i[2]; i[3]++)
        {
            f[0] = get_float("quelle est la note de la matière %i ? ", i[3]+1);
            f[1] = get_float("quel est le coef de la matière %i ? ", i[3]+1);
            printf("%f ; %f\n", f[0], f[1]);
            f[3] += f[0]*f[1];
            printf("%f\n", f[0]);
            f[4] += f[1];
            printf("%f\n", f[4]);
        }
        f[5] += f[3] / f[4];
        f[6] += f[4];
    }
    printf("Ta moyenne générale est : %0.2f\n", f[5] / f[6]);
}