#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include "kmp.h"
#include "utils/io.h" // asumo tienes funciones para leer carpetas y textos

using clock = std::chrono::high_resolution_clock;

// Ejecuta KMP sobre un texto concatenado de varios documentos y mide tiempos
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

    auto t0_total = clock::now();
    for (const auto &p : patrones)
    {
        auto t0 = clock::now();
        auto occs = kmpSearch(texto, p);
        auto t1 = clock::now();

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
    auto t1_total = clock::now();
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