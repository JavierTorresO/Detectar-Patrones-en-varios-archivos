# Búsqueda de Patrones en Documentos

Se puede buscar patrones de texto en múltiples documentos concatenados usando soluciones algoritmicas y estructurales.  
Los documentos están concatenados con el símbolo `$` como separador, y el sistema informa en qué documento aparece cada patrón.

## Estructura del proyecto

- `comparador/` → Contiene los archivos principales `bench.cpp` y `main.cpp`(interactivo)
- `algoritmos/` → Implementaciones de algoritmos de búsqueda
- `estructuras/` → Implementación de soluciones basadas en estructuras
- `utils/` → Funciones de lectura de archivos y manejo de cortes
- `bin/` → Ejecutables generados
- `scripts/build.sh` → Script para compilar
- `datos/documentos/` → Archivos `.txt` individuales que actúan como documentos
- `CMakeLists.txt`

# Restricción importante:

Este programa realiza comparaciones exactas carácter por carácter.
Eso significa que distingue entre:
- Letras con y sin tilde → `canción` ≠ `cancion`
- Mayúsculas y minúsculas → `Hola` ≠ `hola`

!!Si deseas hacer búsquedas insensibles a tildes o mayúsculas, debes aplicar una normalización previa al texto y a los patrones (No implementado en esta versión).


## Compilación
Este proyecto usa [CMake](https://cmake.org/). Para compilarlo, ejecuta:

```bash
git clone <https://github.com/JavierTorresO/Detectar-Patrones-en-varios-archivos>
cd DetectarPatrones
chmod +x scripts/build.sh
./scripts/build.sh
```
Esto creará los ejecutables dentro de "bin/":
bin/
├── comparador     ← para usar main.cpp
├── benchmark      ← para usar bench.cpp

## Ejecución

- Modo benchmark:
Para comparar varios tiempos a la vez, este modo usa patrones predefinidos que son definidos en "patrones" dentro de la funcion main de `bench.cpp`. Este archivo ejecuta todos los algoritmos a la vez para poder comparar tiempos.

```bash
./bin/benchmark
```
EJEMPLO DE EJECUCIÓN:
=== KMP ===
  "dato": 3 ocurrencias en 2 ms

=== Boyer-Moore ===
  "dato": 3 ocurrencias en 1 ms

=== Rabin-Karp ===
  "dato": 3 ocurrencias en 2 ms

=== Autómata Finito ===
  "dato": 3 ocurrencias en 1 ms


- Modo interactivo:
Carga todos los documentos en `datos/documentos/`, en este se te pide ingresar por teclado linea a linea que patrones quieres buscar y luego imprime en que documentos aparece cada patrón. 
!!!El archivo main.cpp está diseñado para ejecutar solo un algoritmo de búsqueda a la vez.
Para cambiar el algoritmo que se utiliza, debes editar manualmente el archivo y hacer lo siguiente:

1.Descomentar el #include del algoritmo que deseas usar.
Ejm: `//#include "rabin_karp.h"` -> `#include "rabin_karp.h"`
2.Comentar los #include y la llamada de los demás algoritmos.
Ejm: por defecto está activado el KMP `#include "kmp.h"` -> `//#include "kmp.h"`
3.Cambiar la línea de búsqueda para llamar a la función correspondiente.
Ejm: `auto occs = kmpSearch(texto, p);` -> `//auto occs = kmpSearch(texto, p);` comentar la antigua
     `//auto occs = rabinKarpSearch(texto, p);` -> `auto occs = rabinKarpSearcharch(texto, p);` descomentar la  deseada
     

```bash
./bin/comparador
```
EJEMPLO DE EJECUCIÓN:
Ingresa patrones (una línea c/u), luego Ctrl+D para buscar:
*ingresar patrones linea por linea, luego CTRL+D para buscar
Patrón: "bin" → 2 ocurrencias en 3 ms
  • Doc 1 (“doc1.txt”) @ pos 34
  • Doc 2 (“doc2.txt”) @ pos 12
...
