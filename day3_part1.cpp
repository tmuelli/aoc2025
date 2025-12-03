#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

struct Pair {
    int key;
    int value;
};

struct LinePair {
    Pair p;
    char first;
    char second;
};

bool combExists(std::vector<Pair> vCombs, Pair comb) {
    bool bHasComb = false;

    for (const Pair p : vCombs) {
        if (p.key == comb.key && p.value == comb.value) {
            bHasComb = true;
            break;
        }
    }

    return bHasComb;
}

bool keyExists(std::vector<LinePair> vValues, int key) {
    bool bHasKey = false;

    for (const LinePair pair : vValues) {
        if (pair.p.key == key) {
            bHasKey = true;
            break;
        }
    }

    return bHasKey;
}

int main (int argc, char* argv[]) {
    int rcode = 1;
    FILE *pInput = NULL;
    char line[256];
    int result = 0;
    std::vector<LinePair> vLineValues;
    std::vector<Pair> vCombinations;

    // read acutal content
    pInput = fopen("./input/day3.txt", "r");
    if (pInput == NULL) {
        return -1;
    }

    while (fgets(line, sizeof(line), pInput)) {
        vLineValues.clear();

        for (char *ptr = line; ptr != NULL && (*ptr != '\n' && *ptr != '\0'); ptr++) {
            vCombinations.clear();
            if (keyExists(vLineValues, *ptr)) {
                continue;
            }

            // find number combinations
            for (char *p = ptr + 1; p != NULL && (*p != '\n' && *p != '\0'); p++) {
                Pair comb = { *ptr, *p };
                if (combExists(vCombinations, comb)) {
                    continue;
                }

                vCombinations.push_back(comb);
            }

            int max_value = 0;
            char first, second;
            for (const Pair comb : vCombinations) {
                if ((comb.key + comb.value) > max_value) {
                    max_value = comb.key + comb.value;
                    first = comb.key;
                    second = comb.value;
                }
            }

            vLineValues.push_back({{ *ptr, max_value }, first, second});
        }

        int add = 0;
        char res[3];
        for (const LinePair pair : vLineValues) {
            res[0] = pair.first;
            res[1] = pair.second;
            res[2] = '\0';

            int value = atoi(res);
            if (value > add) {
                add = value;
            }
        }

        result += add;
    }

    printf("Result: %d\n", result);

    fclose(pInput);
    return 0;
}