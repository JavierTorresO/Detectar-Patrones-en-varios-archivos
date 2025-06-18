//Código para correr pruebas y medir tiempos pruebas

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>

#include "../algoritmos/kmp.h"
#include "../utils/io.h"

void buscarPatrones(const std::string& texto, const std::vector<std::string>& nombresDoc, const std::vector<int>& cortes) {
    std::vector<std::string> patrones;
    std::string input;

    std::cout << "Ingrese patrones uno por linea (linea vacia para buscar) :\n";
    while (true) {
        std::getline(std::cin, input);
        if (input.empty()) break;
        patrones.push_back(input);
    }

    if (patrones.empty()) {
        std::cout << "No se ingresaron patrones. Volviendo al menu.\n";
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < patrones.size(); i++) {
        const std::string& patron = patrones[i];
        std::vector<int> ocurrencias = kmpSearch(texto, patron);

        std::cout << "\nPatron #" << (i + 1) << " \"" << patron << "\":\n";
        if (ocurrencias.empty()) {
            std::cout << "No encontrado en ningun documento.\n";
        } else {
            std::cout << "Encontrado en:\n";
            for (int pos : ocurrencias) {
                int docIndex = obtenerDocumento(pos, cortes);
                if (docIndex != -1 && docIndex <= nombresDoc.size()) {
                    std::cout << "   - " << nombresDoc[docIndex - 1] << "\n";
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "\nTiempo total de busqueda para " << patrones.size() << " patrones: "
              << duracion.count() << " ms\n";
}

int main() {
    std::vector<std::string> nombresDoc;
    std::vector<int> cortes;
    std::string textoTotal;
    std::string carpeta = "datos/documentos";

    // Cargar todos los documentos disponibles para mostrar y búsquedas iniciales
    nombresDoc.clear();
    cortes.clear();
    textoTotal = leerDocumentosDesdeCarpeta(carpeta, nombresDoc, cortes);

    while (true) {
        std::cout << "\n--- Menu ---\n";
        std::cout << "1. Buscar patrones en documentos\n";
        std::cout << "2. Concatenar documentos seleccionados\n";
        std::cout << "3. Salir\n";
        std::cout << "Ingrese opcion: ";

        std::string opcion;
        std::getline(std::cin, opcion);

        if (opcion == "1") {
            if (textoTotal.empty()) {
                std::cout << "No hay documentos cargados.\n";
            } else {
                buscarPatrones(textoTotal, nombresDoc, cortes);
            }
        } else if (opcion == "2") {
            if (nombresDoc.empty()) {
                std::cout << "No hay documentos para seleccionar.\n";
                continue;
            }

            std::cout << "Documentos disponibles:\n";
            for (int i = 0; i < nombresDoc.size(); i++) {
                std::cout << (i + 1) << ". " << nombresDoc[i] << "\n";
            }

            std::cout << "Ingrese los NUMEROS de documentos a concatenar (separados por espacios) : ";
            std::string line;
            std::getline(std::cin, line);
            std::istringstream iss(line);
            std::vector<int> indices;
            int num;
            while (iss >> num) {
                if (num >= 1 && num <= (int)nombresDoc.size()) {
                    indices.push_back(num - 1);
                }
            }

            if (indices.empty()) {
                std::cout << "No se seleccionaron documentos validos.\n";
                continue;
            }

            std::vector<std::string> docsSeleccionados;
            for (int idx : indices) {
                docsSeleccionados.push_back(nombresDoc[idx]);
            }

            cortes.clear();
            textoTotal = concatenarDocumentosSeleccionados(carpeta, docsSeleccionados, cortes);
            nombresDoc = docsSeleccionados;

            std::cout << "Documentos concatenados:\n";
            for (const auto& n : nombresDoc) {
                std::cout << "- " << n << "\n";
            }

            //Mostrar texto concatenado
            std::cout << "\nTexto concatenado con '$':\n";
            std::cout << textoTotal << "\n";

        } else if (opcion == "3") {
            std::cout << "Saliendo...\n";
            break;
        } else {
            std::cout << "Opcion invalida. Intente de nuevo.\n";
        }
    }

    return 0;
}



//como correr: g++ -std=c++17 comparador/main.cpp algoritmos/kmp.cpp utils/io.cpp -o kmp.exe
//luego: .\kmp.exe