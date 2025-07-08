# Sistema de Búsqueda de Patrones en Documentos

Un sistema completo de comparación de algoritmos de búsqueda de patrones en múltiples documentos de texto, diseñado para estudios experimentales y análisis de rendimiento.

## Características Principales

- **5 Algoritmos de Búsqueda**: KMP, Boyer-Moore, Rabin-Karp, Autómata Finito, Suffix Array
- **Sistema Experimental Automatizado**: Variación automática de documentos y patrones
- **Medición Precisa**: Tiempo de ejecución y uso de memoria con estadísticas
- **Exportación de Datos**: Resultados en formato CSV para análisis posterior
- **Carga de Patrones desde Archivos**: Patrones predefinidos desde archivos TXT para resultados reproducibles
- **Múltiples Repeticiones**: 20 ejecuciones por experimento para resultados confiables

## Estructura del Proyecto

```
Detectar-Patrones-en-varios-archivos/
├── comparador/
│   ├── main.cpp              ← Modo interactivo (usuario ingresa patrones)
│   ├── bench.cpp             ← Comparación básica con patrones fijos
│   └── experimental_bench.cpp ← Sistema experimental automatizado (PRINCIPAL)
├── algoritmos/
│   ├── kmp.h/cpp             ← Algoritmo Knuth-Morris-Pratt
│   ├── boyer_moore.h/cpp     ← Algoritmo Boyer-Moore
│   ├── rabin_karp.h/cpp      ← Algoritmo Rabin-Karp
│   └── automata.h/cpp        ← Autómata Finito Determinista
├── estructuras/
│   └── suffix_array.h/cpp    ← Suffix Array con búsqueda binaria
├── utils/
│   └── io.h/cpp              ← Lectura de archivos y manejo de documentos
├── datos/documentos/         ← Archivos de texto para pruebas (D1.txt - D50.txt)
├── datos/patrones/           ← Archivos de patrones predefinidos
├── bin/                      ← Ejecutables generados
├── build/                    ← Archivos de compilación CMake
└── resultados_experimentales.csv ← Resultados del estudio experimental
```

## Compilación

**Requisitos:**

- CMake 3.10+
- Compilador C++17
- Windows (MSVC/MinGW) o Linux (GCC/Clang)

**Instrucciones:**

```bash
# Clonar el repositorio
git clone https://github.com/JavierTorresO/Detectar-Patrones-en-varios-archivos.git

cd Detectar-Patrones-en-varios-archivos

# Compilar con CMake
cmake --build build

# Los ejecutables se generan en bin/
```

**Ejecutables generados:**

- `bin/comparador.exe` - Modo interactivo
- `bin/benchmark.exe` - Comparación básica
- `bin/experimental.exe` - Sistema experimental automatizado (PRINCIPAL)

## Modos de Ejecución

### 1. Modo Experimental (Recomendado)

**Sistema automatizado para estudios científicos:**

```bash
./bin/experimental
```

**Características:**

- Variación automática de documentos (5, 10, 15, 20, 25, 30, 35, 40, 45, 50)
- Variación automática de patrones (50, 100, 150, 200, 250) cargados desde archivos
- 20 repeticiones por experimento
- Patrones predefinidos desde archivos TXT para resultados reproducibles
- Medición de tiempo (milisegundos) y memoria (KB)
- Cálculo de estadísticas (promedio, desviación estándar)
- Exportación automática a CSV

**Ejemplo de salida:**

```
=== ESTUDIO EXPERIMENTAL AUTOMATIZADO ===

Documentos disponibles: 50
Texto total: 125430 caracteres

--- Experimento con 5 documentos (12543 caracteres) ---

Cargando patrones desde datos/patrones/patrones_50.txt...
  Cargados 50 patrones desde patrones_50.txt
  Ejecutando KMP con 50 patrones..... Completado!
  Ejecutando Boyer-Moore con 50 patrones..... Completado!

=== RESUMEN DE RESULTADOS EXPERIMENTALES ===
Algoritmo      Docs    Patrones  Tamaño(KB)  Tiempo(ms)  Std(ms)   Mem(KB)   Ocurrencias
-------------------------------------------------------------------------------------------
KMP            5       50        12          0.45        0.03      1         127
Boyer-Moore    5       50        12          0.32        0.04      1         127
...

Resultados exportados a: resultados_experimentales.csv
```

### 2. Modo Benchmark

**Comparación rápida con patrones predefinidos:**

```bash
./bin/benchmark
```

**Características:**

- Patrones fijos definidos en el código
- Medición de tiempo y memoria por algoritmo
- Comparación directa entre todos los algoritmos

### 3. Modo Interactivo

**Entrada manual de patrones:**

```bash
./bin/comparador
```

**Características:**

- Usuario ingresa patrones línea por línea
- Finaliza con Ctrl+D (Windows: Ctrl+Z + Enter)
- Muestra en qué documentos aparece cada patrón
- Ejecuta todos los algoritmos y compara resultados

**Ejemplo de uso:**

```bash
./bin/comparador

Ingresa patrones (una línea c/u), luego Ctrl+D para buscar:
datos
algoritmo
patron
[Ctrl+D]

=== Patron: "datos" ===
KMP: 8 ocurrencias en 2 ms
Boyer-Moore: 8 ocurrencias en 1 ms
Rabin-Karp: 8 ocurrencias en 3 ms
Autómata: 8 ocurrencias en 1 ms
Suffix Array: 8 ocurrencias en 0 ms
  • Doc 1 ("D1.txt") @ pos 45
  • Doc 2 ("D2.txt") @ pos 123
  ...
```

## Resultados Experimentales

### Archivo CSV Generado

El sistema experimental genera `resultados_experimentales.csv` con las siguientes columnas:

| Campo                 | Descripción                                   |
| --------------------- | --------------------------------------------- |
| `Algoritmo`           | Nombre del algoritmo (KMP, Boyer-Moore, etc.) |
| `Num_Documentos`      | Cantidad de documentos utilizados             |
| `Patrones_Cargados`   | Cantidad de patrones cargados desde archivo   |
| `Tamaño_Texto_Chars`  | Tamaño total del texto en caracteres          |
| `Tiempo_Promedio_ms`  | Tiempo promedio de ejecución en milisegundos  |
| `Desviacion_Std_ms`   | Desviación estándar del tiempo                |
| `Memoria_Promedio_KB` | Memoria adicional utilizada en KB             |
| `Total_Ocurrencias`   | Número total de coincidencias encontradas     |
| `Repeticiones`        | Número de repeticiones realizadas (20)        |

### Análisis de Rendimiento

**Ranking de Velocidad (basado en resultados experimentales):**

## Configuración del Estudio Experimental

Para modificar los parámetros del experimento, edita `experimental_bench.cpp`:

```cpp
// Líneas ~430-435
std::vector<int> num_documentos_tests = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
std::vector<std::string> archivos_patrones = {"patrones_50.txt", "patrones_100.txt",
                                              "patrones_150.txt", "patrones_200.txt",
                                              "patrones_250.txt"};
int repeticiones = 20;
```

## Archivos de Patrones

El sistema utiliza archivos predefinidos de patrones ubicados en `datos/patrones/`:

- `patrones_50.txt` - 50 patrones predefinidos
- `patrones_100.txt` - 100 patrones predefinidos
- `patrones_150.txt` - 150 patrones predefinidos
- `patrones_200.txt` - 200 patrones predefinidos
- `patrones_250.txt` - 250 patrones predefinidos

**Formato:** Un patrón por línea, sin espacios adicionales.

## Consideraciones Importantes

### Búsqueda Exacta

- **Sensible a mayúsculas/minúsculas**: `Hola` ≠ `hola`
- **Sensible a tildes**: `canción` ≠ `cancion`
- **Sin normalización automática**: Se requiere preprocesamiento manual

### Archivos de Datos

- Los documentos se concatenan con separador `$`
- Archivos disponibles: `D1.txt` a `D50.txt`
- Tamaño total: ~125KB de texto de prueba
- Cada documento contiene texto real para pruebas realistas

### Medición de Rendimiento

- **Tiempo**: Medido en milisegundos con alta precisión
- **Memoria**: Medida en KB usando memoria RSS del proceso
- **Repeticiones**: 20 ejecuciones por experimento para resultados estadísticamente válidos
- **Exportación**: Resultados automáticamente guardados en CSV para análisis posterior
