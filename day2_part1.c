#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 4096 // enough for day2.txt content
#define RANGE_DELIM ','
#define NUM_DELIM '-'

bool analyzeRange(char *pStart, char *pEnd, long long *pResult) {
    bool bRcode = true;
    int tmp = 0;
    char *pNum1 = NULL, *pNum2 = NULL;
    size_t nSize1 = 0, nSize2 = 0;

    // extract both number strings and their size
    for (char *ptr = pStart; ptr != pEnd; ptr++) {
        if (*ptr == NUM_DELIM) {
            nSize1 = ptr - pStart;
            nSize2 = pEnd - (ptr + 1);
            break;
        }
    }

    // check for different part of number string
    pNum1 = (char*) calloc(1, nSize1 + 1);
    pNum2 = (char*) calloc(1, nSize2 + 1);

    // copy into number buffer
    memcpy(pNum1, pStart, nSize1);
    memcpy(pNum2, pStart + nSize1 + 1, nSize2);

    // convert to integers
    long long llNum1 = strtoll(pNum1, NULL, 10);
    long long llNum2 = strtoll(pNum2, NULL, 10);

    for (long long i = 0; i <= (llNum2 - llNum1); i++) {
        char num[200];
        _i64toa(llNum1 + i, num, 10);

        size_t len = strlen(num);
        if (len % 2 == 0) {
            bool invalid = true;
            for (int j = 0; j < (len / 2); j++) {
                if (num[j] != num[j + (len/2)]) {
                    invalid = false;
                }
            }

            if (invalid) {
                long long add = strtoll(num, NULL, 10);
                *pResult += add;
            }
        }
    }

    // clean up
    free (pNum1);
    free (pNum2);
    return bRcode;
}

int main (int argc, char* argv[]) {
    bool bRcode = true;
    FILE *pInput = NULL;
    char line[MAX_BUFFER_SIZE];
    long long result = 0;

    pInput = fopen("./input/day2.txt", "r");

    if (pInput == NULL) {
        return 1;
    }

    if (fgets(line, sizeof(line), pInput) == NULL) {
        return 1;
    }

    char *pStart = line;
    for (char *ptr = line; ptr != NULL && *ptr != '\0'; ptr++) {
        if (*(ptr+1) == RANGE_DELIM) {
            if (analyzeRange(pStart, ptr+1, &result)) {
                pStart = ptr + 2;
            } else {
                bRcode = false;
                break;
            }
        }

        if (*(ptr+1) == '\0') {
            if (analyzeRange(pStart, ptr+1, &result)) {
                pStart = ptr + 2;
            } else {
                bRcode = false;
            }
            break;
        }
    }

    printf("Result is: %lld\n", result);

    fclose(pInput);
    return bRcode ? 0 : 1;
}