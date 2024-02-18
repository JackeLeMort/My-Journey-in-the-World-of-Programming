#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


int compare(int a, int b);

int main()
{
    int light_x;
    int light_y;
    int initial_tx;
    int initial_ty;
    scanf("%d%d%d%d", &light_x, &light_y, &initial_tx, &initial_ty);

    while (1) {
        int remaining_turns;
        scanf("%d", &remaining_turns);

        switch (compare (light_y, initial_ty)){
            case 1:
                initial_ty += 1;
                printf("S");
                break;

            case -1:
                initial_ty -= 1;
                printf("N");
                break;

            default:
                break;
        }
        switch (compare(light_x, initial_tx )){
            case 1:
                initial_tx += 1;
                printf("E\n");
                break;

            case -1:
                initial_tx -= 1;
                printf("W\n");
                break  ;

            case 0:
                printf("\n");
                break;

            default:
                break;
        }
    }
    return 0;
}

int compare(int a, int b){
    return (a > b) - (a < b);
}
