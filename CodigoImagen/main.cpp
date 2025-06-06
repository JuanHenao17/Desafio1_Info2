#include <iostream>
#include "procesamiento.h"
#include "operacionesBit.h"
#include "verificaciones.h"

using namespace std;

int main()
{

    string nombreImagen;
    cout << "Bienvenido, ingrese el nombre de la imagen a desencriptar (ej: I_D.bmp): ";
    cin >> nombreImagen;

    // Variables para almacenar las dimensiones de la imagen
    unsigned int height = 0;
    unsigned int width = 0;

    // Carga la imagen BMP en memoria dinámica y obtiene ancho y alto
    QString rutaImagen = QString::fromStdString(nombreImagen);
    unsigned char *pixelData = loadPixels(rutaImagen, width, height);

    if (pixelData == nullptr) {
        cout << "Error al cargar la imagen. Verifique el nombre y la ruta." << endl;
        return 1;
    }

    unsigned int total_bytes = height * width * 3;

    // Cargar la imagen BMP con la que se realiza el XOR en memoria dinámica y obtiene ancho y alto
    unsigned int w_maskXOR = 0;
    unsigned int h_maskXOR = 0;
    unsigned char *pixelDataXoR = loadPixels("I_M.bmp", w_maskXOR, h_maskXOR);

    if (pixelDataXoR == nullptr) {
        cout << "Error al cargar la imagen I_M.bmp. Verifique que esté en la carpeta correcta." << endl;
        delete[] pixelData;
        return 1;
    }

    // Cargar la imagen BMP con la que se realiza la mascara en memoria dinámica y obtiene ancho y alto
    unsigned int w_mask = 0;
    unsigned int h_mask = 0;
    unsigned char *pixelDataMask = loadPixels("M.bmp", w_mask, h_mask);

    if (pixelDataMask == nullptr) {
        cout << "Error al cargar la imagen M.bmp. Verifique que esté en la carpeta correcta." << endl;
        delete[] pixelData;
        return 1;
    }

    unsigned int total_bytes_mask = w_mask * h_mask * 3;

    unsigned short cantidad_pasos = contarArchivosTxt();

    for (int paso = cantidad_pasos - 1; paso >= 0; --paso){

        //Cargar los datos del txt para el enmascaramiento y la verificacion
        bool coincidencia = false;
        unsigned int semilla = 0;
        unsigned int n_pixels = 0;
        string nombreArchivo = "M" + to_string(paso) + ".txt";
        unsigned int* valoresTxt = loadSeedMasking(nombreArchivo.c_str(), semilla, n_pixels);

        for (int tipo = 0; tipo < 4; ++tipo) { // 0: XOR, 1: ROTACION, 2: SHIFT_DER, 3:SHIFT_IZQ

            if(coincidencia){
                break;
            }

            if (tipo == 0) {

                if(verificarXOR(pixelData, pixelDataXoR, pixelDataMask, valoresTxt, semilla, total_bytes_mask)){
                    coincidencia = true;
                    aplicarImagenXOR(pixelData, pixelDataXoR, total_bytes);
                    cout << "OPERACION ENCONTRADA: Paso " << paso + 1 << ": XOR" <<endl;
                    break;
                }
            }

            for (unsigned short bits = 1; bits <= 8; ++bits) {

                if (tipo == 1) {

                    if(verificarRotacion(pixelData, pixelDataMask, valoresTxt, semilla, total_bytes_mask, bits)){
                        rotacionImagen(pixelData, total_bytes, bits);
                        coincidencia = true;
                        cout << "OPERACION ENCONTRADA: Paso " << paso + 1 << ": Rotacion a la derecha de " << 8 - bits  << " bits o rotacion a la izquierda de " << bits << " bits" <<endl;
                        break;
                    }


                } else if(tipo==2){

                    if(verificarDesplazamiento(pixelData, pixelDataMask, valoresTxt, semilla, total_bytes_mask, bits, true)){
                        desplazarImagen(pixelData, total_bytes, bits, true);
                        coincidencia = true;
                        cout << "OPERACION ENCONTRADA: Paso " << paso + 1 << ": Desplazamiento a la derecha de " << bits << " bits" <<endl;
                        break;
                    }

                } else if(tipo==3){

                    if(verificarDesplazamiento(pixelData, pixelDataMask, valoresTxt, semilla, total_bytes_mask, bits, false)){
                        desplazarImagen(pixelData, total_bytes, bits, false);
                        coincidencia = true;
                        cout << "OPERACION ENCONTRADA: Paso " << paso + 1 << ": Desplazamiento a la izquierda de " << bits << " bits" <<endl;
                        break;
                    }
                }

            }

        }

        if (!coincidencia) {
            cout << "No se encontro operacion valida para el paso " << paso + 1<< endl;
        }

        delete[] valoresTxt;

    }

    delete[] pixelData;
    delete[] pixelDataMask;
    delete[] pixelDataXoR;

    return 0; // Fin del programa
}
