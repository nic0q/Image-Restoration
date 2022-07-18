#include "Optimizer.h"
#include "Image.h"
// En el presente main se muestra la comparacion entre la imagen original -> imagen corrupta -> imagen restaurada por el algoritmo implementado
// ejecutar make run para visualizar
int main() {
  int N = 256;    // Tamaño de la matriz
  float ftol = 1e-12; // error relativo   
  int max_it = 100;   // maximas iteraciones
  float *f=new float[N*N];    // matriz
  Image * I_corrupted=new Image(N);   // Objeto imagen 
  I_corrupted->loadImageFromTxt("image_corrupted.txt");   // se carga la imagen corrupta
  Objective *o=new Objective(I_corrupted, new ImageProcessor());  // se 
  Optimizer *optimizer=new Optimizer(o,f,N*N,ftol,max_it);    // Constructor optimizer
  optimizer->frprmn(); // Aplica metodo del gradiente conjugado Fletcher-Reeves
  Image * I_restored = new Image(f, N);   // Se crea objeto imagen para la imagen restaurada
  I_restored->saveImageToTxt("restored.txt"); // Se guarda la imagen restaurada
}