#include <stdio.h>
#include <vector>

#define ROW_COUNT 136
#define COL_COUNT 136
#define POSSIBLE_ACCESS_COUNT 4

int main (int argc, char* argv[]) {
    int rcode = 1;
    FILE *pInput = NULL;
    char line[256];
    int result = 0;
    std::vector<std::vector<int>> vMatrix;
    std::vector<std::pair<int, int>> vNeighbors = {
        {-1, -1}, {0, -1}, {1, -1},
        {-1, 0}, /*{0, 0},*/ {1, 0},
        {-1, 1}, {0, 1}, {1, 1}
    };

    // read acutal content
    pInput = fopen("./input/day4.txt", "r");
    if (pInput == NULL) {
        return -1;
    }

    if (pInput == NULL) {
        return -1;
    }

    // read file and fill matrix
    while (fgets(line, sizeof(line), pInput)) {
        std::vector<int> vRow(COL_COUNT, 0);
        for (char *ptr = line; ptr != NULL && *ptr != '\n' && *ptr != '\0'; ptr++) {
            if (*ptr == '@') {
                int pos = ptr - line;
                vRow[pos] = 1;
            }
        }
        vMatrix.push_back(vRow);
    }

    // calculate access count
    for (int i = 0; i < ROW_COUNT; i++) {
        for (int j = 0; j < COL_COUNT; j++) {
            if (vMatrix[i][j] == 0) {
                // not a paper
                continue;
            }

            int neighbor_count = 0;

            // count neighbor papers
            for (auto n : vNeighbors) {
                int nPosX = i + n.first;
                int nPosY = j + n.second;

                // check if neighbor pos is out of range
                if ((nPosX >= 0) && (nPosY >= 0) &&
                    (nPosX < ROW_COUNT) && (nPosY < COL_COUNT)) {
                        if (vMatrix[nPosX][nPosY] == 1) {
                            neighbor_count++;
                        }
                }
            }

            if (neighbor_count < POSSIBLE_ACCESS_COUNT) {
                result++;
            }
        }
    }

    printf("Result: %d\n", result);

    fclose(pInput);
    return 0;
}