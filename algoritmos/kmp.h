#ifndef KMP_H
#define KMP_H

#include <vector>
#include <string>

// Devuelve todos los offsets donde 'pattern' aparece en 'text'
std::vector<int> kmpSearch(const std::string &text, const std::string &pattern);

#endif
