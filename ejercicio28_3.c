#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//declaro las funciones que voy a usar
void llenar(int *red,int n,float prob);
void imprimir(int *red,int n);
int  hoshen(int *red,int n);
int  actualizar(int *red,int *clase,int s,int frag);
void etiqueta_falsa(int *red,int *clase,int s1,int s2);
void corregir_etiqueta(int *red,int *clase,int n);
int percola(int *red,int n);


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
 hoshen(red,n);
 printf("\n");
 imprimir(red,n);
 percola(red,n);

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
   if(red[i*n+j]>9){
    printf("%d ",red[i*n+j]);
   }
   else{
    printf("%d  ",red[i*n+j]);
   }
  }
  printf("\n");
 }
}

//defino la función hoshen
  /*
    Esta funcion implementa en algoritmo de Hoshen-Kopelman.
    Recibe el puntero que apunta a la red y asigna etiquetas 
    a cada fragmento de red.
  */ 
int hoshen(int *red,int n) {

  int i,j,k,s1,s2,frag;
  int *clase;

  frag=0;
  
  clase=(int *)malloc(n*n*sizeof(int));

  for(k=0;k<n*n;k++) *(clase+k)=frag;
  
  // primer elemento de la red

  s1=0;
  frag=1;
  if (*red) frag=actualizar(red,clase,s1,frag);
  
  // primera fila de la red

  for(i=1;i<n;i++) 
    {
      if (*(red+i)) 
         {
           s1=*(red+i-1);  
           frag=actualizar(red+i,clase,s1,frag);
         }
    }
  

  // el resto de las filas 

  for(i=n;i<n*n;i=i+n)
    {

      // primer elemento de cada fila

      if (*(red+i)) 
         {
           s1=*(red+i-n); 
           frag=actualizar(red+i,clase,s1,frag);
         }

      for(j=1;j<n;j++)
	if (*(red+i+j))
	  {
	    s1=*(red+i+j-1); 
            s2=*(red+i+j-n);

	    if (s1*s2>0)
	      {
		etiqueta_falsa(red+i+j,clase,s1,s2);
	      }
	    else 
	      { if (s1!=0) frag=actualizar(red+i+j,clase,s1,frag);
	        else       frag=actualizar(red+i+j,clase,s2,frag);
	      }
	  }
    }


  corregir_etiqueta(red,clase,n);

  free(clase);

  return 0;
}

//defino la función actualizar
int  actualizar(int *red,int *clase,int s,int frag) {
 /*
 se fija cual es el valor de s. si es negativo busca la etiqueta verdadera y se la asigna a la posicion actual.
 Si s es cero tengo que asignar una etiqueta nueva, para eso tengo que aumentar frag en 1,signar esa etiqueta
 a la posicion y devolver el nuevo valor de frag. 
 Si asgnaste una etiqueta nueva tiene que actualizar el vector clase con esanueva etiqueta
*/
  if(s>0){ //si el vecino no es 0
   while(clase[s]<0) { //busco la etiqueta verdadera de s
    s=-clase[s];
   }
   *red=s; //le doy la etiqueta verdadera a red
   clase[s]=s; //le asigno la etiqueta verdadera a clase
  }
 
  if(s==0) { //si los dos vecinos son 0, tengo que poner una etiqueta nueva
   frag++;
   *red=frag;
   clase[frag]=frag;
  } 
  return frag; //devuelve frag para que actualice el valor, con clase no hace falta porque son posiciones de memoria que se llenan con algo, queda guardado
 }

//defino la función etiqueta_falsa
void etiqueta_falsa(int *red,int *clase,int s1,int s2) {
  while(clase[s1]<0) { //me fijo cuál es la etiqueta verdadera de s1
   s1=-clase[s1];
  }
  while(clase[s2]<0) { //me fijo cuál es la etiqueta verdadera de s2
   s2=-clase[s2];
  }
  if(s1<s2) { //si la etiqueta de s1 es menor que la de s2 le pongo la de s1 a la red
   clase[s2]=-s1;
   clase[s1]=s1;
   *red=s1;
  }
  else{ // si no le pongo la de s2
  clase[s1]=-s2;
  clase[s2]=s2;
  *red=s2;
  }
}

//defino la función corregir_etiqueta
void corregir_etiqueta(int *red,int *clase,int n) {
 int i,s;
 for(i=0;i<n*n;i++) {
  s=red[i];
  while(clase[s]<0) {
   s=-clase[s];
  }
  red[i]=s;
 }
}

//defino la función percola
int percola(int *red,int n) {
 /*
 Creo dos vectores para la primer y ultima fila de la red. Me fijo qué
 clusters están presentes en la primer fila y le pongo un 1 al nuevo 
 vector en la posición del clúster. Ej (fila 02204070 -> vector 0101001)
 Multiplico los dos vectores y me fijo si tienen algún 1, si es así entonces
 la red percoló y la función devuelve un 1, si no, devuelve 0 
 */
 
 int *vecfila1;
 int *vecfila2;
 int j,k,l,s,i,perc,contador; 
 
 perc = 0;
 contador = 0;
 vecfila1=(int *)malloc(n*n/2*sizeof(int));
 vecfila2=(int *)malloc(n*n/2*sizeof(int));

 for(k=0;k<n*n/2;k++) {
  *(vecfila1+k)=0;
  *(vecfila2+k)=0;
 }

 for(i=0;i<n;i++) {
  s=red[i];
  if(s>0) vecfila1[s]=1;
 }

 for(i=n*n-n;i<n*n;i++) {
  s=red[i];
  if(s>0) vecfila2[s]=1;
 }
 
 printf("\n");
 for(j=0;j<n*n/2;j++) printf("%d ",vecfila1[j]);
 printf("\n");
 printf("\n");
 for(j=0;j<n*n/2;j++) printf("%d ",vecfila2[j]);
 printf("\n");

 for(l=0;l<n*n/2;l++) {
  contador = contador + vecfila1[l]*vecfila2[l];
 }
 if(contador>0) perc=1;

 printf("\n%d\n\n",perc);

 return perc;
 free(vecfila1);
 free(vecfila2);
}