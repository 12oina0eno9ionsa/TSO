# Documentación respectiva
> [!IMPORTANT]
> Falta:
> - [ ] Resolver Issue: Realizar cálculo para contar los vecinos https://github.com/12oina0eno9ionsa/TSO/issues/1.
## Memoria Compartida
### Clave única para comunicación interproceso
A través de la inicialización de `key_t key`:
```c
key_t key = ftok(".", 'M');
```
Se utiliza la función `ftok()` que genera una clave única para identificar la memoria, para posterior uso de parte de los hijos, es decir, comunicación de interproceso.
| Parametro | Asignado | Descripción |
|----------|----------|----------|
| Path    | `.` | Especifica ruta de archivo existente y accesible, en este caso indica que se usara el directorio actual.|
| ID   | `M`   |Especifica un carácter que identifica de forma exclusiva.|

> [!WARNING]
> Verificar que los parametros son los mismos para todos los procesos que requieran acceso a esta memoria compartida, dado que `key` se corresponde con una clave que tendrá siempre el mismo valor cuando se reciben los mismos argumentos. Esta clave será empleada después en la llamada a la función `shmget`.

### Creación de segmento de memoria compartida

A través de la inicialización de `int shmid`:
```c
int shmid = shmget(key, sizeof(char) * ROWS * COLUMNS, IPC_CREAT | 0666);
```
Se utiliza la función `shmget()` para crear un nuevo segmento de memoria compartida. Utilizando la `key` obtenida en la sección anterior. Se especifica el tamaño del segmento de memoria que se necesita reservar que en este caso, para una matriz de de tamaño `ROWS * COLUMNS`. Por último, `IPC_CREAT` indica al sistema la creación de un nuevo segmento de memoria para utilizar como "_compartida_", por tanto, `066` es el número que indica ciertos permisos de lectura y escritura.

### Apuntar a el segmento de memoria compartida
A través de la inicialización de puntero `char *tablero`:
```c
char *tablero = (char *)shmat(shmid, NULL, 0);
```
Se utiliza esta variable del proceso de manera que "_apunte_" a esa zona de memoria que no pertenece a su espacio de direccionamiento. Para ello, se utiliza la llamada al sistema `shmat` que permite vincular esa zona de memoria al direccionamiento lógico del proceso.

## Llenado de Tablero
Para esta sección se toma la solución propuesta por @Yohanns, y se adapta para el uso directo de la Memoria Compartida.
```c
for (int i = 0; i < ROWS; i++) {
	for (int j = 0; j < COLUMNS; j++) {
    	// Calcular el índice en el bloque de memoria compartida
        int index = i * COLUMNS + j;
        // Generar un valor aleatorio de 0 o 1 y asignarlo al elemento de la matriz ubicada en memoria compartida
        tablero[index] = rand() % 2;
	}
}
```
### ¿Por qué una dimensión?
Recordemos que la memoria se almacena de manera lineal, es decir, de manera unidimensional, por lo tanto si estamos almacenando una matriz en la memoria compartida, los elementos de la primera file se corresponderia a la de las siguientes.

Para nuestro caso, osea la matriz del `Juego de la vida`, que tiene `ROWS` filas y `COLUMNS` columnas, si la almacenamos en la memoria compartida, no podemos acceder directamente a los elementos de la matriz mediante una notación de bi-dimensional (a través de filas-columnas, denotado de manera matemática `matriz[i][j]`). En su lugar, accedemos a los elementos calculando el índice correspondiente en la representación unidimensional del tablero.
```
int index = i * COLUMNS + j;
```
De forma más visual:

|`i`|`j`|COLUMNS|index|matriz[i][j]|
|----------|----------|----------|----------|----------|
|0|0|120|0|matriz[0][0]|
|0|1|120|1|matriz[0][1]|
|...|...|...|...|...|
|0|119|120|119|matriz[0][119]|
|1|0|120|120|matriz[1][0]|
|...|...|...|...|...|

Por lo tanto, para iterar sobre los elementos del tablero almacenado en la memoria compartida, iteramos a lo largo de una sola dimensión, calculando el índice correspondiente en cada iteración de la manera "`i * COLUMNS + j`". 

# Updates (Changelog)
## Release 10/05/2024
Author: Norman (DiamondRZK)
- Se añadió las librerias unistd.h, sys/ipc.h, sys/shm.h, sys/wait.h, curses.h.
- Se definió las variables ROWS y COLUMNS.
- Se realizó la implementación de iteraciones a través de consola, y su correspondiente excepción.
- Se realizó la implementación de memoria compartida.
- Se añadió README.md .
- Se implementó la issue https://github.com/12oina0eno9ionsa/TSO/issues/1 .