#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <iostream>
#include <random>
#include "Image.h"
#define KERNEL_SIZE 5
#define SIGMA 0.05
using namespace std;
// Clase que contiene todo lo utilitario correspondiente a las operaciones a realizarse con la imagen
// como add noise (añadir ruido), operaciones aritmeticas con el vector de la imagen (substract: resta, multiply: producto, add: suma)
class ImageProcessor {
public:
    ImageProcessor();
    ~ImageProcessor();
    // Estas funciones generan una nueva imagen
    Image* convolve(Image * Kernel, Image * I); // convolucion entre el kernel y la imagen
    Image* addNoise(Image * I); // añade ruido a la imagen
    Image* corrupt(Image* I);   // corrompe la imagen
    Image* setAllPixel(Image* I, float value);  // setea un valor a todos los pixeles de la imagen
    Image* subtract(Image* I1, Image* I2);  // Subtraccion entre imagenes
    Image* add(Image* I1, Image* I2);   // Adicion entre imagenes
    Image* multiply(float x, Image* I2);    // Producto entre imagenes
};
#endif