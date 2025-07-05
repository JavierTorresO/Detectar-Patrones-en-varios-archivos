#include <iostream>
#include <chrono>
#include <vector>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#elif __linux__
#include <sys/resource.h>
#endif

// Incluimos todos los headers de los algoritmos y estructuras
#include "io.h"
#include "kmp.h"
#include "boyer_moore.h"
#include "rabin_karp.h"
#include "automata.h"
#include "suffix_array.h"

using HRClock = std::chrono::high_resolution_clock;

// Funcion simple para obtener memoria en KB
size_t getMemoryKB()
{
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
        return pmc.WorkingSetSize / 1024;
#elif __linux__
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
#endif
    return 0;
}

// Algoritmo 1: KMP
void runKMP(const std::string &texto, const std::vector<std::string> &patrones)
{
    std::cout << "\n=== KMP ===\n";
    size_t mem_inicial = getMemoryKB();
    auto t0_total = HRClock::now();

    for (size_t i = 0; i < patrones.size(); ++i)
    {
        const auto &p = patrones[i];
        size_t mem_ini_p = getMemoryKB();
        auto t0 = HRClock::now();
        auto occ = kmpSearch(texto, p);
        auto t1 = HRClock::now();
        size_t mem_fin_p = getMemoryKB();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "  \"" << p << "\": " << occ.size() << " ocurrencias en " << ms << " ms";
        if (i == 0)
            std::cout << ", Memoria estimada: " << (mem_fin_p - mem_ini_p) << " KB";
        std::cout << "\n";
    }

    auto t1_total = HRClock::now();
    size_t mem_final = getMemoryKB();
    auto total_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1_total - t0_total).count();
    std::cout << "  Tiempo total: " << total_ms << " ms, Memoria total: " << (mem_final - mem_inicial) << " KB\n";
}

// Algoritmo 2: Boyer-Moore
void runBoyerMoore(const std::string &texto, const std::vector<std::string> &patrones)
{
    std::cout << "\n=== Boyer-Moore ===\n";
    size_t mem_inicial = getMemoryKB();
    auto t0_total = HRClock::now();

    for (size_t i = 0; i < patrones.size(); ++i)
    {
        const auto &p = patrones[i];
        size_t mem_ini_p = getMemoryKB();
        auto t0 = HRClock::now();
        auto occ = boyerMooreSearch(texto, p);
        auto t1 = HRClock::now();
        size_t mem_fin_p = getMemoryKB();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "  \"" << p << "\": " << occ.size() << " ocurrencias en " << ms << " ms";
        if (i == 0)
            std::cout << ", Memoria estimada: " << (mem_fin_p - mem_ini_p) << " KB";
        std::cout << "\n";
    }

    auto t1_total = HRClock::now();
    size_t mem_final = getMemoryKB();
    auto total_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1_total - t0_total).count();
    std::cout << "  Tiempo total: " << total_ms << " ms, Memoria total: " << (mem_final - mem_inicial) << " KB\n";
}

// Algoritmo 3: Rabin-Karp
void runRabinKarp(const std::string &texto, const std::vector<std::string> &patrones)
{
    std::cout << "\n=== Rabin-Karp ===\n";
    size_t mem_inicial = getMemoryKB();
    auto t0_total = HRClock::now();

    for (size_t i = 0; i < patrones.size(); ++i)
    {
        const auto &p = patrones[i];
        size_t mem_ini_p = getMemoryKB();
        auto t0 = HRClock::now();
        auto occ = rabinKarpSearch(texto, p);
        auto t1 = HRClock::now();
        size_t mem_fin_p = getMemoryKB();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "  \"" << p << "\": " << occ.size() << " ocurrencias en " << ms << " ms";
        if (i == 0)
            std::cout << ", Memoria estimada: " << (mem_fin_p - mem_ini_p) << " KB";
        std::cout << "\n";
    }

    auto t1_total = HRClock::now();
    size_t mem_final = getMemoryKB();
    auto total_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1_total - t0_total).count();
    std::cout << "  Tiempo total: " << total_ms << " ms, Memoria total: " << (mem_final - mem_inicial) << " KB\n";
}

// EXTRA: Algoritmo 4: DFA(Automata Finito Determinista)
void runAutomata(const std::string &texto, const std::vector<std::string> &patrones)
{
    std::cout << "\n=== Automata Finito ===\n";
    size_t mem_inicial = getMemoryKB();
    auto t0_total = HRClock::now();

    for (size_t i = 0; i < patrones.size(); ++i)
    {
        const auto &p = patrones[i];
        size_t mem_ini_p = getMemoryKB();
        auto t0 = HRClock::now();
        auto occ = automataSearch(texto, p);
        auto t1 = HRClock::now();
        size_t mem_fin_p = getMemoryKB();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "  \"" << p << "\": " << occ.size() << " ocurrencias en " << ms << " ms";
        if (i == 0)
            std::cout << ", Memoria estimada: " << (mem_fin_p - mem_ini_p) << " KB";
        std::cout << "\n";
    }

    auto t1_total = HRClock::now();
    size_t mem_final = getMemoryKB();
    auto total_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1_total - t0_total).count();
    std::cout << "  Tiempo total: " << total_ms << " ms, Memoria total: " << (mem_final - mem_inicial) << " KB\n";
}

// Estructura 1: Suffix Array
void runSuffixArray(const std::string &texto, const std::vector<std::string> &patrones)
{
    std::cout << "\n=== Suffix Array ===\n";
    size_t mem_inicial = getMemoryKB();

    auto t0_build = HRClock::now();
    std::vector<int> suffixArray = construirSuffixArray(texto);
    auto t1_build = HRClock::now();
    size_t mem_despues_construccion = getMemoryKB();
    auto build_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1_build - t0_build).count();
    size_t mem_estructura = mem_despues_construccion - mem_inicial;

    std::cout << "  Tiempo construccion: " << build_ms << " ms\n";
    std::cout << "  Memoria estructura: " << mem_estructura << " KB\n";

    auto t0_busqueda = HRClock::now();
    for (const auto &p : patrones)
    {
        auto t0 = HRClock::now();
        auto occs = buscarConSuffixArray(texto, p, suffixArray);
        auto t1 = HRClock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "  \"" << p << "\": " << occs.size() << " ocurrencias en " << ms << " ms\n";
    }
    auto t1_busqueda = HRClock::now();

    size_t mem_final = getMemoryKB();
    auto total_busqueda_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1_busqueda - t0_busqueda).count();
    std::cout << "  Tiempo busqueda total: " << total_busqueda_ms << " ms\n";
    std::cout << "  Memoria total: " << (mem_final - mem_inicial) << " KB\n";
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    // Preparar datos de prueba
    std::vector<std::string> nombres;
    std::vector<int> cortes;
    std::string texto = leerDocumentosDesdeCarpeta("datos/documentos/", nombres, cortes);

    std::cout << "Texto cargado: " << texto.size() << " caracteres, " << nombres.size() << " documentos\n";

    // Definir patrones a leer de los archivos 
    std::vector<std::string> patrones = cargarPatronesDesdeArchivo("datos/patrones/patrones_50.txt");

    // Ejecutar cada algoritmo
    runKMP(texto, patrones);
    runBoyerMoore(texto, patrones);
    runRabinKarp(texto, patrones);
    runAutomata(texto, patrones);

    // Ejecutar la estructura
    runSuffixArray(texto, patrones);

    return 0;
}
