#ifndef ENMASCARAMIENTO_H
#define ENMASCARAMIENTO_H

void aplicarMascaraInversa(unsigned char* imagen, unsigned char* mascara, int semilla, int total_bytes);

bool compararResultadoConTxt(unsigned char* resultado, unsigned int* valoresTxt, int semilla, int n_pixels);

#endif // ENMASCARAMIENTO_H
