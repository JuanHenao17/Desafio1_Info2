#ifndef VERIFICACIONES_H
#define VERIFICACIONES_H

bool verificarXOR(unsigned char* img, unsigned char* imgXOR, unsigned char* mascara, unsigned int* valores_txt, int semilla, int total_bytes_mascara);

bool verificarRotacion(unsigned char* img, unsigned char* mascara, unsigned int* valores_txt, int semilla, int total_bytes_mascara, int bits, bool band);

bool verificarDesplazamiento(unsigned char* img, unsigned char* mascara, unsigned int* valores_txt, int semilla, int total_bytes_mascara, int bits, bool band);

#endif // VERIFICACIONES_H
