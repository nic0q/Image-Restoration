#include "Optimizer.h"

Optimizer::Optimizer(Objective *o, float* p, int n, float ftol, int max_it) {
  this->p=p;
  this->func=o;
  this->n=n;
  this->ftol=ftol;
  this->max_it=max_it;
  this->iter=0;
  this->fret=0;
  this->fp=0;
}
Optimizer::~Optimizer() {
  delete []p;
  delete []xicom;
  delete []pcom;
}
// Método del gradiente conjugado en su versión de Fletcher-Reeves.
// I: void
// O: void
void Optimizer::frprmn() {
  int j=0,its=0;
  float gg=0,gam=0,fp=0,dgg=0;
  float *g,*h,*xi;
  this->iter=0;
  this->fret=0;
  this->fp=0;
  g = new float[n]; 
  h = new float[n];
  xi = new float[n];
  fp = func->F(p); // calcula la funcion a minimizar
  func->dF(p,xi); // calcula el gradiente
  // asigna a xi el valor de - el gradiente
  for (j=0; j<n; j++) { // ojo se cambio el rango de los indices
    g[j] = -xi[j];
    xi[j]=h[j]=g[j];
  }
  // for principal hasta un maximo de iteraciones
  for (its=0; its<max_it; its++) { //iterations_limit defined in command line
    // cout << "iteracion: " << its << endl;
    this->iter=its;
    // el vector p, fret se actualiza en el linmin
    //linmin(p,xi,n,fret,func);
    linmin(xi); // Aqui modificamos p para obtener un minimo en la direccion xi 
    cout << "xi: " << xi[0] << " p: " << p[0] << " it: " << its <<  endl;
    for(int i = 0;i  < n;i++){  // Se anulan todos los valores negativos
      if(p[i] < 0){
        p[i] = 0; // Positividad del gradiente proyectado
      }
    }
    // si el error es suficientemente bajo, termina
    if (2.0*fabs(this->fret-fp) <= ftol*(fabs(this->fret)+fabs(fp)+EPS)) {
      FREEALL
      return;
    }
    fp=func->F(p);
    //(*dfunc)(p,xi); // esta funcion asigna en xi el valor del gradiente 
    this->func->dF(p,xi); // se retorna un puntero
    dgg=gg=0.0;
    // parte de la construction de la direccion en que se va a minimizar
    for (j=0; j<n; j++) {
      gg += g[j]*g[j];
      dgg += (xi[j]+g[j])*xi[j];
    }
    // aqui el gradiente se hace 0 entonces estamos en un minimo
    if (gg == 0.0) {
      FREEALL
      return;
    }
    gam=dgg/gg;
    // parte de la direccion en que se va a minimizar
    for (j=0; j<n; j++) {
      g[j] = -xi[j];
      xi[j]=h[j]=g[j]+gam*h[j];
    }
  }
  FREEALL
  return;
}
// Dado una direccion xi, y un vector p n dimensional, restaura p donde la funcion evaluada en p tiene un minimo en la direccion xi a p
// y xi es reemplazado por el vector actual de desplacamiento, (p es desplazado), utilizando los metodos de mnbrak y brent anteriores.
// I: arreglo direccional xi
// O: void
void Optimizer::linmin(float* xi) {
  int j;
  float xx, xmin, fx, fb, fa, bx, ax;
  // ncom = n;
  pcom = new float[n];
  xicom = new float[n];
  for (j = 0; j < n; j++) { // copia los vectores p y xi
    pcom[j] = p[j];
    xicom[j] = xi[j];
  }
  ax = 0.0;
  xx = 1.0;
  mnbrak(&ax, &xx, &bx, &fa, &fx, &fb);
  fret = brent(ax, xx, bx, TOL, &xmin);
  for (j = 0; j < n; j++) {
    xi[j] *= xmin;
    p[j] += xi[j];
  }
  delete [] pcom; // elimina los vectores usados
  delete [] xicom;
}
// Dada una funcion, y dados los puntos iniciales ax y bx, busca direccion cuesta abajo definida por la funcion evaluada en los valores iniciales
// retornando nuevos puntos ax, bx, cx soporte de minimos en la función y también son retornados los valores evaluados en la funcion fa, fb,fc
// I: puntos ax, bx, cx, puntos evaluados en f fa,fb,fc
// O: void
void Optimizer::mnbrak(float* ax, float* bx, float* cx, float* fa, float* fb, float* fc) {
  float ulim, u, r, q, fu, dum;
  if (*fb > *fa) {
    SHFT(dum, *ax, *bx, dum)
    SHFT(dum, *fb, *fa, dum)
  }
  *cx = (*bx) + GOLD * (*bx - *ax);
  *fc = f1dim(*cx);
  while (*fb > *fc) {
    r = (*bx - *ax) * (*fb - *fc);
    q = (*bx - *cx) * (*fb - *fa);
    u = (*bx) - ((*bx - *cx) * q - (*bx - *ax) * r) /(2.0 * SIGN(FMAX(fabs(q - r), TINY), q - r));
    ulim = (*bx) + GLIMIT * (*cx - *bx);
    if ((*bx - u) * (u - *cx) > 0.0) {
      fu = f1dim(u);
      if (fu < *fc) {
        *ax = (*bx);
        *bx = u;
        *fa = (*fb);
        *fb = fu;
        return;
      } else if (fu > *fb) {
        *cx = u;
        *fc = fu;
        return;
      }
      u = (*cx) + GOLD * (*cx - *bx);
      fu = f1dim(u);

    } else if ((*cx - u) * (u - ulim) > 0.0) {
      fu = f1dim(u);
      if (fu < *fc) {
        SHFT(*bx, *cx, u, *cx + GOLD * (*cx - *bx))
        SHFT(*fb, *fc, fu, f1dim(u))
      }
    } else if ((u - ulim) * (ulim - *cx) >= 0.0) {
      u = ulim;
      fu = f1dim(u);
    } else {
      u = (*cx) + GOLD * (*cx - *bx);
      fu = f1dim(u);
    }
    SHFT(*ax, *bx, *cx, u)
    SHFT(*fa, *fb, *fc, fu)
  }
}
// Método brent, dada una función utiliza el metodo de la bisección y de la secante buscando una raiz u un minimo de una función
// I: puntos iniciales (tripleta de absisas): ax, bx, cx, tol: tolerancia, xmin: absisa minima
// O: valor mínimo de la función fx
float Optimizer::brent(float ax, float bx, float cx, float tol,float* xmin) {
  int iter;
  float a, b, d = 0.0,e = 0.0, etemp, fu, fv, fw, fx, p, q, r, tol1, tol2, u, v, w, x,xm;              
  a = (ax < cx ? ax : cx);
  b = (ax > cx ? ax : cx);
  x = w = v = bx;
  fw = fv = fx = f1dim(x);  // cambiar por f1dim
  for (iter = 1; iter <= ITMAX; iter++) {
    xm = 0.5 * (a + b);
    tol2 = 2.0 * (tol1 = tol * fabs(x) + ZEPS);
    if (fabs(x - xm) <= (tol2 - 0.5 * (b - a))) {
      *xmin = x;
      return fx;
    }
    if (fabs(e) > tol1) {
      r = (x - w) * (fx - fv);
      q = (x - v) * (fx - fw);
      p = (x - v) * q - (x - w) * r;
      q = 2.0 * (q - r);
      if (q > 0.0) {
        p = -p;
      }
      q = fabs(q);
      etemp = e;
      e = d;
      if (fabs(p) >= fabs(0.5 * q * etemp) || p <= q * (a - x) ||
          p >= q * (b - x)) {
        d = CGOLD * (e = (x >= xm ? a - x : b - x));
      } else {
        d = p / q;
        u = x + d;
        if (u - a < tol2 || b - u < tol2) {
          d = SIGN(tol1, xm - x);
        }
      }
    } else {
      d = CGOLD * (e = (x >= xm ? a - x : b - x));
    }
    u = (fabs(d) >= tol1 ? x + d : x + SIGN(tol1, d));
    fu = f1dim(u);// f1dim
    if (fu <= fx) {
      if (u >= x) {
        a = x;
      } else {
        b = x;
      }
      SHFT(v, w, x, u)
      SHFT(fv, fw, fx, fu)
    } else {
      if (u < x) {
        a = u;
      } else {
        b = u;
      }
      if (fu <= fw || w == x) {
        v = w;
        w = u;
        fv = fw;
        fw = fu;
      } else if (fu <= fv || v == x || v == w) {
        v = u;
        fv = fu;
      }
    }
  }
  *xmin = x;
  return fx;
}
// wrapper o envoltorio de una función a minizar
// I: flotante x
// O: flotante
float Optimizer::f1dim(float x) {
  int j;
  float f,*xt;
  xt = new float[this->n];
  for (j=0; j<=this->n; j++) {
    xt[j]=pcom[j]+x*xicom[j];
  }
  f = this->func->F(xt); // calcula la funcion a minimizar
  delete[] xt; // Elimina arreglo temporal
  return f; // retorna la funcion minimizada
}
