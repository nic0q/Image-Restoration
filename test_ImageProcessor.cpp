#include "ImageProcessor.h"

int main() {
  int N = 256;  // dimensiones imagen 256x256
  ImageProcessor *processor=new ImageProcessor(); // creacion del procesador de imagen
  Image * I=new Image(N); // creacion del objeto imagen
  I->loadImageFromTxt("image.txt"); // Se carga la imagen original
  I->saveImageToTxt("image_original.txt");  // Se guarda la imagen original
  Image* corrupted = processor->corrupt(I);  // Se corrompe la imagen original
  corrupted->saveImageToTxt("image_corrupted.txt"); // Se guarda la imagen corrupta
}