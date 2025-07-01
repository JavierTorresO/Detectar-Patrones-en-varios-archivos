#include "automata.h"
#include <vector>
#include <string>
#include <unordered_map>

const int ASCII_SIZE = 256;  // para ASCII extendido

// Construye la tabla de transiciones (estado × símbolo → estado)
std::vector<std::vector<int>> construirTabla(const std::string& pat) {
    int m = pat.size();
    std::vector<std::vector<int>> dfa(m + 1, std::vector<int>(ASCII_SIZE, 0));

    dfa[0][pat[0]] = 1;
    int x = 0;

    for (int i = 1; i < m; ++i) {
        for (int c = 0; c < ASCII_SIZE; ++c) {
            dfa[i][c] = dfa[x][c];  // copia la fila del estado anterior
        }
        dfa[i][pat[i]] = i + 1;
        x = dfa[x][pat[i]];
    }

    return dfa;
}

std::vector<int> automataSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> result;
    if (pattern.empty() || text.size() < pattern.size())
        return result;

    auto dfa = construirTabla(pattern);
    int m = pattern.size();
    int state = 0;

    for (int i = 0; i < (int)text.size(); ++i) {
        state = dfa[state][(unsigned char)text[i]];
        if (state == m) {
            result.push_back(i - m + 1);
        }
    }

    return result;
}
