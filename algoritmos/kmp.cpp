#include "kmp.h"

std::vector<int> buildLPS(const std::string& pattern) {
    int n = pattern.length();
    std::vector<int> lps(n, 0);
    int len = 0;

    for (int i = 1; i < n; ) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i++] = len;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else
                lps[i++] = 0;
        }
    }
    return lps;
}

std::vector<int> kmpSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> lps = buildLPS(pattern);
    std::vector<int> positions;
    int i = 0, j = 0;
    int n = text.length(), m = pattern.length();

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++, j++;
        }

        if (j == m) {
            positions.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }

    return positions;
}
