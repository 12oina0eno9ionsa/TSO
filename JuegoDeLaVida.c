// Prueba de la funcion contar_unos() con la matriz de 5x5
// Prueba de la funcion Juego de la vida con la matriz de 5x5
// El juego de la vida funciona como debe! ✅💯


#include <stdio.h>
#include <stdlib.h>
// Incluido por DRZK
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <curses.h>

#define ROWS 40
#define COLUMNS 120
// Incluido por DRZK

int contar_unos(char *tablero, int i, int j,);
void print_matriz(char *tablero)
void Juego_de_la_vida(char *tablero, int iteraciones)

int main(int argc, char *argv[]) {
    // Manejar argumento de entrada N para el número de iteraciones
    int iteraciones;
    if (argc != 2) {
        printf("Se escribio: %s <iteraciones>\n Error :P", argv[0]);
        exit(EXIT_FAILURE);
    } else {
        iteraciones = atoi(argv[1]);
    }

    // Crear y adjuntar memoria compartida
    key_t key = ftok(".", 'M');
    int shmid = shmget(key, sizeof(char) * ROWS * COLUMNS, IPC_CREAT | 0666);
    char *tablero = (char *)shmat(shmid, NULL, 0);

    // Llenar la matriz en la memoria compartida
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            // Calcular el índice en el bloque de memoria compartida
            int index = i * COLUMNS + j;
            // Generar un valor aleatorio de 0 o 1 y asignarlo al elemento de la matriz ubicada en memoria compartida
            tablero[index] = rand() % 2;
        }
    }

    // Crear procesos hijos
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == 0) {
        Juego_de_la_vida(tablero, iteraciones);
    } else if (pid1 > 0) {
        pid2 = fork();
        if (pid2 == 0) {
            mostrar_tablero(tablero);
        }
    }

    // Esperar a que ambos hijos terminen, si no, o zombie o huerfano (jugador troll de lolcito)
    wait(NULL);
    wait(NULL);

    // Liberar memoria compartida
    shmdt(tablero);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

// Funcion que simula el ~juego de la vida~ en una matriz
    // Reglas:
    // 1. Si una celda esta muerta: con 3 vecinos vivos, revive
    // 2. Si una celda esta viva: con 2 o 3 vecinos vivos, sobrevive
    // 3. En cualquier otro caso, muere
    
// Funciona como debe! ✅💯
void Juego_de_la_vida(char *tablero, int iteraciones) {
    int vecinos_vivos = 0;

    for (int k = 0; k < iteraciones; k++) {
        // Calcular el nuevo estado del tablero
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                int indice = i * COLUMNS + j; // Calcular el índice correspondiente en el tablero unidimensional
                vecinos_vivos = contar_unos(tablero, i, j);
                if (vecinos_vivos == 3) {
                    tablero[indice] = '1'; // Si hay 3 vecinos, la celda nace
                }
                else if (vecinos_vivos < 2 || vecinos_vivos > 3) {
                    tablero[indice] = '0'; // Si tiene menos de 2 o más de 3 vecinos, muere
                }
                //Por tanto si tiene 2 o 3 (exactamente), se mantiene viva, es decir, no se modifica
            }
        }
    }
}

// Funcion que retorna la cantidad de 1's que hay en la matriz al rededor de la posicion [i][j]
// @variables i y j son las posiciones de la matriz que se quieren evaluar
// @variables i_m y j_m son las dimensiones de la matriz
// @return retorna la cantidad de 1's que hay al rededor de la posicion [i][j]
// Tiene tantos condicionales para no salirse de los limites de la matriz, evalua las esquinas, bordes y centro
// y cada caso tiene sus propias condiciones

// 🆗 funciona como debe! 💯✅
int contar_unos(char *tablero, int i, int j){ //✅
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


void print_matriz(char *tablero) {
    for (int i = 0; i < ROWS; i++) {
        printf("| ");
        for (int j = 0; j < COLUMNS; j++) {
            int indice = i * COLUMNS + j; // Calcular el índice correspondiente en el tablero
            printf("%c ", tablero[indice]);
        }
        printf(" |\n");
    }
    printf("---------------\n");
}

void mostrar_tablero(char *tablero) {
    initscr(); // Iniciar Ncurses
    curs_set(0); // Ocultar cursor

    // Bucle para mostrar el tablero
    while (1) {
        clear(); // Limpiar la pantalla

        // Recorrer el tablero y mostrar cada celda en la pantalla
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLUMNS; j++) {
                int indice = i * COLUMNS + j;
                mvprintw(i, j, "%c", tablero[indice]);
            }
        }

        refresh(); // Actualizar pantalla

        // Verificar si el usuario presionó la tecla Escape
        if (getch() == 27) {
            break; // Salir del bucle si se presionó la tecla Escape
        }

        sleep(2); // Retardo para visualización (ajustar según sea necesario)
    }

    endwin(); // Terminar Ncurses
}
