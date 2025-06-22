cmake_minimum_required(VERSION 3.10)
project(DetectarPatrones VERSION 1.0 LANGUAGES CXX)

# Usar C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opciones de compilación
add_compile_options(-O2 -Wall -Wextra)

# Incluir headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Fuente de algoritmos y estructuras
file(GLOB ALGORITHM_SRCS
    ${PROJECT_SOURCE_DIR}/algoritmos/*.cpp
)
file(GLOB STRUCTURE_SRCS
    ${PROJECT_SOURCE_DIR}/estructuras/*.cpp
)
file(GLOB UTIL_SRCS
    ${PROJECT_SOURCE_DIR}/utils/*.cpp
)
# Fuente del comparador
set(COMPARADOR_SRC
    comparador/main.cpp
)

# Crear librería estática con algoritmos, estructuras y utils
add_library(core ${ALGORITHM_SRCS} ${STRUCTURE_SRCS} ${UTIL_SRCS})

# Ejecutable que enlaza con la librería core
add_executable(comparador ${COMPARADOR_SRC})
target_link_libraries(comparador PRIVATE core)
