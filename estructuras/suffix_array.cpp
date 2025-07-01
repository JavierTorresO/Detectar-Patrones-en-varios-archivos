//Solucion estructurada

#include "suffix_array.h"
#include <algorithm>
#include <iostream>

// Construye el suffix array
std::vector<int> construirSuffixArray(const std::string& texto) {
    int n = texto.size();
    std::vector<int> sa(n), rank(n), tmp(n);

    // Paso 1: Suffixes iniciales por posición
    for (int i = 0; i < n; ++i) {
        sa[i] = i;
        rank[i] = texto[i];
    }

    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = (i + k < n) ? rank[i + k] : -1;
            int rj = (j + k < n) ? rank[j + k] : -1;
            return ri < rj;
        };
        std::sort(sa.begin(), sa.end(), cmp);

        tmp[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        }
        rank = tmp;
    }

    return sa;
}

// Se hace búsqueda binaria del patrón en el texto usando el suffix array
std::vector<int> buscarConSuffixArray(const std::string& texto,
                                      const std::string& patron,
                                      const std::vector<int>& sa) {
    std::vector<int> ocurrencias;
    int n = texto.size();
    int m = patron.size();

    int l = 0, r = n - 1;
    // Buscar la primera posición donde puede aparecer el patrón
    while (l <= r) {
        int mid = (l + r) / 2;
        std::string sufijo = texto.substr(sa[mid], std::min(m, n - sa[mid]));
        if (sufijo < patron)
            l = mid + 1;
        else
            r = mid - 1;
    }

    // Desde "l" buscamos todas las ocurrencias
    while (l < n) {
        std::string sufijo = texto.substr(sa[l], std::min(m, n - sa[l]));
        if (sufijo.substr(0, m) == patron)
            ocurrencias.push_back(sa[l]);
        else
            break;
        ++l;
    }

    return ocurrencias;
}