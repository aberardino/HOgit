//defino la red con numeros random entre 0 y 1


int* red;
int n_filas, n_columnas;
red = malloc(n_filas * n_columnas * sizeof(int));


void llenar(int* red,int n_filas,int n_columnas, float proba) { //función que cambia la matriz a binaria
 int i, j;
 for(i=0 , i<n_filas , i=i+1) {
  for(j=0 , j < n_columnas , i=i+1) {
   if( red[i * n_filas + j] <= proba) { //posición i,j de la red
    red[i * n_filas + j]=0;
   }
   else {
    red[i * n_filas + j]=1;
   }
  }
 }
}

void print-red(int* red) {

}


