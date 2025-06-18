# Búsqueda de Patrones en Documentos
Se puede buscar patrones de texto en múltiples documentos concatenados usando soluciones algoritmicas y estructurales.  
Los documentos tambien se pueden concatenar usando el símbolo `$` como separador, y el sistema informa en qué documento aparece cada patrón.

## Estructura del proyecto

- `comparador/` → Contiene el archivo principal `main.cpp`
- `algoritmos/` → Implementaciones de algoritmos de búsqueda
- `utils/` → Funciones de lectura de archivos y manejo de cortes
- `datos/documentos/` → Archivos `.txt` individuales que actúan como documentos

# Restricción importante:

Este programa realiza comparaciones exactas entre patrones y contenido de documentos.  
Por lo tanto, considera **distintos** los caracteres con tilde (acentos) y sin tilde.  
Ejemplo: `canción` ≠ `cancion`, `cómo` ≠ `como`.
Si se desea hacer la búsqueda insensible a acentos o mayúsculas, se debe aplicar una normalización previa al texto y patrones (no implementado en esta versión).


## Cómo compilar

```bash
g++ -std=c++17 comparador/main.cpp algoritmos/kmp.cpp utils/io.cpp -o kmp !!actualizar cada vez que se agreguen algoritmos
./kmp

