#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "utils/io.h"

#include "kmp.h"
//#include "boyer_moore.h"
//#include "rabin_karp.h"
//#include "automata.h"
//#include "suffix_array.h"

using HighResClock = std::chrono::high_resolution_clock;

// Ejecuta algoritmo sobre un texto concatenado de varios documentos y mide tiempos
void buscarPatrones(const std::string &texto,
                    const std::vector<std::string> &nombresDoc,
                    const std::vector<int> &cortes)
{
    std::cout << "Ingresa patrones (una línea c/u), luego Ctrl+D para buscar:\n";
    std::vector<std::string> patrones;
    std::string pat;
    while (std::getline(std::cin, pat))
    {
        if (!pat.empty())
            patrones.push_back(pat);
    }
    if (patrones.empty())
    {
        std::cerr << "No se ingresó ningún patrón.\n";
        return;
    }

    auto t0_total = HighResClock::now();
    for (const auto &p : patrones)
    {
        auto t0 = HighResClock::now();
        auto occs = kmpSearch(texto, p);
        //auto occs = boyerMooreSearch(texto, p);
        //auto occs = rabinKarpSearch(texto, p);
        //auto occs = automataSearch(texto, p);
        //auto occs = SUFFIX ARRAY SEARCH aun no implementada
        auto t1 = HighResClock::now();

        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();
        std::cout << "\nPatrón: \"" << p << "\" → "
                  << occs.size() << " ocurrencias en " << ms << " ms\n";

        for (int pos : occs)
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