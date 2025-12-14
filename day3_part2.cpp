#include <stdio.h>
#include <string>
#include <vector>

#define JOLTAGE_LEN 12
#define LINE_LEN 100

int main (int argc, char* argv[]) {
    int rcode = 1;
    FILE *pInput = NULL;
    char line[256];
    long long result = 0;

    // read acutal content
    pInput = fopen("./input/day3.txt", "r");
    if (pInput == NULL) {
        return -1;
    }

    while (fgets(line, sizeof(line), pInput)) {
        long long max_value = 0;
        std::string value = "";

        char *ptr = line;
        int nLineLen = LINE_LEN;

        int tmp = (nLineLen - (JOLTAGE_LEN - value.length()) + 1);
        while (tmp > 1 && (value.length() != JOLTAGE_LEN)) {
            char max_digit = 0;
            int max_pos = 0;

            for (int i = 0; i < tmp; i++) {
                if (*(ptr + i) > max_digit) {
                    max_digit = *(ptr + i);
                    max_pos = i;
                }
            }

            value += max_digit;
            nLineLen -= max_pos + 1;
            ptr += (max_pos + 1);

            tmp = (nLineLen - (JOLTAGE_LEN - value.length()) + 1);
        }

        if (value.length() != JOLTAGE_LEN) {
            for (int i = 0; i < nLineLen; i++) {
                value += *(ptr + i);
            }
        }

        long long add = strtoll(value.c_str(), NULL, 10);
        result += add;
    }

    printf("Result: %lld\n", result);

    fclose(pInput);
    return 0;
}