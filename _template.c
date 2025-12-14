#include <stdio.h>

int main (int argc, char* argv[]) {
    int rcode = 1;
    FILE *pInput = NULL;
    char line[256];
    int result = 0;

    // read acutal content
    pInput = fopen("./input/day4_test.txt", "r");
    if (pInput == NULL) {
        return -1;
    }

    if (pInput == NULL) {
        return -1;
    }

    while (fgets(line, sizeof(line), pInput)) {
    }

    printf("Result: %d\n", result);

    fclose(pInput);
    return 0;
}