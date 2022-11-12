# Cómo compilar y ejecutar las soluciones
## Ejercicios 1 al 3:
En una terminal situada en el directorio donde se encuentra el archivo `ej<NUMERO-DE-EJ>.cpp` ejecutar:

    g++ ej<NUMERO-DE-EJ>.cpp -o ejercicio<NUMERO-DE-EJ>
    ./ejercicio<NUMERO-DE-EJ>

Luego introducir por consola el input deseado, con el formato establecido por el enunciado del problema de UVa correspondiente:

- Ejercicio 1: [12363 _"Hedge Mazes"_](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3785)
- Ejercicio 2: [1265 _"Tour Belt"_](https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3706)
- Ejercicio 3: [1233 _"Usher"_](https://onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=3674)

## Ejercicio 4:
Análogamente, para el ejercicio 4 las intrucciones de compilación son similares:

    g++ ej4.cpp -o ejercicio4
    ./ejercicio4

El input debe ingresarse por consola de acuerdo a lo indicado en el enunciado del Trabajo Práctico provisto por la cátedra:

> El input comienza con una línea que contiene la cantidad T de casos de tests. Luego siguen los T casos. La primera línea de cada caso contiene 3 enteros k, n y m, separados por espacios, indicando respectivamente la cantidad de ecuaciones, la cantidad de variables, y el tamaño del
conjunto D. 
> Las siguientes k líneas describen, cada una, una de las ecuaciones del sistema. Estas son descriptas por 3 números enteros a, b y c, donde a y b denotan índices de variables. Las variables están numeradas de 1 a n, por lo que 1 ≤ a, b ≤ n. Los 3 números a, b y c en ese orden representan la ecuación xa − xb ≤ c. 
> Después se sigue una línea con m números enteros d1 . . . dm separados por espacios y ordenados de menor a mayor. Estos representan al conjunto D


Adicionalmente se incluye un archivo CMake `CMakeLists.txt` por si llegara a ser de utilidad.
