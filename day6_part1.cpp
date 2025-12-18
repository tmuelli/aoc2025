#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>

#define VALUE_LINE_COUNT 4

enum Operation {
    ADD,
    MULTIPLY
};

bool isDigit(char c) {
    return (c >= 48 && c <= 57) ? true : false;
}

int main (int argc, char* argv[]) {
    int rcode = 1;
    FILE *pInput = NULL;
    char line[4096];
    long long result = 0;
    std::vector<std::vector<long>> vProblems;
    std::vector<char> vOperations;

    // read acutal content
    pInput = fopen("./input/day6.txt", "r");
    if (pInput == NULL) {
        return -1;
    }

    if (pInput == NULL) {
        return -1;
    }

    int line_count = 0;
    while (fgets(line, sizeof(line), pInput)) {
        std::vector<long> vLineValues;
        vProblems.push_back(vLineValues);

        if (line_count < VALUE_LINE_COUNT) {
            // values line
            char *pStart = line;
            for (char *ptr = line; ptr != NULL && *ptr != '\0'; ptr++) {
                if (isDigit(*ptr)) {
                    if (*pStart == ' ') {
                        pStart = ptr;
                    }
                    continue;
                }

                if ((*ptr != ' ') && (*ptr != '\n')) {
                    printf("Error?");
                    break;
                }

                if (*pStart != ' ') {
                    size_t nNumLen = ptr - pStart;
                    char *pConv = (char*) calloc(1 ,nNumLen + 1);
                    strncpy (pConv, pStart, nNumLen);
                    long value = strtol(pConv, NULL, 10);

                    vProblems[line_count].push_back(value);

                    free (pConv);
                }

                pStart = ptr;
            }
        } else {
            // operation line
            for (char *ptr = line; ptr != NULL && *ptr != '\0'; ptr++) {
                if (*ptr == '\n') {
                    break;
                }

                if (*ptr == ' ') {
                    continue;
                }

                if ((*ptr == '*') || (*ptr == '+')) {
                    vOperations.push_back(*ptr);
                } else {
                    printf("Error operation: %c\n", *ptr);
                }
            }
        }

        line_count++;
    }

    size_t nOpSize = vOperations.size();
    size_t nProblemSize = 0;
    size_t nProblems = vProblems.size();
    // test purpose
    for (int i = 0; i < nProblems; i++) {
        if (nProblemSize == 0) {
            nProblemSize = vProblems[i].size();
            break;
        }

        if (nProblemSize != vProblems[i].size()) {
            printf("Error with size\n");
        }
    }

    size_t nValueSize = vProblems[0].size();
    for (int i = 0; i < nValueSize; i++) {
        long long value = 0;
        Operation op;

        if (vOperations[i] == '*') {
            op = MULTIPLY;
        } else if (vOperations[i] == '+') {
            op = ADD;
        }

        value = vProblems[0][i];

        for (int j = 1; j < nProblems - 1; j++) {
            if (op == MULTIPLY) {
                value *= vProblems[j][i];
            } else if (op == ADD) {
                value += vProblems[j][i];
            }
        }

        result += value;
    }

    printf("Result: %lld\n", result);

    fclose(pInput);
    return 0;
}