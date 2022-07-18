#include "Objective.h"
#include "Optimizer.h"
using namespace std;

// En la presenta clase se realiza una herencia virtual para sobreescribir los metodos df y F de la clase Objective
// Los cuales testearan el algoritmo de restauracion frprmn sin cargar una imagen sino, solo con un arreglo de flotantes.
class test_Optimizer : public Objective {
  private:
    int n;  // Tamaño n
  public:
    test_Optimizer(int n) {
      this->n = n;
    }
    // Funcion que calcula el valor de la funcion objetivo
    // I: arreglo de flotantes
    // O: valor funcion minimizada
    virtual float F(float x[]) {  // Funcion a minimizar
      float r=0.5;
      for(int i=1; i<n+1; i++) {
        r=r+0.5*(x[i]-i)*(x[i]-i)/(i+1);
      }
      return r;
    }
    // Funcion que calcula el gradiente de la funcion anterior F [gradiente = K*(K*p-Icorrupted)], es almacenado en el vector xi
    // I: vector p imagen, vector xi
    // O: void
    virtual void dF(float x[], float xi[]) {  // Gradiente de F
      for(int i=1; i<n+1; i++) {
        xi[i]=(x[i]-i)/(i+1);
      }
    }
};
int main() {
  int N = 10; // numero de iteraciones realizadas
  float ftol = 1e-12; // tolerancia relativa con la cual termina
  int max_it = 100; // maximo numero de iteraciones
  float *f=new float[N*N];  // vector de tamaño n*n donde se guarda la imagen restaurada
  Objective *o=new test_Optimizer(N*N); 
  Optimizer *optimizer=new Optimizer(o,f,N*N,ftol,max_it);
  optimizer->frprmn();  // Aplica metodo del gradiente conjugado Fletcher-Reeves
  for(int i = 0; i < N*N;i++){
    cout << f[i] << endl;  // Se muestra el arreglo con la imagen restarada por el metodo anterior
  }
}