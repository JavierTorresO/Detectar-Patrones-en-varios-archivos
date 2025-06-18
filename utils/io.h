#ifndef IO_H
#define IO_H

#include <string>
#include <vector>

// Lee todos los archivos .txt desde una carpeta, los concatena con '$'
// Guarda en 'nombresDoc' los nombres de los archivos (documentos)
// Guarda en 'cortes' las posiciones donde termina cada documento en el texto concatenado
std::string leerDocumentosDesdeCarpeta(const std::string& carpeta, std::vector<std::string>& nombresDoc, std::vector<int>& cortes);

// Lee y concatena sólo los documentos seleccionados (por nombre) en 'docsSeleccionados'
// Igual guarda en 'cortes' las posiciones de corte
std::string concatenarDocumentosSeleccionados(const std::string& carpeta, const std::vector<std::string>& docsSeleccionados, std::vector<int>& cortes);

// Dado una posición en el texto concatenado, indica a qué documento pertenece
int obtenerDocumento(int pos, const std::vector<int>& cortes);

#endif
