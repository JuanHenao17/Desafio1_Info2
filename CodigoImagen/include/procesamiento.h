#ifndef PROCESAMIENTO_H
#define PROCESAMIENTO_H

#include <QString>

// Carga los píxeles RGB de una imagen BMP (retorna arreglo dinámico)
unsigned char* loadPixels(QString input, unsigned int &width, unsigned int &height);

// Exporta imagen modificada desde un arreglo RGB
bool exportImage(unsigned char* pixelData, int width,int height, QString archivoSalida);

// Carga la semilla y los datos RGB desde un archivo .txt de enmascaramiento
unsigned int* loadSeedMasking(const char* nombreArchivo, unsigned int &seed, unsigned int &n_pixels);

unsigned short contarArchivosTxt();

#endif // PROCESAMIENTO_H
