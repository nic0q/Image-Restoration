#include "Image.h"

int main() {
  int N = 256;  // dimensiones imagen: 256x256
  Image *I=new Image(N);  // creacion del objeto imagen
  I->loadImageFromTxt("image.txt"); // Se carga la imagen original
  cout << "Se carga la imagen" << endl;
  I->saveImageToTxt("image_originalTest.txt");  // Se guarda la imagen original
  cout << "Se guarda la imagen" << endl;
  cout << "se obtiene el pixel " << I->getPixel(4,3) << endl;
  I->setPixel(4,3,10.2);  // se setea un valor al pixel 4,3
  cout << "se setea el pixel [4,3] a " << I->getPixel(4,3) << endl;
  cout << "se obtiene la dimension de la imagen " << I->getN() << endl;
}