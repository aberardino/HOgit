#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//defino y declaro la función llenar
void llenar(int *red,int m, int n,float proba) {
 int i;
 for(i=0;i<n*m;i=i+1){
  if(red[i]<proba){
   red[i]=0;
  }
  else {
   red[i]=1;
  }
 }
}
//defino y declaro la función imprimir
void imprimir(int *red,int m,int n) {
 int i,j;
 for(j=0;j<n;j=j+1){
  for(i=0;i<m;i=i+1){
   printf("%d ",red[i+j*m]);
  }
  printf("\n");
 }
} 

//empieza la función main
int main(){
 int i,m,n;
 int *red;
 float proba;

 m = 10; //cantidad de filas de la red
 n = 10; //cantdad de columnas de la red
 proba = 50.0; //la probabilidad de llenar la red
 red = malloc(m*n*sizeof(float));
 
 /*le asigno números aleatorios a la red del 0 al 100 con la misma semilla
 for(i=0;i<m*n;i=i+1){
  red[i]=rand()%100;
 }
 */
 
 //le asigno números aleatorios a la red del 0 al 100 con distinta semilla
 srand(time(NULL));
 for(i=0;i<m*n;i=i+1){
  red[i]=rand()%100;
 }
  

 llenar(red,m,n,proba);
 imprimir(red,m,n);

 return 0;
 free(red);
}
