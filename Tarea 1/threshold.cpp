// threshold.cpp

#include <iostream>
#include <cmath> // for exp, tanh

using namespace std;

// determina ls usma de la multiplicacion de un arreglo con otro 
// determina si esta lleno el arreglo
int H(double *w, double *x, int n)
{

 double sum=0.0;
 for (int i=0; i<=n; i++)
 {
   sum += w[i]*x[i];
 }

 if (sum>=0.0)
  return 1;
 else
  return 0;

}

//determina el signo de lo que se encuentra en lso arreglos
int sign(double* w, double *x, int n)
{
 double sum=0.0;
 for (int i=0; i<=n; i++)
 {
  sum += w[i]*x[i];
 }
 
 if (sum>=0.0) return 1;
 else return 0;
}

//detemina el valor unipolar de los arreglos
double unipolar(double *w, double *x, int n)
{
 double lambda = 1.0;
 double sum = 0.0;
 for (int i=0; i<=n; i++)
 {
  sum += w[i]*x[i];
 }
 
 return 1.0/(1.0 + exp(-lambda*sum));
}

//regresa el valor bipolar de los arreglos
double bipolar(double *w, double *x, int n)
{
 double lambda = 1.0;
 double sum = 0.0;
 for (int i=0; i<=n; i++)
 {
  sum += w[i]*x[i];
 }

 return tanh(lambda*sum);
}

int main(void)
{

 int n=5; // length of input vector includes bias
 double theta = 0.5; // threshold
 // memory allocation for weight vector w
 double* w = new double[n];
 w[0] = -theta;
 w[1] = 0.7;
 w[2] = -1.1;
 w[3] = 4.5;
 w[4] = 1.5;

// memory allocation for input vector x
 double* x= new double[n];
 x[0] = 1.0; // bias
 x[1] = 0.7;
 x[2] = 1.2;
 x[3] = 1.5;
 x[4] = -4.5;

 int r1 = H(w,x,n);
 cout << " r1= " << r1 << endl;
 
 int r2 = sign(w,x,n);
 cout << " r2= " << r2 << endl;

 double r3= unipolar(w,x,n);
 cout << " r3=" << r3 << endl;

 double r4=bipolar(w,x,n);
 cout << " r4=" << r4 << endl;

 delete[] w;
 delete[] x;

return 0;
 
  

}

