#include "ImageProcessor.h"

ImageProcessor::ImageProcessor(){
}
ImageProcessor::~ImageProcessor(){
}
// Realiza la convolucion entre una imagen y un kernel o filtro y genera una nueva imagen
// I: Image Image
// O: Image
Image * ImageProcessor::convolve(Image * Kernel, Image * I){
    int N = I->getN();  // Tamaño de la imagen
    int M = (Kernel->getN()-1)/2;   // Tamaño del kernel
    Image* convolved = new Image(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            float sum = 0;
            for (int k = -M; k < M; k++) {
                for (int l = -M; l < M; l++) {
                    if (i + k >= 0 && i + k < N && j + l >= 0 && j + l < N) {
                        sum += I->getPixel(i + k, j + l) * Kernel->getPixel(k + M, l + M);
                    }
                }
            }
            convolved->setPixel(i, j, sum);
        }
    }
    return convolved;
}
// Coloca cada pixel de una iamgen a un valor en específico
// I: Image, valor
// O: Image
Image * ImageProcessor::setAllPixel(Image * I, float value){
    int N = I->getN();
    Image * newImage = new Image(N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            newImage->setPixel(i, j, value);
        }
    }
    return newImage;
}
// Añade ruido a la imagen
// I: Image
// O: Image
Image * ImageProcessor::addNoise(Image * I){
    int N = I->getN();
    Image * newImage = new Image(N);
    random_device rd;
    normal_distribution<float> normal(0, SIGMA);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            newImage->setPixel(i, j, I->getPixel(i, j) + normal(rd));
        }
    }
    return newImage;
}
// Genera una nueva imagen corrupta, realiza la convolucion y el ruido.
// I: Image
// O: Image
Image * ImageProcessor::corrupt(Image * I){
    Image * newImage;
    Image* kernel = new Image(KERNEL_SIZE);
    kernel=setAllPixel(kernel, 1.0/(KERNEL_SIZE*KERNEL_SIZE));
    newImage=convolve(kernel,I);    // convolve
    newImage=addNoise(newImage);    // noise
    return newImage;
}
// Realiza la resta o substraccion entre cada pixel de cada imagen entregada
// I: Image Image
// O: Image
Image * ImageProcessor::subtract(Image * I1, Image * I2){
    int N = I1->getN();
    Image * newImage = new Image(N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            newImage->setPixel(i, j, I1->getPixel(i, j) - I2->getPixel(i, j));
        }
    }
    return newImage;
}
// Realiza la suma o adición entre cada pixel de cada imagen entregada
// I: Image Image
// O: Image
Image * ImageProcessor::add(Image * I1, Image * I2){
    int N = I1->getN();
    Image * newImage = new Image(N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            newImage->setPixel(i, j, I1->getPixel(i, j) + I2->getPixel(i, j));
        }
    }
    return newImage;
}
// Realiza la multiplicacion de cada pixel de la imagen entregada por un flotante ingresado
// I: numeroIngresadoX, Image
// O: Image
Image * ImageProcessor::multiply(float x, Image * I2){
    int N = I2->getN();
    Image * newImage = new Image(N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            newImage->setPixel(i, j, x * I2->getPixel(i, j));
        }
    }
    return newImage;
}