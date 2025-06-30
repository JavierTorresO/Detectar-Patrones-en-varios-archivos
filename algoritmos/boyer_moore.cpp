#include "boyer_moore.h"
#include <vector>
#include <algorithm>

void preprocessBadChar(const std::string &pattern, std::vector<int> &badChar) {
    badChar.assign(256, -1);
    for (int i = 0; i < (int)pattern.size(); ++i) {
        badChar[(unsigned char)pattern[i]] = i;
    }
}

std::vector<int> boyerMooreSearch(const std::string &text, const std::string &pattern) {
    std::vector<int> result;
    int n = text.size(), m = pattern.size();
    if (m == 0 || n < m) return result;

    std::vector<int> badChar;
    preprocessBadChar(pattern, badChar);

    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && pattern[j] == text[s + j]) j--;

        if (j < 0) {
            result.push_back(s);
            s += (s + m < n) ? m - badChar[(unsigned char)text[s + m]] : 1;
        } else {
            s += std::max(1, j - badChar[(unsigned char)text[s + j]]);
        }
    }
    return result;
}
