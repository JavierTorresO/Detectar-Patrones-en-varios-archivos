//Funciones comunes (lectura, timer, estadísticas)

#include "io.h"
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

std::string leerDocumentosDesdeCarpeta(const std::string& carpeta, std::vector<std::string>& nombresDoc, std::vector<int>& cortes) {
    std::vector<std::pair<std::string, std::string>> archivosContenido;

    for (const auto& entry : fs::directory_iterator(carpeta)) {
        if (entry.path().extension() == ".txt") {
            std::ifstream file(entry.path());
            if (!file.is_open()) continue;

            std::string contenido((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            std::string nombreArchivo = entry.path().filename().string();

            archivosContenido.push_back({nombreArchivo, contenido});
        }
    }

    std::sort(archivosContenido.begin(), archivosContenido.end());

    std::string textoTotal;
    int acumulado = 0;
    nombresDoc.clear();
    cortes.clear();

    for (const auto& [nombre, contenido] : archivosContenido) {
        textoTotal += contenido + '$';
        acumulado = textoTotal.size();
        cortes.push_back(acumulado);
        nombresDoc.push_back(nombre);
    }

    return textoTotal;
}

std::string concatenarDocumentosSeleccionados(const std::string& carpeta,
                                             const std::vector<std::string>& docsSeleccionados,
                                             std::vector<int>& cortes) {
    std::string textoTotal;
    int acumulado = 0;
    cortes.clear();

    for (const auto& nombreArchivo : docsSeleccionados) {
        std::ifstream file(carpeta + "/" + nombreArchivo);
        if (!file.is_open()) continue;

        std::string contenido((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        textoTotal += contenido + '$';
        acumulado = textoTotal.size();
        cortes.push_back(acumulado);
    }
    return textoTotal;
}

int obtenerDocumento(int pos, const std::vector<int>& cortes) {
    for (int i = 0; i < cortes.size(); ++i) {
        if (pos < cortes[i]) {
            return i + 1;
        }
    }
    return -1;
}
