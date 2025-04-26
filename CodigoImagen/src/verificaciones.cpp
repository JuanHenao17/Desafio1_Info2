#include "verificaciones.h"
#include "operacionesBit.h"

bool verificarXOR(unsigned char* img, unsigned char* imgXOR, unsigned char* mascara, unsigned int* valores_txt, int semilla, int total_bytes_mascara){

    for (int i = 0; i < total_bytes_mascara; ++i) {

        unsigned int val1 = img[semilla + i];
        unsigned int val2 = imgXOR[semilla + i];

        if ((val1 ^ val2) + mascara[i] != valores_txt[i]){
            return false;
        }

    }

    return true;

}

bool verificarRotacion(unsigned char* img, unsigned char* mascara, unsigned int* valores_txt, int semilla, int total_bytes_mascara, int bits, bool band){

    for (int i = 0; i < total_bytes_mascara; ++i) {

        unsigned int val1 = img[semilla + i];
        unsigned int resultado = band ? (rotarDerecha(val1, bits) + mascara[i]) : (rotarIzquierda(val1, bits) + mascara[i]);

        if(resultado != valores_txt[i]){
            return false;
        }
    }

    return true;

}

bool verificarDesplazamiento(unsigned char* img, unsigned char* mascara, unsigned int* valores_txt, int semilla, int total_bytes_mascara, int bits, bool band){

    for (int i = 0; i < total_bytes_mascara; ++i) {

        unsigned int val1 = img[semilla + i];
        unsigned int resultado = band ? ((val1 >> bits) + mascara[i]) : ((val1 << bits) + mascara[i]);

        if(resultado != valores_txt[i]){
            return false;
        }
    }

    return true;

}
