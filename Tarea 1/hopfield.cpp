// hopfield.cpp

#include <iostream>
using namespace std;

// initialize the weigth matrix W with the patterns

//llenado del nuevo arreglo con los pesos de los otros arreglos
void weights(int **W, int *x0, int *x1, int *x2, int N)
{
 for (int i=0;i<N;i++)
 
  for (int j=0; j<N; j++)
  {
   W[i][j]=x0[i]*x0[j] + x1[i]*x1[j] + x2[i]*x2[j];
  }

  for (int k=0; k<N; k++)//llenado a 0 la diagonal del arreglo
   W[k][k]=0;
}

//calculation of sum over j of W[i][j]*s[j]
void mul(int **W, int *s, int *h, int N)
{
 for (int i=0;i<N;i++)
 {
  int sum=0;
  for (int j=0;j<N;j++)
  {
   sum+=W[i][j]*s[j];
  }
  h[i]=sum;
 }
} 

//determina si es mayor a cero
int sign(int y)
{
 if (y>0)
  return 1;
 else
  return -1;
}

//evalua los valores dentro de 2 arreglos
int check(int *v1, int *v2, int N)
{
 for(int i=0;i<N;i++)
 {
  if (v1[i] != v2[i])
   return 0;
 }
 return 1;
}

//llenado del arreglo de energia 
int energy(int **W, int *s, int N)
{
 int E=0;
 for (int i=0;i<N;i++)
  for(int j=0;j>N;j++)
   E+=W[i][j]*s[i]*s[j]; //suma de multiplicacion de los arreglos 

 return -E; 
}

int main(void)
{

 int N=40; // cantidad dentro del arreglo
 int *x0= new int[N]; //puntero a un arreglo para la creaciond e un arreglo dinamico
 int *x1= new int[N]; //puntero a un arreglo para la creaciond e un arreglo dinamico
 int *x2= new int[N]; //puntero a un arreglo para la creaciond e un arreglo dinamico


//neado de los 3 arreglos creados
 // pattern 0
x0[0]  = -1; x0[1]  = -1; x0[2]  = 1;  x0[3]  = -1; x0[4]  =-1; 
x0[5]  = -1; x0[6]  =  1; x0[7]  = 1;  x0[8]  = -1; x0[9]  =-1;
x0[10] = -1; x0[11] = -1; x0[12] = 1;  x0[13] = -1; x0[14] =-1; 
x0[15] = -1; x0[16] = -1; x0[17] = 1;  x0[18] = -1; x0[19] =-1; 
x0[20] = -1; x0[21] = -1; x0[22] = 1;  x0[23] = -1; x0[24] =-1; 
x0[25] = -1; x0[26] = -1; x0[27] = 1;  x0[28] = -1; x0[29] =-1; 
x0[30] = -1; x0[31] = -1; x0[32] = 1;  x0[33] = -1; x0[34] =-1; 
x0[35] = -1; x0[36] = -1; x0[37] = -1; x0[38] = -1; x0[39] =-1;


 // pattern 2
x1[0]  = -1; x1[1]  =  1; x1[2]  =  1;  x1[3]  =  1; x1[4]  =-1;
x1[5]  =  1; x1[6]  = -1; x1[7]  = -1;  x1[8]  = -1; x1[9]  = 1;
x1[10] = -1; x1[11] = -1; x1[12] = -1;  x1[13] = -1; x1[14] = 1;
x1[15] = -1; x1[16] = -1; x1[17] =  1;  x1[18] =  1; x1[19] =-1;
x1[20] = -1; x1[21] =  1; x1[22] = -1;  x1[23] = -1; x1[24] =-1;
x1[25] =  1; x1[26] = -1; x1[27] = -1;  x1[28] = -1; x1[29] =-1;
x1[30] =  1; x1[31] =  1; x1[32] =  1;  x1[33] =  1; x1[34] = 1;
x1[35] = -1; x1[36] = -1; x1[37] = -1;  x1[38] = -1; x1[39] =-1;



 // pattern 3
x2[0]  =  1; x2[1]  = -1; x2[2]  = -1;  x2[3]  =  1; x2[4]  =-1;
x2[5]  =  1; x2[6]  = -1; x2[7]  = -1;  x2[8]  =  1; x2[9]  =-1;
x2[10] =  1; x2[11] = -1; x2[12] = -1;  x2[13] =  1; x2[14] =-1;
x2[15] =  1; x2[16] =  1; x2[17] =  1;  x2[18] =  1; x2[19] = 1;
x2[20] = -1; x2[21] = -1; x2[22] = -1;  x2[23] =  1; x2[24] =-1;
x2[25] = -1; x2[26] = -1; x2[27] = -1;  x2[28] =  1; x2[29] =-1;
x2[30] = -1; x2[31] = -1; x2[32] = -1;  x2[33] =  1; x2[34] =-1;
x2[35] = -1; x2[36] = -1; x2[37] = -1;  x2[38] = -1; x2[39] =-1;

// allocating memory for W
// Localizaciond e w en la memoria dinamicamebte

int **W=NULL;
W = new int *[N];
for(int i=0; i<N;i++)
{
 W[i]=new int [N];
}

//llenado del nuevo arreglo
for(int i=0;i<N;i++)
 for(int j=0;j<N;j++)
  W[i][j]=0;

weights(W, x0, x1, x2, N);
//creacion de un nuevo arreglo
int *s= new int[N];

// start configuration
s[0]  =  1; s[1]  =  1; s[2]  = -1;  s[3]  =  1; s[4]  =-1;
s[5]  = -1; s[6]  =  1; s[7]  = -1;  s[8]  =  1; s[9]  = 1;
s[10] =  1; s[11] = -1; s[12] = -1;  s[13] =  1; s[14] =-1;
s[15] =  1; s[16] = -1; s[17] =  1;  s[18] =  1; s[19] = 1;
s[20] = -1; s[21] = -1; s[22] = -1;  s[23] = -1; s[24] =-1;
s[25] = -1; s[26] = -1; s[27] =  1;  s[28] =  1; s[29] =-1;
s[30] = -1; s[31] = -1; s[32] = -1;  s[33] =  1; s[34] =-1;
s[35] = -1; s[36] = -1; s[37] = -1;  s[38] = -1; s[39] =-1;

//enegia utilizada en todas las matrices
int E=energy(W,s,N);
cout << "energy of initial configuration: " << E << endl;

//creacion de nuevo arreglo
int *h= new int[N];
//llenado edl nuevo arreglo a 0
for(int p=0;p<N;p++)
{
 h[p]=0;
}


//creacion dinamica de otro arreglo
int *s1=new int[N];
//se copia el arreglo s en el nuevo arreglo
for(int i=0;i<N;i++)
{
 s1[i]=s[i];
}

//se crean variables de resultaod y cuenta
int result,count;
count=0;


do
{
 for(int i=0;i<N;i++)
 {
  s1[i]=s[i];
 }
 
 mul(W,s,h,N);
 for(int j=0;j<N;j++)
 {
  if (h[j]!=0)
  {
   s[j]=sign(h[j]);
  }
 
 if (h[j]==0)
 {
  s[j]=s1[j];
 }

 }
 result=check(s, s1, N);
 count++;
 cout << "count="<< count << endl;

//mientras el contador sea menor a 100 y el resutado sea dif a 1 
} while ((count<100) && (result!=1));

cout << "number of iterations:"<< count << endl;

for (int i=0;i<N;i++)
{
 cout << "s[" << i << "]=" << s[i] << " "; // end configuration
 if ( ( (i+1) % 5) == 0)
 {
  cout << endl;
 }

}

E =energy(W,s,N);
cout << "energy of end configuration:"<< E << endl;

delete[] x0; delete[] x1; delete[] x2;
delete[] s; delete[] s1; delete[] h;
for (int i=0; i<N; i++)
{
 delete[] W[i];
}
delete[] W;

return 0;
}
