#include "operacionesBit.h"

void aplicarImagenXOR(unsigned char* img1, unsigned char* img2, int total_bytes) {
    for (int i = 0; i < total_bytes; ++i) {
        img1[i] = img1[i] ^ img2[i];
    }
}

unsigned char rotarDerecha(unsigned char byte, int bits) {
    return (byte >> bits) | (byte << (8 - bits));
}

unsigned char rotarIzquierda(unsigned char byte, int bits) {
    return (byte << bits) | (byte >> (8 - bits));
}

void rotacionImagen(unsigned char* img, int total_bytes, int bits, bool band) {
    for (int i = 0; i < total_bytes; i++) {
        img[i] = band ? rotarDerecha(img[i], bits) : rotarIzquierda(img[i], bits);
    }
}


void desplazarImagen(unsigned char* img, int total_bytes, int bits, bool band) {
    for (int i = 0; i < total_bytes; i++) {
        img[i] = band ? (img[i] >> bits) : (img[i] << bits);
    }
}
