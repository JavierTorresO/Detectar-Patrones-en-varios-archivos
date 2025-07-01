#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <string>
#include <vector>

// Busca ocurrencias del patrón en el texto usando autómata finito
std::vector<int> automataSearch(const std::string& text, const std::string& pattern);

#endif
