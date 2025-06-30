#include <iostream>
#include <chrono>
#include <vector>
#include <string>

// Incluimos todos los headers de los algoritmos y estructuras
#include "kmp.h"
#include "boyer_moore.h"
// #include "robin_karp.h"
// #include "suffix_array.h"

using HRClock = std::chrono::high_resolution_clock;

// Funcion helper para leer docs igual que en main
extern std::string leerDocumentosDesdeCarpeta(
    const std::string &, std::vector<std::string> &, std::vector<int> &);

//Algoritmo 1: KMP        
void runKMP(const std::string &texto, const std::vector<std::string> &patrones)
{
    std::cout << "=== KMP ===\n";
    for (auto &p : patrones)
    {
        auto t0 = HRClock::now();
        auto occ = kmpSearch(texto, p);
        auto t1 = HRClock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "  \"" << p << "\": " << occ.size() << " en " << ms << " ms\n";
    }
}

// Algoritmo 2: Boyer-Moore
void runBoyerMoore(const std::string &texto, const std::vector<std::string> &patrones)
{
    std::cout << "\n=== Boyer-Moore ===\n";
    for (const auto &p : patrones)
    {
        auto t0 = HRClock::now();
        auto occ = boyerMooreSearch(texto, p);
        auto t1 = HRClock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "  \"" << p << "\": " << occ.size() << " ocurrencias en " << ms << " ms\n";
    }
}

int main()
{
    // Preparar datos de prueba
    std::vector<std::string> nombres;
    std::vector<int> cortes;
    std::string texto = leerDocumentosDesdeCarpeta("datos/documentos/", nombres, cortes);

    // Definir patrones de prueba (o leer de un archivo)
    std::vector<std::string> patrones = {
        "bin", "datos", "busqueda", "criptograficas"};

    // Ejecutar cada algoritmo
    runKMP(texto, patrones);
    runBoyerMoore(texto, patrones);
    // runRobinKarp(texto, patrones);
    // runSuffixArray(texto, patrones);

    return 0;
}
