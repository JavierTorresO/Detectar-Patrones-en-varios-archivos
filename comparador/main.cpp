#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "io.h"

#include "kmp.h"
#include "boyer_moore.h"
#include "rabin_karp.h"
#include "automata.h"
#include "suffix_array.h"

using HighResClock = std::chrono::high_resolution_clock;

// Ejecuta algoritmo sobre un texto concatenado de varios documentos y mide tiempos
void buscarPatrones(const std::string &texto,
                    const std::vector<std::string> &nombresDoc,
                    const std::vector<int> &cortes)
{
    std::cout << "Ingresa patrones (una linea c/u), luego Ctrl+D para buscar:\n";
    std::vector<std::string> patrones;
    std::string pat;
    while (std::getline(std::cin, pat))
    {
        if (!pat.empty())
            patrones.push_back(pat);
    }
    if (patrones.empty())
    {
        std::cerr << "No se ingresó ningun patron.\n";
        return;
    }

    // Construir suffix array una vez
    std::vector<int> suffixArray = construirSuffixArray(texto);

    auto t0_total = HighResClock::now();
    for (const auto &p : patrones)
    {
        std::cout << "\n=== Patron: \"" << p << "\" ===\n";

        // KMP
        auto t0 = HighResClock::now();
        auto occs_kmp = kmpSearch(texto, p);
        auto t1 = HighResClock::now();
        auto ms_kmp = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "KMP: " << occs_kmp.size() << " ocurrencias en " << ms_kmp << " ms\n";

        // Boyer-Moore
        t0 = HighResClock::now();
        auto occs_bm = boyerMooreSearch(texto, p);
        t1 = HighResClock::now();
        auto ms_bm = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "Boyer-Moore: " << occs_bm.size() << " ocurrencias en " << ms_bm << " ms\n";

        // Rabin-Karp
        t0 = HighResClock::now();
        auto occs_rk = rabinKarpSearch(texto, p);
        t1 = HighResClock::now();
        auto ms_rk = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "Rabin-Karp: " << occs_rk.size() << " ocurrencias en " << ms_rk << " ms\n";

        // Autómata
        t0 = HighResClock::now();
        auto occs_auto = automataSearch(texto, p);
        t1 = HighResClock::now();
        auto ms_auto = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "Autómata: " << occs_auto.size() << " ocurrencias en " << ms_auto << " ms\n";

        // Suffix Array
        t0 = HighResClock::now();
        auto occs_sa = buscarConSuffixArray(texto, p, suffixArray);
        t1 = HighResClock::now();
        auto ms_sa = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "Suffix Array: " << occs_sa.size() << " ocurrencias en " << ms_sa << " ms\n";

        // Mostrar posiciones usando KMP como referencia
        for (int pos : occs_kmp)
        {
            int docId = obtenerDocumento(pos, cortes);
            int offset = (docId == 1 ? pos : pos - cortes[docId - 2]);
            std::cout << "  • Doc " << docId
                      << " (“" << nombresDoc[docId - 1] << "”) @ pos "
                      << offset << "\n";
        }
    }
    auto t1_total = HighResClock::now();
    auto total_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1_total - t0_total).count();
    std::cout << "\nTiempo total (todos patrones): " << total_ms << " ms\n";
}

int main(int argc, char *argv[])
{
    // Leer lista de archivos y concatenarlos
    std::vector<std::string> nombresDoc;
    std::vector<int> cortes;

    // Se lee y concatenan los .txt
    std::string texto = leerDocumentosDesdeCarpeta("datos/documentos/", nombresDoc, cortes);

    // Lanzar búsquedas
    buscarPatrones(texto, nombresDoc, cortes);
    return 0;
}