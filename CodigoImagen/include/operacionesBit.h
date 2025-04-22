#ifndef OPERACIONESBIT_H
#define OPERACIONESBIT_H

void aplicarXOR(unsigned char* img1, unsigned char* img2, unsigned char* resultado, int total_bytes);

unsigned char rotarDerecha(unsigned char byte, int bits);

unsigned char rotarIzquierda(unsigned char byte, int bits);

void rotacionImagen(unsigned char* img, unsigned char* resultado, int total_bytes, int bits, bool band);

void DesplazarBits(unsigned char* img, unsigned char* resultado, int total_bytes, int bits, bool band);

#endif // OPERACIONESBIT_H
