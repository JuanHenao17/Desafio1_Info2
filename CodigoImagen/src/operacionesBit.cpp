#include "operacionesBit.h"

void aplicarXOR(unsigned char* img1, unsigned char* img2, unsigned char* resultado, int total_bytes) {
    for (int i = 0; i < total_bytes; ++i) {
        resultado[i] = img1[i] ^ img2[i];
    }
}

unsigned char rotarDerecha(unsigned char byte, int bits) {
    return (byte >> bits) | (byte << (8 - bits));
}

unsigned char rotarIzquierda(unsigned char byte, int bits) {
    return (byte << bits) | (byte >> (8 - bits));
}

void rotacionImagen(unsigned char* img, unsigned char* resultado, int total_bytes, int bits, bool band) {
    for (int i = 0; i < total_bytes; i++) {
        resultado[i] = band ? rotarDerecha(img[i], bits) : rotarIzquierda(img[i], bits);
    }
}

void DesplazarBits(unsigned char* img, unsigned char* resultado, int total_bytes, int bits, bool band) {
    for (int i = 0; i < total_bytes; i++) {
        resultado[i] = band ? (img[i] >> bits) : (img[i] << bits);
    }
}
