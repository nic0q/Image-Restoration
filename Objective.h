#ifndef OBJECTIVE_H
#define OBJECTIVE_H

#include "ImageProcessor.h"

class Objective {
  public:
    Objective(Image *I_corrupted, ImageProcessor *processor);
    Objective();
    ~Objective();
    virtual float F(float* p);   // Funcion que calcula el valor de la funcion objetivo
    virtual void dF(float* p, float* xi); // Calcula el gradiente de la funcion anterior F
  private:
    Image *I_corrupted; // Imagen corrupt
    Image *ImagesubConv;    // Imagen convolucionada y restada con el kernel (ver método dF)
    ImageProcessor *processor;  // Procesador de la imagen
};
#endif