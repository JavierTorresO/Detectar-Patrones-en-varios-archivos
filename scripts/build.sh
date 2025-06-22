#!/usr/bin/env bash
set -e

# Ruta a la raíz del proyecto
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$ROOT/build"

# Crear y entrar a build/
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# 1) Configurar (detecta Ninja o Make según tu sistema)
cmake -S .. -B .

# 2) Compilar usando el build tool que corresponda
cmake --build . --parallel "$(nproc)"

echo
echo "=== Build completo! Ejecutable en $BUILD_DIR/comparador ==="
