#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <numeric>
#include <iomanip>

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

// Estructura para almacenar resultados experimentales
struct ExperimentResult
{
    std::string algoritmo;
    int num_documentos;
    int num_patrones;
    int tamaño_texto;
    double tiempo_promedio_ms;
    double desviacion_std_ms;
    size_t memoria_promedio_kb;
    int total_ocurrencias;
    int repeticiones;
};

// Funcion para obtener memoria en KB
size_t getMemoryKB()
{
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)))
    {
        return pmc.WorkingSetSize / 1024;
    }
#elif __linux__
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
#endif
    return 0;
}

// Funcion para generar patrones aleatorios a partir del texto
std::vector<std::string> generarPatrones(const std::string &texto, int num_patrones,
                                         double porcentaje_existentes = 0.7,
                                         int min_len = 3, int max_len = 10)
{
    std::vector<std::string> patrones;
    std::random_device rd;
    std::mt19937 gen(rd());

    int patrones_existentes = static_cast<int>(num_patrones * porcentaje_existentes);
    int patrones_no_existentes = num_patrones - patrones_existentes;

    // Generar patrones existentes (substrings del texto)
    std::uniform_int_distribution<> pos_dist(0, std::max(0, static_cast<int>(texto.size()) - max_len));
    std::uniform_int_distribution<> len_dist(min_len, max_len);

    for (int i = 0; i < patrones_existentes && !texto.empty(); ++i)
    {
        int pos = pos_dist(gen);
        int len = std::min(len_dist(gen), static_cast<int>(texto.size()) - pos);
        if (len > 0)
        {
            std::string patron = texto.substr(pos, len);
            // Evitar patrones muy cortos o que solo contengan espacios
            if (patron.size() >= min_len && patron.find_first_not_of(" \t\n\r") != std::string::npos)
            {
                patrones.push_back(patron);
            }
        }
    }

    // Generar patrones no existentes (aleatorios)
    std::uniform_int_distribution<> char_dist(97, 122); // a-z
    for (int i = 0; i < patrones_no_existentes; ++i)
    {
        int len = len_dist(gen);
        std::string patron;
        for (int j = 0; j < len; ++j)
        {
            patron += static_cast<char>(char_dist(gen));
        }
        // Agregar sufijo unico para asegurar que no existe
        patron += "xyz123";
        patrones.push_back(patron);
    }

    return patrones;
}

// Funcion para medir tiempo de ejecucion de un algoritmo
std::pair<double, size_t> medirAlgoritmo(const std::string &algoritmo,
                                         const std::string &texto,
                                         const std::vector<std::string> &patrones)
{
    size_t mem_inicial = getMemoryKB();
    auto inicio = HRClock::now();

    // Ejecutar el algoritmo correspondiente
    if (algoritmo == "KMP")
    {
        for (const auto &p : patrones)
        {
            kmpSearch(texto, p);
        }
    }
    else if (algoritmo == "Boyer-Moore")
    {
        for (const auto &p : patrones)
        {
            boyerMooreSearch(texto, p);
        }
    }
    else if (algoritmo == "Rabin-Karp")
    {
        for (const auto &p : patrones)
        {
            rabinKarpSearch(texto, p);
        }
    }
    else if (algoritmo == "Automata")
    {
        for (const auto &p : patrones)
        {
            automataSearch(texto, p);
        }
    }
    else if (algoritmo == "Suffix-Array")
    {
        auto suffixArray = construirSuffixArray(texto);
        for (const auto &p : patrones)
        {
            buscarConSuffixArray(texto, p, suffixArray);
        }
    }

    auto fin = HRClock::now();
    size_t mem_final = getMemoryKB();

    double tiempo_ms = std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio).count() / 1000.0;

    // Corregir calculo de memoria para evitar overflow
    size_t memoria_extra = 0;
    if (mem_final >= mem_inicial)
    {
        memoria_extra = mem_final - mem_inicial;
    }

    return {tiempo_ms, memoria_extra};
}

// Funcion para realizar experimento con repeticiones
ExperimentResult realizarExperimento(const std::string &algoritmo,
                                     const std::string &texto,
                                     const std::vector<std::string> &patrones,
                                     int num_documentos,
                                     int repeticiones = 20)
{
    std::vector<double> tiempos;
    std::vector<size_t> memorias;

    std::cout << "  Ejecutando " << algoritmo << " con " << patrones.size()
              << " patrones, " << repeticiones << " repeticiones..." << std::flush;

    for (int i = 0; i < repeticiones; ++i)
    {
        auto [tiempo, memoria] = medirAlgoritmo(algoritmo, texto, patrones);
        tiempos.push_back(tiempo);
        memorias.push_back(memoria);

        if ((i + 1) % 5 == 0)
        {
            std::cout << "." << std::flush;
        }
    }

    // Calcular estadisticas
    double tiempo_promedio = std::accumulate(tiempos.begin(), tiempos.end(), 0.0) / tiempos.size();
    double suma_cuadrados = 0.0;
    for (double t : tiempos)
    {
        suma_cuadrados += (t - tiempo_promedio) * (t - tiempo_promedio);
    }
    double desviacion_std = std::sqrt(suma_cuadrados / tiempos.size());

    size_t memoria_promedio = std::accumulate(memorias.begin(), memorias.end(), 0ULL) / memorias.size();

    // Contar ocurrencias totales (usando la primera medicion)
    int total_ocurrencias = 0;
    if (algoritmo == "KMP")
    {
        for (const auto &p : patrones)
        {
            total_ocurrencias += kmpSearch(texto, p).size();
        }
    }
    else if (algoritmo == "Boyer-Moore")
    {
        for (const auto &p : patrones)
        {
            total_ocurrencias += boyerMooreSearch(texto, p).size();
        }
    }
    else if (algoritmo == "Rabin-Karp")
    {
        for (const auto &p : patrones)
        {
            total_ocurrencias += rabinKarpSearch(texto, p).size();
        }
    }
    else if (algoritmo == "Automata")
    {
        for (const auto &p : patrones)
        {
            total_ocurrencias += automataSearch(texto, p).size();
        }
    }
    else if (algoritmo == "Suffix-Array")
    {
        auto suffixArray = construirSuffixArray(texto);
        for (const auto &p : patrones)
        {
            total_ocurrencias += buscarConSuffixArray(texto, p, suffixArray).size();
        }
    }

    std::cout << " Completado!\n";

    return {
        algoritmo,
        num_documentos,
        static_cast<int>(patrones.size()),
        static_cast<int>(texto.size()),
        tiempo_promedio,
        desviacion_std,
        memoria_promedio,
        total_ocurrencias,
        repeticiones};
}

// Funcion para exportar resultados a CSV
void exportarResultados(const std::vector<ExperimentResult> &resultados, const std::string &archivo)
{
    std::ofstream file(archivo);
    if (!file.is_open())
    {
        std::cerr << "Error: No se pudo crear el archivo " << archivo << std::endl;
        return;
    }

    // Cabecera CSV
    file << "Algoritmo,Num_Documentos,Num_Patrones,Tamaño_Texto,Tiempo_Promedio_ms,"
         << "Desviacion_Std_ms,Memoria_Promedio_KB,Total_Ocurrencias,Repeticiones\n";

    // Datos
    for (const auto &resultado : resultados)
    {
        file << std::fixed << std::setprecision(4)
             << resultado.algoritmo << ","
             << resultado.num_documentos << ","
             << resultado.num_patrones << ","
             << resultado.tamaño_texto << ","
             << resultado.tiempo_promedio_ms << ","
             << resultado.desviacion_std_ms << ","
             << resultado.memoria_promedio_kb << ","
             << resultado.total_ocurrencias << ","
             << resultado.repeticiones << "\n";
    }

    file.close();
    std::cout << "Resultados exportados a: " << archivo << std::endl;
}

// Funcion para mostrar resumen de resultados
void mostrarResumen(const std::vector<ExperimentResult> &resultados)
{
    std::cout << "\n=== RESUMEN DE RESULTADOS EXPERIMENTALES ===\n";
    std::cout << std::left << std::setw(15) << "Algoritmo"
              << std::setw(8) << "Docs"
              << std::setw(10) << "Patrones"
              << std::setw(12) << "Tamaño(KB)"
              << std::setw(12) << "Tiempo(ms)"
              << std::setw(10) << "Std(ms)"
              << std::setw(10) << "Mem(KB)"
              << std::setw(12) << "Ocurrencias" << std::endl;
    std::cout << std::string(95, '-') << std::endl;

    for (const auto &r : resultados)
    {
        std::cout << std::left << std::setw(15) << r.algoritmo
                  << std::setw(8) << r.num_documentos
                  << std::setw(10) << r.num_patrones
                  << std::setw(12) << (r.tamaño_texto / 1024)
                  << std::setw(12) << std::fixed << std::setprecision(2) << r.tiempo_promedio_ms
                  << std::setw(10) << std::fixed << std::setprecision(2) << r.desviacion_std_ms
                  << std::setw(10) << r.memoria_promedio_kb
                  << std::setw(12) << r.total_ocurrencias << std::endl;
    }
}

int main()
{
    std::cout << "=== ESTUDIO EXPERIMENTAL AUTOMATIZADO ===\n\n";

    // Cargar todos los documentos disponibles
    std::vector<std::string> nombres;
    std::vector<int> cortes;
    std::string texto_completo = leerDocumentosDesdeCarpeta("datos/documentos/", nombres, cortes);

    std::cout << "Documentos disponibles: " << nombres.size() << std::endl;
    std::cout << "Texto total: " << texto_completo.size() << " caracteres\n\n";

    // Configuracion del experimento
    std::vector<std::string> algoritmos = {"KMP", "Boyer-Moore", "Rabin-Karp", "Automata", "Suffix-Array"};
    std::vector<int> num_documentos_tests = {3, 5, 8, 10, 13}; // Usar diferentes cantidades de documentos
    std::vector<int> num_patrones_tests = {5, 10, 20, 30};     // Diferentes cantidades de patrones
    int repeticiones = 20;

    std::vector<ExperimentResult> todos_resultados;

    // Ejecutar experimentos
    for (int num_docs : num_documentos_tests)
    {
        if (num_docs > static_cast<int>(nombres.size()))
            continue;

        // Crear texto con los primeros num_docs documentos
        std::string texto_experimento;
        for (int i = 0; i < num_docs; ++i)
        {
            if (i < static_cast<int>(cortes.size()) - 1)
            {
                int inicio = (i == 0) ? 0 : cortes[i];
                int fin = cortes[i + 1];
                texto_experimento += texto_completo.substr(inicio, fin - inicio);
            }
        }

        std::cout << "\n--- Experimento con " << num_docs << " documentos ("
                  << texto_experimento.size() << " caracteres) ---\n";

        for (int num_patrones : num_patrones_tests)
        {
            std::cout << "\nGenerando " << num_patrones << " patrones...\n";
            auto patrones = generarPatrones(texto_experimento, num_patrones);

            for (const auto &algoritmo : algoritmos)
            {
                auto resultado = realizarExperimento(algoritmo, texto_experimento,
                                                     patrones, num_docs, repeticiones);
                todos_resultados.push_back(resultado);
            }
        }
    }

    // Mostrar resumen
    mostrarResumen(todos_resultados);

    // Exportar resultados
    exportarResultados(todos_resultados, "resultados_experimentales.csv");

    std::cout << "\n=== EXPERIMENTO COMPLETADO ===\n";
    std::cout << "Total de experimentos realizados: " << todos_resultados.size() << std::endl;

    return 0;
}
