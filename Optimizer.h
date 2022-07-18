#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include <iostream>
#include <math.h>
#include "Objective.h"
using namespace std;
#define FREEALL delete[] xi; delete[] h; delete[] g;  // deletes para liberar memoria
static float maxarg1,maxarg2;
#define FMAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ?(maxarg1) : (maxarg2)) // maximo entre 2 flotantes
#define EPS 1.0e-10 // rectificar en caso converge a cero
#define ITMAX 100 // iteraciones maximas
#define CGOLD 0.3819660 // cuadrado reciproco golden ratio
#define ZEPS 1.0e-10  // rectificar en caso converge a cero
#define TOL 1.0e-7  // tolerancia
#define GOLD 1.618034 // golden ratio
#define GLIMIT 100.0  // limite de iteraciones de ajuste parabolico
#define TINY 1.0e-20  // valor bajo
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);  // Obtenido de nrutil
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a)) // signo entre 2 numeros
// I: tolerance, array 
// p: arreglo de parámetros, hay que pasarlo con memoria e inicializarlo en la imagen inicial. Aqui deja el resultado este algoritmo.
// ftol: error hasta donde va a llegar el algoritmo (ver while del enunciado)
// iter: numero de iteraciones al cual llegó este algortimo
// fret: mínimo valor de la función a minimizar al cual se llega.
// func: puntero a la funcion que retorna el valor de la funcion a optimizar
// dfunc: puntero a la funcion que retorna el gradiente
// max_it: número de iteraciones a seguir, este algoritmo además implementa un tope.
class Optimizer {
  public:
    Optimizer(Objective *o, float* p, int n, float ftol, int max_it);
    ~Optimizer();
    void frprmn();          
    void linmin(float* xi);
    void mnbrak(float* ax, float* bx, float* cx, float* fa, float* fb, float* fc);                           
    float f1dim(float x);
    float brent(float ax, float bx, float cx, float tol,float* xmin);
    float * getParameter();
  private:
    float *p;   // imagen vector
    int n;      // tamaño del vector
    float ftol; // tolerancia
    int max_it; // maximo de iteraciones
    float *xicom; // vector auxiliar para el contenido de xi
    float *pcom;  // vector auxiliar para el contenido de p
    int iter;   // numero de iteraciones
    float fret; // resultado de aplicar el método brent
    float fp; // funcion a minimizar
    Objective *func;    // funcion objetivo
};
#endif