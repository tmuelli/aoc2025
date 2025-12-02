#include <stdio.h>
#include <stdlib.h>

#define DIAL_MAX 99

#define LEFT 'L'
#define RIGHT 'R'

int main (int argc, char* argv[]) {
    int rcode = 1;
    FILE *pInput = NULL;
    char line[256];
    int dial = 50;
    int count = 0;

    pInput = fopen("./input/day1.txt", "r");

    if (pInput == NULL) {
        return 1;
    }

    while (fgets(line, sizeof(line), pInput)) {
        char* pValue = &line[1];
        int value = atoi(pValue);

        if (!value) {
            printf("error converting string to integer!\n");
            rcode = 0;
            break;
        }

        if (value >= (DIAL_MAX + 1)) {
            value = value % (DIAL_MAX + 1);
        }

        if (line[0] == LEFT) {
            if (dial - value < 0) {
                dial = DIAL_MAX + 1 - (value - dial);
            } else {
                dial -= value;
            }
        }

        if (line[0] == RIGHT) {
            if (dial + value > DIAL_MAX) {
                dial = value - (DIAL_MAX + 1 - dial);
            } else {
                dial += value;
            }
        }

        if (dial == 0) {
            count++;
        }
    }

    if (rcode) {
        printf("The password is: %d\n", count);
    } else {
        printf("Error occured!\n");
    }

    fclose(pInput);
    return 0;
}