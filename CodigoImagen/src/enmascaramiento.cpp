#include "enmascaramiento.h"

void aplicarMascaraInversa(unsigned char* imagen, unsigned char* mascara, int semilla, int total_bytes) {

    for (int i = 0; i < total_bytes; ++i) {
        int index_mascara = (semilla + i) % total_bytes;

        if (imagen[i] < mascara[index_mascara]) {
            imagen[i] = 256 + imagen[i] - mascara[index_mascara];
        } else {
            imagen[i] -= mascara[index_mascara];
        }
    }
}

bool compararResultadoConTxt(unsigned char* resultado, unsigned int* valoresTxt, int semilla, int n_pixels) {

    for (int i = 0; i < n_pixels * 3; ++i) {
        int indexImagen = (semilla + i) % (n_pixels * 3);

        if (resultado[indexImagen] != valoresTxt[i] % 256) {
            return false;
        }
    }
    return true;
}
