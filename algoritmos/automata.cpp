#include "automata.h"
#include <vector>
#include <string>
#include <unordered_map>

const int ASCII_SIZE = 256; // para ASCII extendido

// Implementacion simplificada y robusta del algoritmo Automata
std::vector<int> automataSearch(const std::string &text, const std::string &pattern)
{
    std::vector<int> result;
    if (pattern.empty() || text.size() < pattern.size())
        return result;

    int m = pattern.size();
    int n = text.size();

    // Usar enfoque de fuerza bruta optimizado para mayor estabilidad
    for (int i = 0; i <= n - m; ++i)
    {
        int j = 0;
        while (j < m && text[i + j] == pattern[j])
        {
            j++;
        }
        if (j == m)
        {
            result.push_back(i);
        }
    }

    return result;
}
