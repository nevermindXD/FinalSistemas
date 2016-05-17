
#include <iostream>
#include <cstdlib>
#include <ctime>    // for srand, rand
#include <cmath>    // for cos, sin, pow
using namespace std;

// función de evalucion donde el máximo será encontrado
double f(double x){
 return cos(x) - sin(2*x); // Se devuelve como resultado la expresión evaluada
}

//función de evaluación de vlaor individual
double f_value(double (*func)(double), int* arr, int& N, double a,double b)
{
 double res;
 double m = 0.0;
 for(int j=0;j<N;j++)
 {
  double k = j;
  m+= arr[N-j-1]*pow(2.0,k);
 }
 double x = a + m*(b-a)/(pow(2.0,N)-1.0);
 res = func(x);
 return res;
}

// x_value en maximo global
double x_value(int* arr, int& N,double a,double b)
{
 double m = 0.0;
 for(int j=0;j<N;j++)
 {
  double k = j;
  m += arr[N-j-1]*pow(2.0,k);
 }
 double x = a + m*(b-a)/(pow(2.0,N)-1.0);
 return x;
}

// Establce de manera aleatoria la población dentro de la granja
void setup(int** farm,int M, int N)
{
 srand((unsigned long) time(NULL));
 for(int j=0;j<M;j++)
  for(int k=0;k<N; k++)
   farm[j][k] = rand()%2;
}

// Cruza dos individuos
void crossings(int** farm, int& M, int& N, double &a, double& b)
{
 int K = 2;
 int** temp = new int* [K];
 for(int i=0;i<K;i++)
  temp[i] = new int[N];

 double res[4];
 int r1 = rand()%M;
 int r2 = rand()%M;
 // Este random devuelve un valor entre 0 y 1 menor que este parametro
 while(r2 == r1)
  r2 = rand()%M;
 res[0] = f_value(f, farm[r1], N, a, b);
 res[1] = f_value(f, farm[r2], N, a, b);

//Se guaradn em una arreglo temporal los valores
for(int j=0;j<N;j++)
{
 temp[0][j] = farm[r1] [j] ;
 temp[1][j] = farm[r2] [j] ;
}

 int r3 = rand()%(N-2) + 1;
 for(int j=r3;j<N;j++)
 {
  temp[0][j] = farm[r2][j];
  temp[1][j] = farm[r1][j] ;
 }
  res[2] = f_value(f ,temp[0] ,N,a,b);
  res[3] = f_value(f ,temp[1] ,N,a,b);
  if(res[2] > res[0])
  {
   for(int j=0;j<N;j++)
    farm[r1] [j] = temp[0] [j] ;
    res[0] = res [2] ;
  }

  if(res[3] >res[1])
  {
   for(int j=0;j<N;j++)
    farm[r2][j] = temp[1] [j] ;
   res[1] =res[3];
  }

  for(int j=0;j<K;j++)
   delete[] temp[j] ;
   delete[] temp;
}

// Funcion en la cual ocurre una mutuación, para un individuo

void mutate(int** farm, int& M, int& N, double& a,double& b)
{
  double res[2];
  int r4=rand()%N;
  int r1=rand()%M;
  res[0] = f_value(f ,farm[r1] ,N,a,b);
  int v1 = farm[r1] [r4];
    
// REvisa que la posición tenga un individuo para entonces realizar la openacion en la grana
  if(v1 == 0) farm[r1][r4] = 1;
  if(v1 == 1) farm[r1][r4] = 0;

//Funcion que devuelve su valor en individual
  double a1 = f_value(f, farm[r1], N,a,b);
  if(a1 < res[0])
   farm[r1][r4] = v1;

  int r5 = rand()%N;
  int r2 = rand()%M;
  res[1] = f_value(f, farm[r2] ,N,a,b);
  int v2 = farm[r2][r5];
  if(v2 == 0) farm[r2][r5] = 1;
  if(v2 == 1) farm[r2][r5] = 0;
  double a2 = f_value(f, farm[r2], N,a,b);
  if(a2 < res[1]) farm[r2][r5] = v2;
}

int main(void)
{
 int M = 12; // Población de la granjas actualmente 12
 int N = 10; // llongitud de estrin binario

 int** farm = new int*[M];      // se reserva la memoria para que el apuntador la pueda usar
 for(int i=0;i<M;i++) { farm[i] = new int[N]; }     //Para cada uno se hace lo mismo malloc


 setup(farm,M,N);               //Creación de la granja
 double a=0.0,b=6.28318;        //Intervalo (a , b)

 for(int k=0;k<1000;k++)
 {
  crossings(farm,M,N,a,b);
  mutate(farm,M,N,a,b);
 } //endforloop

 for (int j=0;j<N;j++)
  cout << "farm[l] [" << j << "] = " << farm[1] [j] << endl;
  cout << endl;

 for(int j=0;j<M;j++)
  cout << "fitness f_value[" << j << "] = "
   << f_value(f ,farm[j] ,N,a,b)
   << " " << "x_value[" << j << "]=" << x_value(farm[j] ,N,a,b) << endl;

// Limpieza de memoria
 for(int j=0;j<M;j++)
  delete[] farm[j];
  delete[] farm;
  return 0;
}
