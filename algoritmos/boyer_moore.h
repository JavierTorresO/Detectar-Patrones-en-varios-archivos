#ifndef BOYER_MOORE_H
#define BOYER_MOORE_H

#include <string>
#include <vector>

// Devuelve todos los offsets donde 'pattern' aparece en 'text'
std::vector<int> boyerMooreSearch(const std::string &text, const std::string &pattern);

#endif
