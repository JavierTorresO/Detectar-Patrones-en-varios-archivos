# 🔍 Sistema de Búsqueda de Patrones en Documentos

Un sistema completo de comparación de algoritmos de búsqueda de patrones en múltiples documentos de texto, diseñado para estudios experimentales y análisis de rendimiento.

## 📋 Características Principales

- **5 Algoritmos de Búsqueda**: KMP, Boyer-Moore, Rabin-Karp, Autómata Finito, Suffix Array
- **Sistema Experimental Automatizado**: Variación automática de documentos y patrones
- **Medición Precisa**: Tiempo de ejecución y uso de memoria con estadísticas
- **Exportación de Datos**: Resultados en formato CSV para análisis posterior
- **Generación Automática**: Patrones existentes y no existentes en el texto
- **Múltiples Repeticiones**: 20 ejecuciones por experimento para resultados confiables

## 🏗️ Estructura del Proyecto

```
📁 Detectar-Patrones-en-varios-archivos/
├── 📁 comparador/
│   ├── main.cpp              ← Modo interactivo (usuario ingresa patrones)
│   ├── bench.cpp             ← Comparación básica con patrones fijos
│   └── experimental_bench.cpp ← Sistema experimental automatizado ⭐
├── 📁 algoritmos/
│   ├── kmp.h/cpp             ← Algoritmo Knuth-Morris-Pratt
│   ├── boyer_moore.h/cpp     ← Algoritmo Boyer-Moore
│   ├── rabin_karp.h/cpp      ← Algoritmo Rabin-Karp
│   └── automata.h/cpp        ← Autómata Finito Determinista
├── 📁 estructuras/
│   └── suffix_array.h/cpp    ← Suffix Array con búsqueda binaria
├── 📁 utils/
│   └── io.h/cpp              ← Lectura de archivos y manejo de documentos
├── 📁 datos/documentos/      ← Archivos de texto para pruebas (D1.txt - D13.txt)
├── 📁 bin/                   ← Ejecutables generados
├── 📁 build/                 ← Archivos de compilación CMake
└── resultados_experimentales.csv ← Resultados del estudio experimental
```

## ⚙️ Compilación

**Requisitos:**

- CMake 3.10+
- Compilador C++17
- Windows (MSVC/MinGW) o Linux (GCC/Clang)

**Instrucciones:**

```bash
# Clonar el repositorio
git clone <URL_REPOSITORIO>
cd Detectar-Patrones-en-varios-archivos

# Compilar con CMake
cmake --build build

# Los ejecutables se generan en bin/
```

**Ejecutables generados:**

- `bin/comparador.exe` - Modo interactivo
- `bin/benchmark.exe` - Comparación básica
- `bin/experimental.exe` - **Sistema experimental automatizado** ⭐

## 🔬 Modos de Ejecución

### 1. Modo Experimental (Recomendado)

**Sistema automatizado para estudios científicos:**

```bash
./bin/experimental
```

**Características:**

- ✅ Variación automática de documentos (3, 5, 8, 10, 13)
- ✅ Variación automática de patrones (5, 10, 20, 30)
- ✅ 20 repeticiones por experimento
- ✅ Generación de patrones existentes y no existentes
- ✅ Medición de tiempo (microsegundos) y memoria (KB)
- ✅ Cálculo de estadísticas (promedio, desviación estándar)
- ✅ Exportación automática a CSV

**Ejemplo de salida:**

```
=== ESTUDIO EXPERIMENTAL AUTOMATIZADO ===

Documentos disponibles: 13
Texto total: 13213 caracteres

--- Experimento con 3 documentos (4527 caracteres) ---

Generando 5 patrones...
  Ejecutando KMP con 5 patrones, 20 repeticiones..... Completado!
  Ejecutando Boyer-Moore con 5 patrones, 20 repeticiones..... Completado!

=== RESUMEN DE RESULTADOS EXPERIMENTALES ===
Algoritmo      Docs    Patrones  Tamaño(KB)  Tiempo(ms)  Std(ms)   Mem(KB)   Ocurrencias
-------------------------------------------------------------------------------------------
KMP            3       5         4           0.04        0.01      0         21
Boyer-Moore    3       5         4           0.04        0.05      0         21
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
- Muestra en qué documentos aparece cada patrón
- Un solo algoritmo por ejecución (configurable en código)

## 📊 Resultados Experimentales

### Archivo CSV Generado

El sistema experimental genera `resultados_experimentales.csv` con las siguientes columnas:

| Campo                 | Descripción                                   |
| --------------------- | --------------------------------------------- |
| `Algoritmo`           | Nombre del algoritmo (KMP, Boyer-Moore, etc.) |
| `Num_Documentos`      | Cantidad de documentos utilizados             |
| `Num_Patrones`        | Cantidad de patrones buscados                 |
| `Tamaño_Texto`        | Tamaño total del texto en caracteres          |
| `Tiempo_Promedio_ms`  | Tiempo promedio de ejecución en milisegundos  |
| `Desviacion_Std_ms`   | Desviación estándar del tiempo                |
| `Memoria_Promedio_KB` | Memoria adicional utilizada en KB             |
| `Total_Ocurrencias`   | Número total de coincidencias encontradas     |
| `Repeticiones`        | Número de repeticiones realizadas (20)        |

### Análisis de Rendimiento

**Ranking de Velocidad (basado en resultados experimentales):**

1. **🥇 Boyer-Moore** - Más rápido (0.02-0.35ms)
2. **🥈 KMP** - Segundo lugar (0.04-0.43ms)
3. **🥉 Automata** - Tercero (0.08-1.28ms)
4. **4️⃣ Rabin-Karp** - Cuarto (0.12-1.57ms)
5. **5️⃣ Suffix Array** - Quinto (0.85-3.38ms) \*

_\*Suffix Array tiene overhead de construcción pero búsquedas muy rápidas_

**Eficiencia de Memoria:**

- Todos los algoritmos son muy eficientes (0-3 KB adicionales)
- Boyer-Moore y KMP: 0 KB en la mayoría de casos
- Automata: Ocasionalmente 1 KB extra

## 🔧 Configuración del Estudio Experimental

Para modificar los parámetros del experimento, edita `experimental_bench.cpp`:

```cpp
// Línea ~290
std::vector<int> num_documentos_tests = {3, 5, 8, 10, 13};  // Documentos a probar
std::vector<int> num_patrones_tests = {5, 10, 20, 30};      // Patrones por experimento
int repeticiones = 20;                                       // Repeticiones por experimento
```

## 📈 Generación de Patrones

El sistema genera automáticamente:

- **70% patrones existentes**: Extraídos del texto real
- **30% patrones no existentes**: Generados aleatoriamente
- **Longitud**: 3-10 caracteres (configurable)

## ⚠️ Consideraciones Importantes

### Búsqueda Exacta

- **Sensible a mayúsculas/minúsculas**: `Hola` ≠ `hola`
- **Sensible a tildes**: `canción` ≠ `cancion`
- **Sin normalización automática**: Se requiere preprocesamiento manual

### Archivos de Datos

- Los documentos se concatenan con separador `$`
- Archivos disponibles: `D1.txt` a `D13.txt`
- Tamaño total: ~13KB de texto de prueba
