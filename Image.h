#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Clase utilitaria para manejar las imagenes en formato txt (guardar, cargar, obtener pixeles a partir de una coordenada en el vector imagen)
class Image {
public:
    Image(int N);   // Constructor imagen
    Image(float *p, int N); // Indexa contenido al vector p
    ~Image();
    void loadImageFromTxt(string filename);
    void saveImageToTxt(string filename);
    float getPixel(int i, int j);   // Obtiene el pixel segun las coordenadas i,j
    void setPixel(int i, int j, float value);   // Setea un valor al pixel de coordenadas i,j
    int getN(); // Obtiene dimensiones de la imagen (NxN)
private:
    int N;  // Tamaño imagen
    float *image;   // arreglo de imagen
};
#endif