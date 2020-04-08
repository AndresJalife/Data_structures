#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/
int comparar(const void* a, const void* b){
    return (strcmp((char*)a, (char*)b));
}
static void prueba_crear_heap_vacio(){
	printf("\nINICIO DE PRUEBAS HEAP VACIO \n\n");
    heap_t* heap = new_heap(comparar);

    print_test("Prueba heap crear heap vacio", heap);
    print_test("Prueba heap la cantidad de elementos es 0", heap_quantity(heap) == 0);
    print_test("El heap esta vacio", heap_empty(heap));
	print_test("Ver el max en un heap vacio es NULL", !heap_top(heap));
	print_test("Desencolar en un heap vacio es NULL", !heap_dequeue(heap));

    heap_delete(heap, NULL);
}

static void prueba_heap_insertar(){
	
	printf("\nINICIO DE PRUEBAS HEAP INSERTAR \n\n");
	heap_t* heap = new_heap(comparar);

    char *valor1 = "perro";
    char *valor2 = "gato";
    char *valor3 = "vaca";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba heap insertar valor1", heap_enqueue(heap, valor1));
    print_test("Prueba heap la cantidad de elementos es 1", heap_quantity(heap) == 1);
    print_test("Prueba heap desencolar valor1, es valor1", heap_dequeue(heap) == valor1);
    print_test("Prueba heap la cantidad de elementos es 0", heap_quantity(heap) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el heap) */
    print_test("Prueba heap insertar valor2", heap_enqueue(heap, valor2));
    print_test("Prueba heap la cantidad de elementos es 1", heap_quantity(heap) == 1);
    print_test("Prueba heap insertar valor3", heap_enqueue(heap, valor3));
    print_test("Prueba heap la cantidad de elementos es 2", heap_quantity(heap) == 2);

    heap_delete(heap, NULL);
}

static void pruebas_heapsort(){
    printf("\nPRUEBAS DEL HEAPSORT\n\n");

    void** arreglo = malloc(sizeof(char*) * 4);

    arreglo[0] = "a";
    arreglo[1] = "d";
    arreglo[2] = "b";
    arreglo[3] = "c";
    
    heap_sort(arreglo, 4, comparar);
    print_test("El heapsort funciona correctamente", comparar(arreglo[0], "a") == 0 && comparar(arreglo[3], "d") == 0);

    free(arreglo);


}
static void prueba_heap_valor_vacia(){
	printf("\nINICIO DE PRUEBAS HEAP VALOR VACIO \n\n");

    heap_t* heap = new_heap(comparar);

    char *valor = "";

    print_test("Prueba heap insertar valor vacia", heap_enqueue(heap, valor));
    print_test("Prueba heap la cantidad de elementos es 1", heap_quantity(heap) == 1);
    print_test("Prueba heap desencolar valor vacia, es valor", heap_dequeue(heap) == valor);
    print_test("Prueba heap la cantidad de elementos es 0", heap_quantity(heap) == 0);
    print_test("El heap esta vacio", heap_empty(heap));
    heap_delete(heap, NULL);
}

static void pruebas_heap_arreglo(){
    printf("\nPRUEBAS CON HEAP INICIALIZADO CON UN ARREGLO\n\n");

    void** encolar = malloc(sizeof(void*) * 4);
    encolar[0] = "a";
    encolar[1] = "d";
    encolar[2] = "b";
    encolar[3] = "c";

    heap_t* heap2 = new_heap_arr(encolar, 4, comparar);

    print_test("El heap es creado correctamente", heap2);
    print_test("El heap no esta vacio", !heap_empty(heap2));
    print_test("El maximo es 'd'", comparar(heap_top(heap2), "d") == 0);
    print_test("El heap contiene 4 elementos", heap_quantity(heap2) == 4);
    print_test("Desencola el 'd'", comparar(heap_dequeue(heap2), "d") == 0);
    print_test("El heap contiene 3 elementos", heap_quantity(heap2) == 3);
    print_test("El heap no esta vacio", !heap_empty(heap2));
    print_test("Desencola el 'c'", comparar(heap_dequeue(heap2), "c") == 0);
    print_test("El heap no esta vacio", !heap_empty( heap2));
    print_test("El heap contiene 2 elementos", heap_quantity(heap2) == 2);
    print_test("Desencola el 'b'", comparar(heap_dequeue(heap2), "b") == 0);
    print_test("Desencola el 'a'", comparar(heap_dequeue(heap2), "a") == 0);

    char *valor1 = "1";
    char *valor2 = "2";
    
    print_test("Prueba heap insertar valor1", heap_enqueue(heap2, valor1));
    print_test("Prueba heap ver maximo es correcto", heap_top(heap2) == valor1);
    print_test("Prueba heap insertar valor2", heap_enqueue(heap2, valor2));
    print_test("Prueba heap ver maximo es correcto", heap_top(heap2) == valor2);
    print_test("Prueba heap desencolar es valor2", heap_dequeue(heap2) == valor2);
    print_test("Prueba heap desencolar es valor1", heap_dequeue(heap2) == valor1);
    print_test("El heap esta vacio", heap_empty(heap2));


    heap_delete(heap2, NULL);
    free(encolar);

    print_test("Destruyo el heap con 2 elementos", true);
}

static void prueba_heap_valor_null(){
	printf("\nINICIO DE PRUEBAS HEAP VALOR NULL \n\n");
    heap_t* heap = new_heap(comparar);

    char *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba heap insertar valor vacia valor NULL", heap_enqueue(heap, valor));
    print_test("Prueba heap la cantidad de elementos es 1", heap_quantity(heap) == 1);
    print_test("Prueba heap desencolar valor vacia, es valor NULL", heap_dequeue(heap) == valor);
    print_test("Prueba heap la cantidad de elementos es 0", heap_quantity(heap) == 0);

    heap_delete(heap, NULL);
}
static void pruebas_heap_dequeue(){
    printf("\nINICIO DE PRUEBAS HEAP DESENCOLAR \n\n");

    heap_t* heap = new_heap(comparar);

    char *valor1 = "1";
    char *valor2 = "2";
    char *valor3 = "3";
    char *valor4 = "4";
    char *valor5 = "5"; 

    print_test("Prueba heap insertar valor1", heap_enqueue(heap, valor1));
    print_test("Prueba heap ver maximo es correcto", heap_top(heap) == valor1);
    print_test("Prueba heap insertar valor2", heap_enqueue(heap, valor2));
    print_test("Prueba heap ver maximo es correcto", heap_top(heap) == valor2);
    print_test("Prueba heap desencolar es valor2", heap_dequeue(heap) == valor2);
    print_test("Prueba heap desencolar es valor1", heap_dequeue(heap) == valor1);
    print_test("El heap esta vacio", heap_empty(heap));

    print_test("Prueba heap la cantidad de elementos es 0", heap_quantity(heap) == 0);
    print_test("Prueba heap insertar valor3", heap_enqueue(heap, valor3));
    print_test("Prueba heap ver maximo es correcto", heap_top(heap) == valor3);
    print_test("Prueba heap la cantidad de elementos es 1", heap_quantity(heap) == 1);
    print_test("Prueba heap insertar valor4", heap_enqueue(heap, valor4));
    print_test("Prueba heap ver maximo es correcto", heap_top(heap) == valor4);
    print_test("Prueba heap la cantidad de elementos es 2", heap_quantity(heap) == 2);
    print_test("Prueba heap insertar valor3", heap_enqueue(heap, valor2));
    print_test("Prueba heap ver maximo es correcto", heap_top(heap) == valor4);
    print_test("Prueba heap la cantidad de elementos es 3", heap_quantity(heap) == 3);
    print_test("Prueba heap insertar valor5", heap_enqueue(heap, valor5));
    print_test("Prueba heap ver maximo es correcto", heap_top(heap) == valor5);
    print_test("Prueba heap la cantidad de elementos es 4", heap_quantity(heap) == 4);
    print_test("Prueba heap insertar valor1", heap_enqueue(heap, valor1));
    print_test("Prueba heap ver maximo es correcto", heap_top(heap) == valor5);
    print_test("Prueba heap la cantidad de elementos es 5", heap_quantity(heap) == 5);

    print_test("Prueba heap desencolar es valor5", heap_dequeue(heap) == valor5);
    print_test("Prueba heap la cantidad de elementos es 4", heap_quantity(heap) == 4);
    print_test("Prueba heap desencolar es valor4", heap_dequeue(heap) == valor4);
    print_test("Prueba heap la cantidad de elementos es 3", heap_quantity(heap) == 3);
    print_test("Prueba heap desencolar es valor3", heap_dequeue(heap) == valor3);
    print_test("Prueba heap la cantidad de elementos es 2", heap_quantity(heap) == 2);
    print_test("Prueba heap desencolar es valor2", heap_dequeue(heap) == valor2);
    print_test("Prueba heap la cantidad de elementos es 1", heap_quantity(heap) == 1);
    print_test("Prueba heap desencolar es valor1", heap_dequeue(heap) == valor1);
    print_test("Prueba heap la cantidad de elementos es 0", heap_quantity(heap) == 0);
    print_test("El heap esta vacio", heap_empty(heap));
    heap_delete(heap, NULL);
}

void swapp (char** valor, int x, size_t y) {
    /* Intercambia dos valores enteros. */
    char* a = valor[x];
    char* b = valor[y];
    valor[y] = a;
    valor[x] = b;
}

static void shuffle(char* valor[], size_t largo) {
    srand((unsigned int) time(NULL));

    // Fisher–Yates
    for (int i = (int) (largo - 1); i >= 0; i--) {
        size_t j = (size_t) rand() % (unsigned int)(i + 1);
        swapp(valor, i, j);
    }
}

static void prueba_heap_volumen(size_t largo, bool debug){
	printf("\nINICIO DE PRUEBAS HEAP VOLUMEN \n\n");
    heap_t* heap = new_heap(comparar);

    unsigned valor_valor = 10;         

    char** valor = malloc(sizeof(char*) * largo);
    char** valor_ordenado = malloc(sizeof(char*) * largo);
    for (unsigned i = 0; i < largo; i++){
        valor[i] = malloc(valor_valor);
        sprintf(valor[i], "%08d", i);
        valor_ordenado[i] = malloc(valor_valor);
        sprintf(valor_ordenado[i], "%08d", i);
    }
    shuffle(valor, largo);
    /* Inserta 'largo' parejas en el heap */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        ok = heap_enqueue(heap, valor[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba heap almacenar muchos elementos", ok);
    if (debug) print_test("Prueba heap la cantidad de elementos es correcta", heap_quantity(heap) == largo);
    /* Verifica que borre y devuelva los valores correctos */
    int t = 999;
    for (size_t i = 0; i < largo ; i++) {
        ok = comparar(heap_dequeue(heap), valor_ordenado[t]) == 0;
        t--;
        if (!ok) break;
    }

    if (debug) print_test("Prueba heap desencolar muchos elementos", ok);
    if (debug) print_test("Prueba heap la cantidad de elementos es 0", heap_quantity(heap) == 0);

    /* Destruye el heap y crea uno nuevo que sí libera */
    heap_delete(heap, NULL);
    heap = new_heap(comparar);
    for (int b = 0; b < largo; b++){
        free(valor_ordenado[b]);
    }
    free(valor_ordenado);


    /* Inserta 'largo' parejas en el heap */
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = heap_enqueue(heap, valor[i]);
        if (!ok) break;
    }
    if (!ok) printf("PROBLEMA\n");
    /* Destruye el heap - debería liberar los enteros */
    heap_delete(heap, free);
    free(valor);
}

void heap_tests(){
	prueba_crear_heap_vacio();
	prueba_heap_insertar();
    pruebas_heapsort();
	prueba_heap_valor_vacia();
    pruebas_heap_arreglo();
	prueba_heap_valor_null();
    pruebas_heap_dequeue();
	prueba_heap_volumen(1000,true);	
}