#include <iostream>
#include "procesamiento.h"
#include "operacionesBit.h"
#include "enmascaramiento.h"

using namespace std;

int main()
{

    string nombreImagen;
    cout << "Bienvenido, ingrese el nombre de la imagen a desencriptar (ej: I_D.bmp): ";
    cin >> nombreImagen;

    // Variables para almacenar las dimensiones de la imagen
    int height = 0;
    int width = 0;

    // Carga la imagen BMP en memoria dinámica y obtiene ancho y alto
    QString rutaImagen = QString::fromStdString(nombreImagen);
    unsigned char *pixelData = loadPixels(rutaImagen, width, height);


    if (pixelData == nullptr) {
        cout << "Error al cargar la imagen. Verifique el nombre y la ruta." << endl;
        return 1;
    }

    int total_bytes = height * width * 3;

    // Cargar la imagen BMP con la que se realiza el XOR en memoria dinámica y obtiene ancho y alto
    int w_maskXOR = 0;
    int h_maskXOR = 0;
    unsigned char *pixelDataXoR = loadPixels("I_M.bmp", w_maskXOR, h_maskXOR);

    if (pixelDataXoR == nullptr) {
        cout << "Error al cargar la imagen I_M.bmp. Verifique que esté en la carpeta correcta." << endl;
        delete[] pixelData;
        return 1;
    }

    // Cargar la imagen BMP con la que se realiza la mascara en memoria dinámica y obtiene ancho y alto
    int w_mask = 0;
    int h_mask = 0;
    unsigned char *pixelDataMask = loadPixels("M.bmp", w_mask, h_mask);

    if (pixelDataMask == nullptr) {
        cout << "Error al cargar la imagen M.bmp. Verifique que esté en la carpeta correcta." << endl;
        delete[] pixelData;
        return 1;
    }

    unsigned short cantidad_pasos = contarArchivosTxt();
    for (int paso = cantidad_pasos - 2; paso >= 0; --paso){

        //Cargar los datos del txt para el enmascaramiento y la verificacion
        bool coincidencia = false;
        int semilla = 0;
        int n_pixels = 0;
        string nombreArchivo = "M" + to_string(paso) + ".txt";
        unsigned int* valoresTxt = loadSeedMasking(nombreArchivo.c_str(), semilla, n_pixels);

        unsigned char* resultado = new unsigned char[total_bytes];
        aplicarMascaraInversa(pixelData, pixelDataMask, semilla, total_bytes);

        for (int tipo = 0; tipo < 5; ++tipo) { // 0: XOR, 1: ROT_DER, 2:ROT_IZQ, 3: SHIFT_DER, 4:SHIFT_IZQ

            if(coincidencia){
                break;
            }

            if (tipo == 0) {

                aplicarXOR(pixelData, pixelDataXoR, resultado, total_bytes);
                if(compararResultadoConTxt(resultado, valoresTxt, semilla, n_pixels)){
                    cout << "OPERACION ENCONTRADA: Paso " << paso << ": XOR" <<endl;
                    break;
                }
            }

            for (int bits = 1; bits <= 8; ++bits) {

                if(tipo == 0){
                    break;
                }

                else if (tipo == 1) {

                    rotacionImagen(pixelData, resultado, total_bytes, bits, true);
                    if(compararResultadoConTxt(resultado, valoresTxt, semilla, n_pixels)){
                        coincidencia = true;
                        cout << "OPERACION ENCONTRADA: Paso " << paso << ": Rotacion a la izquierda de " << bits << " bits" <<endl;
                        break;
                    }

                } else if (tipo == 2) {

                    rotacionImagen(pixelData, resultado, total_bytes, bits, false);
                    if(compararResultadoConTxt(resultado, valoresTxt, semilla, n_pixels)){
                        coincidencia = true;
                        cout << "OPERACION ENCONTRADA: Paso " << paso << ": Rotacion a la derecha de " << bits << " bits" <<endl;
                        break;
                    }

                } else if(tipo==3){

                    DesplazarBits(pixelData, resultado, total_bytes, bits, true);
                    if(compararResultadoConTxt(resultado, valoresTxt, semilla, n_pixels)){
                        coincidencia = true;
                        cout << "OPERACION ENCONTRADA: Paso " << paso << ": Desplazamiento a la izquierda de " << bits << " bits" <<endl;
                        break;
                    }

                } else if(tipo==4){

                    DesplazarBits(pixelData, resultado, total_bytes, bits, false);
                    if(compararResultadoConTxt(resultado, valoresTxt, semilla, n_pixels)){
                        coincidencia = true;
                        cout << "OPERACION ENCONTRADA: Paso " << paso << ": Desplazamiento a la derecha de " << bits << " bits" <<endl;
                        break;
                    }
                }

            }

            if (!coincidencia) {
                cout << "No se encontró operacion valida para el paso " << paso << endl;
            }

        }

        memcpy(pixelData, resultado, total_bytes);
        delete[] valoresTxt;
        delete[] resultado;

    }

    delete[] pixelData;
    delete[] pixelDataMask;
    delete[] pixelDataXoR;

    return 0; // Fin del programa
}
