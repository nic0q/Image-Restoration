#include "Image.h"

// Constructor de la clase Image
// I: Dimension
// O: void
Image::Image(int N) {
    this->N = N;
    image = new float[N * N];
}
// Indexa el contenido de la imagen al arreglo p
// I: p: Arreglo de pixeles, Dimension imagen
// O: void
Image::Image(float *p, int N) {
    this->N = N;
    image = new float[N * N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            image[i * N + j] = p[i * N + j];
        }
    }
}
Image::~Image() {
    delete[] image;
}
// Carga la imagen en formato txt a partir del nombre del archivo
// I: Nombre del archivo (.txt)
// O: void
void Image::loadImageFromTxt(string filename) {
    ifstream infile;
    infile.open(filename);
    if (!infile) {
        cout << "Error opening file" << endl;
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            infile >> image[i * N + j];
        }
    }
    infile.close();
}
// Guarda la imagen en formato txt
// I: Nombre del archivo (.txt)
// O: void
void Image::saveImageToTxt(string filename) {
    ofstream outfile;
    outfile.open(filename);
    if (!outfile) {
        cout << "Error opening file" << endl;
        exit(1);
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            outfile << image[i * N + j] << endl;
        }
    }
    outfile.close();
}
// Obtiene un pixel a partir de sus coordenadas (matriz)
// I: Coord1, Coord2
// O: valor de pixel en la matriz imagen
float Image::getPixel(int i, int j) {
    return image[i * N + j];
}
// Coloca un nuevo pixel en la matriz a partir de sus coordenadas(matriz)
// I: Coord1, Coord2, valor
// O: void
void Image::setPixel(int i, int j, float value) {
    image[i * N + j] = value;
}
// Obtiene la dimension de la imagen cuadrada (mismo ancho y alto)
// I: void
// O: valor de N
int Image::getN() {
    return N;
}