#include "kmp.h"
#include <vector>
#include <string>

void buildLPS(const std::string &pattern, std::vector<int> &lps)
{
    int m = pattern.size();
    lps.assign(m, 0);
    int len = 0; // length of the previous longest prefix suffix
    int i = 1;   // the current index in pattern

    while (i < m)
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                // retrocedemos al valor previo del lps
                len = lps[len - 1];
            }
            else
            {
                // si no hay coincidencia, lps[i] es 0
                lps[i] = 0;
                i++;
            }
        }
    }
}

std::vector<int> kmpSearch(const std::string &text, const std::string &pattern)
{
    // casos triviales
    if (pattern.empty())
        return {};
    if (text.empty() || pattern.size() > text.size())
        return {};

    int n = (int)text.size();
    int m = (int)pattern.size();
    std::vector<int> lps;
    buildLPS(pattern, lps);

    std::vector<int> matches;
    int i = 0; // indice para texto
    int j = 0; // indice para patron

    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
            // si completamos el patron se registra la coincidencia
            if (j == m)
            {
                matches.push_back(i - m);
                j = lps[j - 1]; // retrocedemos al valor previo del lps
            }
        }
        else
        {
            if (j != 0)
            {
                // no coincide: retrocedemos j para evitar empezar de 0
                j = lps[j - 1];
            }
            else
            {
                // j==0 y no hay coincidencia, avanzamos i
                i++;
            }
        }
    }
    return matches;
}
