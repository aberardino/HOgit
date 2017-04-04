#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//declaro las funciones que voy a usar
void llenar(int *red,int n,float prob);
void imprimir(int *red,int n);


//empieza la función main
int main() {
 
 //declaro las variables que voy a usar
 int n;
 int *red;
 float prob;

 //defino las variales que voy a usar
 n = 10; //cantdad de columnas de la red
 prob = 0.5; //la probabilidad de llenar la red
 red = (int *)malloc(n*n*sizeof(int));
  
 //elijo la smilla del rand() variable según el reloj de la pc
 srand(time(NULL));


 llenar(red,n,prob);
 imprimir(red,n);

 return 0;
 free(red);
}


//defino la función llenar
void llenar(int *red,int n,float prob) {
 int i;
 float r;
 for(i=0;i<n*n;i++){
  r=rand()/(float)RAND_MAX; //rand() es un int, RAND_MAX es un int entonces la division si no es entero da 0 por eso hay que aclarar que lo tome como float
  if(r<prob){
   red[i]=0;
  }
  else {
   red[i]=1;
  }
 }
}

//defino la función imprimir
void imprimir(int *red,int n) {
 int i,j;
 for(i=0;i<n;i++){
  for(j=0;j<n;j++){
   printf("%d ",red[i*n+j]);
  }
  printf("\n");
 }
}

