#include <stdio.h>
#include <vector>
#include <string>

struct Range {
    long long start;
    long long end;
};

struct Id {
    long long id;
    bool checked;
};

void printTestData(std::vector<Range> ranges, std::vector<Id> ids) {
    printf("Ranges:\n");
    for (auto r : ranges) {
        printf("From %lld to %lld\n", r.start, r.end);
    }
    printf("\n");

    printf("Ids:\n");
    for (auto id : ids) {
        printf("%lld\n", id.id);
    }
    printf("\n");
}

int main (int argc, char* argv[]) {
    int rcode = 1;
    FILE *pInput = NULL;
    char line[256];
    int result = 0;
    std::vector<Range> vRanges;
    std::vector<Id> vIds;

    // read acutal content
    pInput = fopen("./input/day5.txt", "r");
    if (pInput == NULL) {
        return -1;
    }

    if (pInput == NULL) {
        return -1;
    }

    // analyze input content
    bool bDidReadRanges = false;
    while (fgets(line, sizeof(line), pInput)) {
        std::string sLine;
        sLine += line;
        if (line[0] == '\n') {
            bDidReadRanges = true;
            continue;
        }

        if (!bDidReadRanges) {
            size_t delimIndex = sLine.find('-');
            size_t endIndex = sLine.find('\n');
            std::string sStart = sLine.substr(0, delimIndex);
            std::string sEnd = sLine.substr(delimIndex + 1, endIndex);

            vRanges.push_back(
                {
                    strtoll(sStart.c_str(), NULL, 10),
                    strtoll(sEnd.c_str(), NULL, 10)
                }
            );
        } else {
            vIds.push_back({strtoll(sLine.c_str(), NULL, 10), false});
        }
    }

    // printTestData(vRanges, vIds);

    for (auto id : vIds) {
        for (auto r : vRanges) {
            if (id.checked) {
                // already found range where id is in => do not check further
                continue;
            }

            if ((id.id >= r.start) && (id.id <= r.end)) {
                id.checked = true;
                result++;
            }
        }
    }

    printf("Result: %d\n", result);

    fclose(pInput);
    return 0;
}