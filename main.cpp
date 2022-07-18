#include "Optimizer.h"
#include <ctime>
#include <cmath>
// En el presente main se muestra la comparacion entre la imagen original -> imagen corrupta -> imagen restaurada por el algoritmo implementado
// ejecutar make test_main para ejecutar
int main() {
    int N = 256;    // Tamaño de la matriz
    float ftol = 1e-12; // error relativo   
    int max_it = 100;   // maximas iteraciones
    float *f=new float[N*N];    // matriz
    Image * I_corrupted=new Image(N);   // Objeto imagen
    Image *I_test = new Image(N);
    ImageProcessor *processor=new ImageProcessor(); // creacion del procesador de imagen
    int n = 100;    // Numero de iteraciones
    unsigned t0,t1; // Variables de tiempo
	double time, tp = 0;
	int dif_t;
    for(int i = 0; i < n;i++){
        t0 = clock();
        I_test->loadImageFromTxt("image.txt");
        I_test->saveImageToTxt("image_original.txt");
        I_corrupted =  processor->corrupt(I_test); // Se crea la imagen corrompida
        I_corrupted->saveImageToTxt("image_corrupted.txt");
        Objective *o=new Objective(I_corrupted, new ImageProcessor());  // se crea el Objeto Objective
        Optimizer *optimizer=new Optimizer(o,f,N*N,ftol,max_it);    // Constructor optimizer
        optimizer->frprmn(); // Aplica metodo del gradiente conjugado Fletcher-Reeves
        Image * I_restored = new Image(f, N);   // Se crea objeto imagen para la imagen restaurada
        cout << "------------------ " << i + 1 << " -------------"<< endl;
        t1 = clock();
		time = double(t1-t0) / CLOCKS_PER_SEC;  // Calcula el tiempo
		tp = double(time + tp);
        I_restored->saveImageToTxt("restored.txt"); // Se guarda la imagen restaurada
        cout << i + 1 << ".- " << time <<"[s]"<< endl;
    }
	cout <<"Promedio: "<< tp / n << "[s]" << endl;
}