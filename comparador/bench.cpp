#include <iostream>
#include <chrono>
#include <vector>
#include <string>

// Incluimos todos los headers de los algoritmos y estructuras
#include "io.h"
#include "kmp.h"
#include "boyer_moore.h"
#include "rabin_karp.h"
#include "automata.h"
#include "suffix_array.h"

using HRClock = std::chrono::high_resolution_clock;

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
void runAutomata(const std::string &texto, const std::vector<std::string> &patrones)
{
    std::cout << "\n=== Automata Finito ===\n";
    for (const auto &p : patrones)
    {
        auto t0 = HRClock::now();
        auto occ = automataSearch(texto, p);
        auto t1 = HRClock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

        std::cout << "  \"" << p << "\": " << occ.size() << " ocurrencias en " << ms << " ms\n";
    }
}

// Estructura 1: Suffix Array
void runSuffixArray(const std::string &texto,
                    const std::vector<std::string> &patrones)
{
    std::cout << "\n=== Suffix Array ===\n";

    // Medir tiempo de construcción
    auto t0_build = HRClock::now();
    std::vector<int> suffixArray = construirSuffixArray(texto);
    auto t1_build = HRClock::now();
    auto build_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1_build - t0_build).count();
    std::cout << "\nTiempo construccion: " << build_ms << " ms\n";

    // Buscar cada patrón
    auto t0_total = HRClock::now();
    for (const auto &p : patrones)
    {
        auto t0 = HRClock::now();
        auto occs = buscarConSuffixArray(texto, p, suffixArray);
        auto t1 = HRClock::now();

        auto us = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "\nPatron: \"" << p << "\" contiene "
                  << occs.size() << " ocurrencias en " << us << " ms\n";

        for (int pos : occs)
        {
            std::cout << "  Posicion absoluta en texto: " << pos << "\n";
        }
    }

    auto t1_total = HRClock::now();
    auto total_us = std::chrono::duration_cast<std::chrono::milliseconds>(t1_total - t0_total).count();
    std::cout << "\nTiempo total (todos patrones): " << total_us << " ms\n";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
    runSuffixArray(texto, patrones);

    return 0;
}
