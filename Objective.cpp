#include "Objective.h"

Objective::Objective(Image *I_corrupted, ImageProcessor *processor) {
    this->I_corrupted = I_corrupted;
    this->processor = processor;
}
Objective::Objective(){
}
Objective::~Objective(){
}
// Funcion que calcula el valor de la funcion objetivo
// I: arreglo de flotantes
// O: valor funcion minimizada
float Objective::F(float* p){
    float f = 0;
    int N = I_corrupted->getN();    // Tamaño de la imagen a corromper    
    Image *I=new Image(p,N);    // I: imagen del mapache corrupta
    Image *newImage;    // Nueva Imagen
    Image *kernel = new Image(KERNEL_SIZE); // Kernel
    kernel = processor->setAllPixel(kernel, 1.0/(KERNEL_SIZE*KERNEL_SIZE)); // creación del kernel
    newImage = processor->convolve(kernel,I);   // convolución kernel Imagen Corrupta
    newImage = processor->subtract(newImage,I_corrupted); // resta de K*p - Icorrupted
    ImagesubConv = newImage;
    for(int i = 0; i < N; i++){ 
        for(int j = 0; j < N; j++){
            f += newImage->getPixel(i, j) * newImage->getPixel(i, j);   // suma de los cuadrados de los pixeles de la imagen
        }
    }
    return f * 0.5;
}
// Funcion que calcula el gradiente de la funcion anterior F [gradiente = K*(K*p-Icorrupted)], es almacenado en el vector xi
// I: vector p imagen, vector xi
// O: void
void Objective::dF(float* p, float* xi){
    int N = I_corrupted->getN();    // Obtiene dimensiones de la imagen corrupta
    Image *I=new Image(p,N);    // Crea una nueva imagen con el arreglo p y dimensiones N
    Image *newImage;
    Image *kernel = new Image(KERNEL_SIZE); // Crea el kernel
    kernel = processor->setAllPixel(kernel, 1.0/(KERNEL_SIZE*KERNEL_SIZE)); // Setea el kernel con un valor cte
    newImage = ImagesubConv;    // Image con substraccion y convolucion
    newImage = processor->convolve(kernel,newImage);    // Convoluciona la imagen y el kernel
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            xi[i*N+j] = newImage->getPixel(i, j);   // Obtiene los pixeles de la nueva imagen
        }
    }
}