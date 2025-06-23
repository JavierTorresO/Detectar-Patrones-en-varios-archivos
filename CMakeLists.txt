cmake_minimum_required(VERSION 3.10)
project(DetectarPatrones VERSION 1.0 LANGUAGES CXX)

# Usar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opciones de compilación
add_compile_options(-O2 -Wall -Wextra)

# Incluir headers
include_directories(core PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/utils
    ${PROJECT_SOURCE_DIR}/algoritmos
    ${PROJECT_SOURCE_DIR}/estructuras)

# Fuente de algoritmos, estructuras y comparador
file(GLOB ALGORITHM_SRCS
    ${PROJECT_SOURCE_DIR}/algoritmos/*.cpp
)
file(GLOB STRUCTURE_SRCS
    ${PROJECT_SOURCE_DIR}/estructuras/*.cpp
)
file(GLOB UTIL_SRCS
    ${PROJECT_SOURCE_DIR}/utils/*.cpp
)
set(COMPARADOR_SRC
    ${PROJECT_SOURCE_DIR}/comparador/main.cpp
)

# Crear librería estática con algoritmos, estructuras y utils
add_library(core STATIC
    ${ALGORITHM_SRCS}
    ${STRUCTURE_SRCS}
    ${UTIL_SRCS}
)

# Ejecutable que enlaza con la librería core
add_executable(comparador ${COMPARADOR_SRC})
target_link_libraries(comparador PRIVATE core)

# Directorio de salida (prueba1)
set_target_properties(comparador PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)