#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

struct Range {
    long long start;
    long long end;
    bool toBeRemoved;
};

bool compareRange(const Range &a, const Range &b) {
    return a.start < b.start;
}

void printTestData(std::vector<Range> ranges) {
    printf("Ranges:\n");
    int i = 0;
    for (auto r : ranges) {
        // printf("%d: From %lld to %lld\n", i, r.start, r.end);
        printf("%lld - %lld\n", r.start, r.end);
        i++;
    }
    printf("\n");
}

int main (int argc, char* argv[]) {
    int rcode = 1;
    FILE *pInput = NULL;
    char line[256];
    long long result = 0;
    std::vector<Range> vRanges;
    std::vector<Range> vResult;

    // read acutal content
    pInput = fopen("./input/day5.txt", "r");
    if (pInput == NULL) {
        return -1;
    }

    if (pInput == NULL) {
        return -1;
    }

    // analyze input content
    while (fgets(line, sizeof(line), pInput)) {
        std::string sLine;
        sLine += line;
        if (line[0] == '\n') {
            break;
        }

        size_t delimIndex = sLine.find('-');
        size_t endIndex = sLine.find('\n');
        std::string sStart = sLine.substr(0, delimIndex);
        std::string sEnd = sLine.substr(delimIndex + 1, endIndex);

        vRanges.push_back(
            {
                strtoll(sStart.c_str(), NULL, 10),
                strtoll(sEnd.c_str(), NULL, 10),
                false
            }
        );
    }

    // printTestData(vRanges);
    std::sort(vRanges.begin(), vRanges.end(), compareRange);

    // summarize ranges and filter vector accordingly
    for (auto r : vRanges) {
        if (vResult.empty()) {
            // nothing to summarize
            vResult.push_back(r);
            continue;
        }

        Range *pStartContained = NULL;
        Range *pEndContained = NULL;
        for (auto &s : vResult) {
            if (s.toBeRemoved) { continue; }
            // check if start and end are contained in another range
            if (((s.start <= r.start) && (s.end >= r.start)) && ((s.start <= r.end) && (s.end >= r.end))) {
                pStartContained = &s;
                pEndContained = &s;
                break;
            }
            
            if ((s.start <= r.start) && (s.end >= r.start)) {
                pStartContained = &s;
                break;
            }

            if ((s.start <= r.end) && (s.end >= r.end)) {
                pEndContained = &s;
                break;
            }
        }

        // not in existing range
        if ((pStartContained == NULL) && (pEndContained == NULL)) {
            vResult.push_back(r);
            continue;
        }

        if (pStartContained == pEndContained) {
            // range is completly in existing range => nothing to do
            // already inside
            continue;
        }

        // begin is in existing range => extend existing range to new end
        if ((pStartContained != NULL) && (pEndContained == NULL)) {
            pStartContained->end = r.end;
            continue;
        }

        // end is in existing range => extend existing range to new start
        if ((pStartContained == NULL) && (pEndContained != NULL)) {
            pEndContained->start = r.start;
            continue;
        }
    }

    // printTestData(vResult);

    // calculate all ids
    for (auto r : vResult) {
        if (r.toBeRemoved) {
            continue;
        }

        long long add = r.end - r.start;
        if (add == 0) {
            result += 1;
            continue;
        }

        result += ((r.end - r.start) + 1);
    }

    printf("Result: %lld\n", result);

    fclose(pInput);
    return 0;
}