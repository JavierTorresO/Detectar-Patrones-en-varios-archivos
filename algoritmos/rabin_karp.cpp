#include "rabin_karp.h"
#include <vector>
#include <string>

const int d = 256;             // número de caracteres posibles (ASCII)
const int q = 101;             // número primo para hashing (puedes cambiarlo)

std::vector<int> rabinKarpSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> result;
    int n = text.size();
    int m = pattern.size();

    if (m == 0 || n < m) return result;

    int h = 1;
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    int p = 0;  // hash del patrón
    int t = 0;  // hash del texto

    // calcular hash inicial de patrón y ventana de texto
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // deslizar la ventana de texto
    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            // posible coincidencia, verificar carácter por carácter
            if (text.substr(i, m) == pattern)
                result.push_back(i);
        }
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) t += q; // asegurarse de que el hash sea positivo
        }
    }

    return result;
}
