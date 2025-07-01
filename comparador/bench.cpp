#include <iostream>
#include <chrono>
#include <vector>
#include <string>

// Incluimos todos los headers de los algoritmos y estructuras
#include "kmp.h"
#include "boyer_moore.h"
#include "rabin_karp.h"
#include "automata.h"
// #include "suffix_array.h"

using HRClock = std::chrono::high_resolution_clock;

// Funcion helper para leer docs igual que en main
extern std::string leerDocumentosDesdeCarpeta(
    const std::string &, std::vector<std::string> &, std::vector<int> &);

// Algoritmo 1: KMP        
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

// Algoritmo 3: Rabin-Karp
void runRabinKarp(const std::string &texto, const std::vector<std::string> &patrones)
{
    std::cout << "\n=== Rabin-Karp ===\n";
    for (const auto &p : patrones)
    {
        auto t0 = HRClock::now();
        auto occ = rabinKarpSearch(texto, p);
        auto t1 = HRClock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

        std::cout << "  \"" << p << "\": " << occ.size() << " ocurrencias en " << ms << " ms\n";
    }
}

// EXTRA: Algoritmo 4: DFA(Automata Finito Determinista)
void runAutomata(const std::string& texto, const std::vector<std::string>& patrones)
{
    std::cout << "\n=== Autómata Finito ===\n";
    for (const auto& p : patrones)
    {
        auto t0 = HRClock::now();
        auto occ = automataSearch(texto, p);
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

    // Definir patrones a leer de los archivos (Se dejan preestablecidos los patrones aquí)
    std::vector<std::string> patrones = {
        "bin", "datos", "busqueda", "criptograficas"};

    // Ejecutar cada algoritmo
    runKMP(texto, patrones);
    runBoyerMoore(texto, patrones);
    runRabinKarp(texto, patrones);
    runAutomata(texto, patrones);

    // Ejecutar la estructura
    // runSuffixArray(texto, patrones); 

    return 0;
}
