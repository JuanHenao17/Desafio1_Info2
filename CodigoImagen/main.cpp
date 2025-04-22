#include <iostream>
#include "procesamiento.h"
#include "operacionesBit.h"

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
    int w_mask = 0;
    int h_mask = 0;
    unsigned char *pixelDataXoR = loadPixels("I_M.bmp", w_mask, h_mask);

    if (pixelDataXoR == nullptr) {
        cout << "❌ Error al cargar la imagen I_M.bmp. Verifique que esté en la carpeta correcta." << endl;
        delete[] pixelData;
        return 1;
    }

    unsigned short cantidad_pasos = contarArchivosTxt();
    for (int paso = cantidad_pasos - 1; paso >= 0; --paso){

        //Cargar los datos del txt para el enmascaramiento y la verificacion
        int semilla = 0;
        int n_pixels = 0;
        string nombreArchivo = "M" + to_string(paso) + ".txt";
        unsigned int* valoresTxt = loadSeedMasking(nombreArchivo.c_str(), semilla, n_pixels);

        unsigned char* resultadoOp = new unsigned char[total_bytes];

        for (int tipo = 0; tipo < 5; ++tipo) { // 0: XOR, 1: ROT_DER, 2:ROT_IZQ, 3: SHIFT_DER, 4:SHIFT_IZQ
            for (int bits = 1; bits <= 8; ++bits) {
                // 3.1. Copiar la imagen actual (encriptada) a un arreglo temporal

                if (tipo == 0) {
                    // XOR con imagen IM (es su propia inversa)
                    aplicarXOR(pixelData, pixelDataXoR, resultadoOp, total_bytes);
                } else if (tipo == 1) {
                    rotacionImagen(pixelData, resultadoOp, total_bytes, bits, true);

                } else if (tipo == 2) {
                    rotacionImagen(pixelData, resultadoOp, total_bytes, bits, false);

                } else if(tipo==3){
                    DesplazarBits(pixelData, resultadoOp, total_bytes, bits, true);

                } else if(tipo==4){
                    DesplazarBits(pixelData, resultadoOp, total_bytes, bits, false);
                }

            }
        }
    }
    // Variables para almacenar la semilla y el número de píxeles leídos del archivo de enmascaramiento
    //int seed = 0;
    //int n_pixels = 0;

    // Carga los datos de enmascaramiento desde un archivo .txt (semilla + valores RGB)
    //unsigned int *maskingData = loadSeedMasking("M1.txt", seed, n_pixels);

    // Muestra en consola los primeros valores RGB leídos desde el archivo de enmascaramiento
    //for (int i = 0; i < n_pixels * 3; i += 3) {
        //cout << "Pixel " << i / 3 << ": ("
            // << maskingData[i] << ", "
            // << maskingData[i + 1] << ", "
             //<< maskingData[i + 2] << ")" << endl;
    //}

    // Libera la memoria usada para los datos de enmascaramiento
    //if (maskingData != nullptr){
        //delete[] maskingData;
       // maskingData = nullptr;
    //}

    return 0; // Fin del programa
}
