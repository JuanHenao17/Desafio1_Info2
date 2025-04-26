#ifndef OPERACIONESBIT_H
#define OPERACIONESBIT_H

bool verificarXOR(unsigned char* img, unsigned char* imgXOR, unsigned char* mascara, unsigned int* valores_txt, int semilla, int total_bytes_mascara);

void aplicarImagenXOR(unsigned char* img1, unsigned char* img2, int total_bytes);

bool verificarRotacion(unsigned char* img, unsigned char* mascara, unsigned int* valores_txt, int semilla, int total_bytes_mascara, int bits, bool band);

unsigned char rotarDerecha(unsigned char byte, int bits);

unsigned char rotarIzquierda(unsigned char byte, int bits);

void rotacionImagen(unsigned char* img, int total_bytes, int bits, bool band);

bool verificarDesplazamiento(unsigned char* img, unsigned char* mascara, unsigned int* valores_txt, int semilla, int total_bytes_mascara, int bits, bool band);

void desplazarImagen(unsigned char* img, int total_bytes, int bits, bool band);

#endif // OPERACIONESBIT_H
