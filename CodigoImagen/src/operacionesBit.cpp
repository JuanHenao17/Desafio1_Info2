#include "operacionesBit.h"

void aplicarImagenXOR(unsigned char* img1, unsigned char* img2, unsigned int total_bytes) {
    for (unsigned int i = 0; i < total_bytes; ++i) {
        img1[i] = img1[i] ^ img2[i];
    }
}

unsigned char rotarDerecha(unsigned char byte, unsigned short bits) {
    return (byte >> bits) | (byte << (8 - bits));
}

void rotacionImagen(unsigned char* img, unsigned int total_bytes, unsigned short bits) {
    for (unsigned int i = 0; i < total_bytes; i++) {
        img[i] = rotarDerecha(img[i], bits);
    }
}


void desplazarImagen(unsigned char* img, unsigned int total_bytes, unsigned short bits, bool band) {
    for (unsigned int i = 0; i < total_bytes; i++) {
        img[i] = band ? (img[i] >> bits) : (img[i] << bits);
    }
}
