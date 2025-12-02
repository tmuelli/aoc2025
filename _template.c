#include <stdio.h>

int main (int argc, char* argv[]) {
    int rcode = 1;
    FILE *pInput = NULL;

    // pInput = fopen();

    if (pInput == NULL) {
        return -1;
    }

    fclose(pInput);
    return 0;
}