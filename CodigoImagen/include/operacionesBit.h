#ifndef OPERACIONESBIT_H
#define OPERACIONESBIT_H

void aplicarImagenXOR(unsigned char* img1, unsigned char* img2, unsigned int total_bytes);

unsigned char rotarDerecha(unsigned char byte, unsigned short bits);

void rotacionImagen(unsigned char* img, unsigned int total_bytes, unsigned short bits);

void desplazarImagen(unsigned char* img, unsigned int total_bytes, unsigned short bits, bool band);

#endif // OPERACIONESBIT_H
