// Prueba de la funcion contar_unos() con la matriz de 5x5
// Prueba de la funcion Juego de la vida con la matriz de 5x5
// El juego de la vida funciona como debe! ✅💯


#include <stdio.h>
#include <stdlib.h>

int contar_unos(int matriz[5][5], int i, int j,int i_m, int j_m);
void print_matriz(int matriz[5][5], int i_m, int j_m);
void Juego_de_la_vida(int matriz[5][5], int i_m, int j_m, int iteraciones);

int main(){
    //Partiremos creando una matriz de 5x5 con 1's y 0's aleatorios
    int i_m = 5; //cantidad de filas
    int j_m = 5; //cantidad de columnas

    int i,j,matriz[i_m][j_m];

    //Llenamos la matriz con valores aleatorios
    for(i=0;i<i_m;i++){
        for(j=0;j<j_m;j++){
            matriz[i][j]=rand()%2;
        }
    }

    //Mostramos la matriz
    print_matriz(matriz,i_m,j_m);
    

    //Accedemos a los valores que se encuentran alrededor de la matriz
    /* comprobamos que calcule bien los valores alrededor de la matriz
    for(i = 0; i<i_m; i++){
        for(j = 0; j<j_m; j++){
            printf("Posicion [%d][%d]->[%d]\n",i,j,matriz[i][j]);
            printf("Cantidad de 1's alrededor: %d\n",contar_unos(matriz,i,j,i_m,j_m));
        }
    }
    */

    
    Juego_de_la_vida(matriz,i_m,j_m,3);

    return 0;
}

// Funcion que simula el ~juego de la vida~ en una matriz
    // Reglas:
    // 1. Si una celda esta muerta: con 3 vecinos vivos, revive
    // 2. Si una celda esta viva: con 2 o 3 vecinos vivos, sobrevive
    // 3. En cualquier otro caso, muere
    
// Funciona como debe! ✅💯
void Juego_de_la_vida(int matriz[5][5], int i_m, int j_m, int iteraciones){
    int vecinos_vivos = 0;
    for (int k = 0; k<iteraciones; k++){
        for(int i = 0; i<i_m; i++){
            for(int j = 0; j<j_m; j++){
                //if(matriz[i][j]==0){
                    vecinos_vivos = contar_unos(matriz,i,j,i_m,j_m);
                        if(vecinos_vivos==3){ // si hay 3 vecinos Vive
                        matriz[i][j]=1;
                    }
                    else if(vecinos_vivos>3 || vecinos_vivos<2){ // si hay mas de 3 o menos de 2 vecinos Muere
                        matriz[i][j]=0;
                    }
                    // Si no cumple ninguna de las condiciones anteriores, se mantiene igual

            }
        }
        //}
        print_matriz(matriz,i_m,j_m);
    }
}



// Funcion que retorna la cantidad de 1's que hay en la matriz al rededor de la posicion [i][j]
// @variables i y j son las posiciones de la matriz que se quieren evaluar
// @variables i_m y j_m son las dimensiones de la matriz
// @return retorna la cantidad de 1's que hay al rededor de la posicion [i][j]
// Tiene tantos condicionales para no salirse de los limites de la matriz, evalua las esquinas, bordes y centro
// y cada caso tiene sus propias condiciones

// 🆗 funciona como debe! 💯✅
int contar_unos(int matriz[5][5], int i, int j,int i_m, int j_m){ //✅
    int contador = 0;
    
    if(i==0 & j==0){ // Esquina superior izquierda
        contador += matriz[i][j+1]+ //Fila actual
        matriz[i+1][j]+matriz[i+1][j+1]; //Fila de abajo

    }
    
    else if(i==0 & j==j_m-1){ // Esquina superior derecha
        contador += matriz[i][j-1]+ //Fila actual
        matriz[i+1][j-1]+matriz[i+1][j]; //Fila de abajo
        
    }
    
    else if(i==i_m-1 & j==0){ // Esquina inferior izquierda
        contador +=matriz[i-1][j]+matriz[i-1][j+1]+ //Fila de arriba
        matriz[i][j+1]; //Fila actual
        
    }
    
    else if(i==i_m-1 & j==j_m-1){// Esquina inferior derecha
        contador += matriz[i-1][j-1]+matriz[i-1][j]+ //Fila de arriba
        matriz[i][j-1]; //Fila actual
        
    }

    // ####Bordes####
    else if(i==0){
        contador += matriz[i][j-1]+matriz[i][j+1]+ //Fila actual
        matriz[i+1][j-1]+matriz[i+1][j]+matriz[i+1][j+1]; //Fila de abajo
         
    }
    else if (j==0){
        contador +=matriz[i-1][j]+matriz[i-1][j+1]+ //Fila de arriba
        matriz[i][j+1]+ //Fila actual
        matriz[i+1][j]+matriz[i+1][j+1]; //Fila de abajo
            
    }
    else if(i==i_m-1){
        contador +=matriz[i-1][j-1]+matriz[i-1][j]+matriz[i-1][j+1]+ //Fila de arriba
        matriz[i][j-1]+matriz[i][j+1]; //Fila actual
        
    }
    else if (j==j_m-1){
        contador += matriz[i-1][j-1]+matriz[i-1][j]+ //Fila de arriba
        matriz[i][j-1]+ //Fila actual
        matriz[i+1][j-1]+matriz[i+1][j]; //Fila de abajo
        
    }
    
    // ####Centro####
    else{
        contador += matriz[i-1][j-1]+matriz[i-1][j]+matriz[i-1][j+1]+ //Fila de arriba 
        matriz[i][j-1]+matriz[i][j+1]+ //Fila actual
        matriz[i+1][j-1]+matriz[i+1][j]+matriz[i+1][j+1]; //Fila de abajo
     
    }
   
    return contador;
}


void print_matriz(int matriz[5][5], int i_m, int j_m){
    int i,j;
    for(i = 0; i<i_m; i++){
        printf("| ");
        for(j = 0; j<j_m; j++){
            printf("%d ",matriz[i][j]);
        }
        printf(" |\n");
    }
    printf("---------------\n");
}
