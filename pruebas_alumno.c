#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pila.h"
#define ELEMENTOS_PRUEBA_VOLUMEN 10000
#define A 5


bool no_hace_nada(void* dato, void* extra){
    return false;
}


bool suma_total(void*dato,void* total){
    *(int*)total += *(int*)dato;
    return true;
}


bool sumar_cinco(void* dato,void* extra){
    if (*(size_t*) extra >= 3){
        return false;
    }
    int cinco = 5;
    *(int*)dato += cinco;
    *(size_t*)extra += 1;
    return true;
}


bool insertar_volumen(lista_t* lista, int* vector_pruebas, bool insertar(lista_t*,void*)){
    for(int i = 0; i < ELEMENTOS_PRUEBA_VOLUMEN; i++){
        if (!insertar(lista,&vector_pruebas[i])){
            return false;
        }
    }
    return true;
}

bool borrar_volumen(lista_t* lista, int* vector_pruebas, int inicial){
    int posicion = inicial;
    int paso;
    if (inicial == 0){
        paso = 1;
    }else{
        paso = -1;
    }

    while (!lista_esta_vacia(lista)){
        if (lista_ver_primero(lista) != &vector_pruebas[posicion]){
            return false;
        }
        lista_borrar_primero(lista);
        posicion += paso;
    }
    return true;
}



void pila_destruir_wrapper(void* elem){
    pila_destruir((pila_t*) elem);
}



void prueba_volumen_primero(){
    printf("\nPRUEBAS CON GRAN VOLUMEN DE ELEMENTOS (en primera posicion)\n");
    lista_t* lis = lista_crear();
    int vector_temporal[ELEMENTOS_PRUEBA_VOLUMEN];
    print_test("insertando muchos elementos en primera posicion",insertar_volumen(lis,vector_temporal,lista_insertar_primero));
    print_test("eliminando los elementos de la lista y verificando primero, ultimo y largo de lista",borrar_volumen(lis,vector_temporal,ELEMENTOS_PRUEBA_VOLUMEN-1));
    print_test("lista esta vacia ",lista_esta_vacia(lis));
    lista_destruir(lis,NULL);
}

void prueba_volumen_ultimo(){
    printf("\nPRUEBAS CON GRAN VOLUMEN DE ELEMENTOS (en ultima posicion)\n");
    lista_t* lis = lista_crear();
    int vector_temporal[ELEMENTOS_PRUEBA_VOLUMEN];
    print_test("insertando muchos elementos en ultima posicion",insertar_volumen(lis,vector_temporal,lista_insertar_ultimo));
    print_test("eliminando los elementos de la lista y verificando primero, ultimo y largo de lista",borrar_volumen(lis,vector_temporal,0));
    print_test("lista esta vacia",lista_esta_vacia(lis));
    lista_destruir(lis,NULL);
}



void prueba_crear_destruir(){
    printf("\nPRUEBAS CREANDO/DESTUYENDO LISTA\n");
    lista_t* lis = lista_crear();
    lista_destruir(lis,NULL);
}


void prueba_null_primero(){
    printf("\nPRUEBA CON ELEMENTO NULL EN POSICION DE PRIMERO\n");
    lista_t* lis = lista_crear();
    print_test("inserto elemento NULL en primera posicion",lista_insertar_primero(lis,NULL));
    print_test("verificacion NULL agregado correctamente",!lista_esta_vacia(lis));
    print_test("elemento NULL es primero de lista",!lista_ver_primero(lis));
    print_test("elemento NULL es ultimo de lista",!lista_ver_ultimo(lis));
    print_test("el largo de la lista es 1",lista_largo(lis) == 1);
    print_test("recupero el primero de la lista (elemento NULL)",lista_borrar_primero(lis) == NULL);
    print_test("verificacion NULL eliminado correctamente de la lista (lista vacia)",lista_esta_vacia(lis));
    lista_destruir(lis,NULL);
}

void prueba_null_ultimo(){
    printf("\nPRUEBAS CON ELEMENTOS NULL EN POSICION DE ULTIMO\n");
    lista_t* lis = lista_crear();
    print_test("inserto elemento NULL en ultima posicion",lista_insertar_ultimo(lis,NULL));
    print_test("verificacion NULL agregado correctamente",!lista_esta_vacia(lis));
    print_test("elemento NULL es primero de lista",!lista_ver_primero(lis));
    print_test("elemento NULL es ultimo de lista",!lista_ver_ultimo(lis));
    print_test("el largo de la lista es 1",lista_largo(lis) == 1);
    print_test("recupero el primero de la lista (elemento NULL)",lista_borrar_primero(lis) == NULL);
    print_test("verificacion NULL eliminado correctamente de la lista",lista_esta_vacia(lis));
    lista_destruir(lis,NULL);
}

void prueba_lista_nueva(){
    printf("\nPRUEBAS SOBRE LISTA NUEVA\n");
    lista_t* lis = lista_crear();
    print_test("verificacion lista esta vacia", lista_esta_vacia(lis));
    print_test("verificacion tope de lista",!lista_ver_primero(lis));
    print_test("eliminar primero no esta permitido",!lista_borrar_primero(lis));
    print_test("no hay primero de lista",!lista_ver_primero(lis));
    print_test("no hay ultimo de lista",!lista_ver_ultimo(lis));
    print_test("el largo de la lista es 0",lista_largo(lis) == 0);
    lista_destruir(lis,NULL);
}

void prueba_insertar_eliminar_estaticos(){
    printf("\nPRUEBAS INSERTAR ELEMENTOS ESTATICOS\n");
    int a = 5;
    int b = 12;
    int c = 436;
    int d = 7982;
    lista_t* lis = lista_crear();
    print_test("insertar elemento en primera posicion",lista_insertar_primero(lis,&a));
    print_test("verificacion lista no esta vacia",!lista_esta_vacia(lis));
    print_test("ver primero de lista",*(int*)lista_ver_primero(lis) == a);
    print_test("ver ultimo de lista",*(int*)lista_ver_ultimo(lis) == a);
    print_test("el largo de la lista es 1",lista_largo(lis) == 1);

    print_test("insertar elemento en ultima posicion",lista_insertar_ultimo(lis,&b));
    print_test("ver primero de lista",*(int*)lista_ver_primero(lis) == a);
    print_test("ver ultimo de lista",*(int*)lista_ver_ultimo(lis) == b);
    print_test("el largo de la lista es 2",lista_largo(lis) == 2);

    print_test("insertar elemento en primera posicion",lista_insertar_primero(lis,&c));
    print_test("ver primero de lista",*(int*)lista_ver_primero(lis) == c);
    print_test("ver ultimo de lista",*(int*)lista_ver_ultimo(lis) == b);
    print_test("el largo de la lista es 3",lista_largo(lis) == 3);

    print_test("insertar elemento en ultima posicion",lista_insertar_ultimo(lis,&d));
    print_test("ver primero de lista",*(int*)lista_ver_primero(lis) == c);
    print_test("ver ultimo de lista",*(int*)lista_ver_ultimo(lis) == d);
    print_test("el largo de la lista es 4",lista_largo(lis) == 4);

    print_test("elimino primer elemento",*(int*)lista_borrar_primero(lis) == c);
    print_test("ver primero de lista",*(int*)lista_ver_primero(lis) == a);
    print_test("ver ultimo de lista",*(int*)lista_ver_ultimo(lis) == d);
    print_test("el largo de la lista es 3",lista_largo(lis) == 3);

    print_test("elimino primer elemento",*(int*)lista_borrar_primero(lis) == a);
    print_test("ver primero de lista",*(int*)lista_ver_primero(lis) == b);
    print_test("ver ultimo de lista",*(int*)lista_ver_ultimo(lis) == d);
    print_test("el largo de la lista es 2",lista_largo(lis) == 2);

    print_test("elimino primer elemento",*(int*)lista_borrar_primero(lis) == b);
    print_test("ver primero de lista",*(int*)lista_ver_primero(lis) == d);
    print_test("ver ultimo de lista",*(int*)lista_ver_ultimo(lis) == d);
    print_test("el largo de la lista es 1",lista_largo(lis) == 1);

    print_test("elimino primer elemento",*(int*)lista_borrar_primero(lis) == d);
    print_test("ver primero de lista",!lista_ver_primero(lis));
    print_test("ver ultimo de lista",!lista_ver_ultimo(lis));
    print_test("el largo de la lista es 0",lista_largo(lis) == 0);

    print_test("verificacion lista esta vacia", lista_esta_vacia(lis));
    print_test("no se puede eliminar primer elemento",!lista_borrar_primero(lis));

    lista_destruir(lis,NULL);
}

void prueba_destruir_estaticos(){
    printf("\nDESTRUIR LISTA CON ELEMENTOS ESTATICOS RESTANTES\n");
    int a = 5;
    int b = 12;
    lista_t* lis = lista_crear();
    print_test("insertar elemento en primera posicion",lista_insertar_primero(lis,&a));
    print_test("insertar elemento en ultima posicion",lista_insertar_ultimo(lis,&b));
    lista_destruir(lis,NULL);
}

void prueba_insertar_eliminar_dinamicos(){
    printf("\nPRUEBAS INSERTAR/BORRAR PUNTEROS DINAMICOS\n");
    int* ptr0 = (int*)malloc(5*sizeof(int));
    int* ptr1 = (int*)malloc(5*sizeof(int));
    int* ptr2 = (int*)malloc(5*sizeof(int));
    lista_t* lis = lista_crear();

    print_test("insertar elemento en primera posicion",lista_insertar_primero(lis,&ptr0));
    print_test("verificacion lista no esta vacia",!lista_esta_vacia(lis));
    print_test("ver primero de lista",lista_ver_primero(lis) == &ptr0);
    print_test("ver ultimo de lista",lista_ver_ultimo(lis) == &ptr0);
    print_test("el largo de la lista es 1",lista_largo(lis) == 1);

    print_test("insertar elemento en ultima posicion",lista_insertar_ultimo(lis,&ptr1));
    print_test("ver primero de lista",lista_ver_primero(lis) == &ptr0);
    print_test("ver ultimo de lista",lista_ver_ultimo(lis) == &ptr1);
    print_test("el largo de la lista es 2",lista_largo(lis) == 2);

    print_test("insertar elemento en primera posicion",lista_insertar_primero(lis,&ptr2));
    print_test("ver primero de lista",lista_ver_primero(lis) == &ptr2);
    print_test("ver ultimo de lista",lista_ver_ultimo(lis) == &ptr1);
    print_test("el largo de la lista es 3",lista_largo(lis) == 3);


    print_test("elimino primer elemento",lista_borrar_primero(lis) == &ptr2);
    print_test("ver primero de lista",lista_ver_primero(lis) == &ptr0);
    print_test("ver ultimo de lista",lista_ver_ultimo(lis) == &ptr1);
    print_test("el largo de la lista es 3",lista_largo(lis) == 2);

    print_test("elimino primer elemento",lista_borrar_primero(lis) == &ptr0);
    print_test("ver primero de lista",lista_ver_primero(lis) == &ptr1);
    print_test("ver ultimo de lista",lista_ver_ultimo(lis) == &ptr1);
    print_test("el largo de la lista es 2",lista_largo(lis) == 1);

    print_test("elimino primer elemento",lista_borrar_primero(lis) == &ptr1);
    print_test("ver primero de lista",!lista_ver_primero(lis));
    print_test("ver ultimo de lista",!lista_ver_ultimo(lis));
    print_test("el largo de la lista es 0",lista_largo(lis) == 0);

    print_test("verificacion lista esta vacia", lista_esta_vacia(lis));
    print_test("no se puede eliminar primer elemento",!lista_borrar_primero(lis));

    lista_destruir(lis,free);
    free(ptr0);
    free(ptr1);
    free(ptr2);
}

void prueba_destruir_dinamicos(){
    printf("\nPRUEBAS DESTRUIR LISTA CON ELEMENTOS DINAMICOS RESTANTES\n");
    int* ptr0 = (int*)malloc( 5*sizeof(int));
    int* ptr1 = (int*)malloc( 5*sizeof(int));
    int* ptr2 = (int*)malloc( 5*sizeof(int));
    lista_t* lis = lista_crear();
    print_test("insertar elemento en ultima posicion",lista_insertar_ultimo(lis,ptr0));
    print_test("insertar elemento en primera posicion",lista_insertar_primero(lis,ptr1));
    print_test("insertar elemento en primera posicion",lista_insertar_primero(lis,ptr2));
    lista_destruir(lis,free);
}

void prueba_destruir_pilas(){
    printf("\nPRUEBAS DESTRUIR LISTA CON PILAS RESTANTES\n");
    int a = 5;
    int b = 212;
    pila_t* p1 = pila_crear();
    pila_apilar(p1,&a);
    pila_t* p2 = pila_crear();
    pila_apilar(p2,&b);
    lista_t* lis = lista_crear();
    print_test("insertar elemento en ultima posicion",lista_insertar_ultimo(lis,p1));
    print_test("insertar elemento en primera posicion",lista_insertar_primero(lis,p2));
    print_test("verificacion lista no esta vacia",!lista_esta_vacia(lis));
    lista_destruir(lis,pila_destruir_wrapper);
}


void prueba_iterador_insertar_primero(){
    printf("\nPRUEBA A INSERTAR UN ELEMENTO EN EL PRINCIPIO DE LA LISTA (I. EXTERNO)\n");
    int a = 5;
    int b = 12;
    int i = 212;
    lista_t* lis = lista_crear();
    print_test("insertar elemento en primera posicion (primitiva de lista)",lista_insertar_primero(lis,&a));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&b));
    lista_iter_t* itera = lista_iter_crear(lis);
    print_test("se inserta elemento al principio con iterador",lista_iter_insertar(itera,&i));
    print_test("el elemento en primer lugar es el insertado",*(int*)lista_iter_ver_actual(itera) == i);
    lista_iter_avanzar(itera);
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera) == a);
    lista_iter_avanzar(itera);
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera) == b);
    print_test("final iterador",lista_iter_avanzar(itera));
    print_test("iterador esta al final",lista_iter_al_final(itera));
    lista_iter_destruir(itera);
    lista_destruir(lis,NULL);
}


void prueba_iterador_insertar_final(){
    printf("\nPRUEBA A INSERTAR UN ELEMENTO EN EL FINAL DE LA LISTA (I. EXTERNO)\n");
    int a = 5;
    int b = 12;
    int i = 212;
    lista_t* lis = lista_crear();
    print_test("insertar elemento en primera posicion (primitiva de lista)",lista_insertar_primero(lis,&a));
    print_test("insertar elemento en primera posicion (primitiva de lista)",lista_insertar_primero(lis,&b));
    lista_iter_t* itera = lista_iter_crear(lis);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera));
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera));
    print_test("el iterador llega al final de la lista",lista_iter_al_final(itera));
    print_test("se inserta elemento al final con iterador",lista_iter_insertar(itera,&i));
    print_test("el iterador no esta al final de la lista",!lista_iter_al_final(itera));
    print_test("el elemento se inserto al final",*(int*)lista_iter_ver_actual(itera) == i);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera));
    print_test("el iterador llega al final de la lista",lista_iter_al_final(itera));
    lista_iter_destruir(itera);
    lista_destruir(lis,NULL);
}


void prueba_iterador_insertar_medio(){
    printf("\nPRUEBA A INSERTAR UN ELEMENTO EN EL MEDIO DE LA LISTA (I. EXTERNO)\n");
    int a = 5;
    int b = 12;
    int c = 352;
    int d = 9999;
    int i = 212;
    lista_t* lis = lista_crear();
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&a));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&b));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&c));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&d));
    lista_iter_t* itera0 = lista_iter_crear(lis);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera0));
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera0));
    print_test("se inserta elemento en medio de la lista con iterador",lista_iter_insertar(itera0,&i));
    lista_iter_destruir(itera0);
    lista_iter_t* itera1 = lista_iter_crear(lis);
    printf("nuevo iterador para comprobar que la lista mantuvo el orden\n");
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == a);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == b);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == i);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == c);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == d);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("el iterador llega al final de la lista",lista_iter_al_final(itera1));
    lista_iter_destruir(itera1);
    lista_destruir(lis,NULL);

}


void prueba_iterador_eliminar_primero(){
    printf("\nPRUEBA A BORRAR EL PRIMER ELEMENTO DE LA LISTA (I. EXTERNO)\n");
    int a = 5;
    int b = 12;
    int c = 352;
    lista_t* lis = lista_crear();
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&a));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&b));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&c));
    lista_iter_t* itera = lista_iter_crear(lis);
    print_test("el elemento borrado es el primero de la lista",*(int*)lista_iter_borrar(itera) == a);
    lista_iter_destruir(itera);
    printf("nuevo iterador para comprobar que la lista mantuvo el orden\n");
    lista_iter_t* itera1 = lista_iter_crear(lis);
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == b);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == c);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("el iterador llega al final de la lista",lista_iter_al_final(itera1));
    lista_iter_destruir(itera1);
    lista_destruir(lis,NULL);
}


void prueba_iterador_eliminar_final(){
    printf("\nPRUEBA A BORRAR UN ELEMENTO EL FINAL DE LA LISTA (I. EXTERNO)\n");
    int a = 5;
    int b = 12;
    int c = 352;
    lista_t* lis = lista_crear();
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&a));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&b));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&c));
    lista_iter_t* itera = lista_iter_crear(lis);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera));
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera));
    print_test("el iterador esta en el ultimo elemento",*(int*)lista_iter_ver_actual(itera) == c);
    print_test("el elemento borrado es el ultimo de la lista",*(int*)lista_iter_borrar(itera) == c);
    lista_iter_destruir(itera);
    printf("nuevo iterador para comprobar que la lista mantuvo el orden\n");
    lista_iter_t* itera1 = lista_iter_crear(lis);
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == a);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == b);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("el iterador llega al final de la lista",lista_iter_al_final(itera1));
    lista_iter_destruir(itera1);
    lista_destruir(lis,NULL);
}


void prueba_iterador_eliminar_medio(){
    printf("\nPRUEBA A ELIMINAR ELEMENTO EN MEDIO DE LA LISTA (I. EXTERNO)\n");
    int a = 5;
    int b = 12;
    int c = 352;
    lista_t* lis = lista_crear();
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&a));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&b));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&c));
    lista_iter_t* itera = lista_iter_crear(lis);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera));
    print_test("el elemento borrado es el del medio de la lista",*(int*)lista_iter_borrar(itera) == b);
    lista_iter_destruir(itera);
    printf("nuevo iterador para comprobar que la lista mantuvo el orden\n");
    lista_iter_t* itera1 = lista_iter_crear(lis);
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == a);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == c);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("el iterador llega al final de la lista",lista_iter_al_final(itera1));
    lista_iter_destruir(itera1);
    lista_destruir(lis,NULL);
}


void prueba_interno_rango(){
    printf("\nPRUEBA A APLICAR UNA FUNCION A UN RANGO DE LA LISTA (I. INTERNO)\n");
    int a = 5;
    int b = 12;
    int c = 352;
    int d = 2431;
    int e = 9;
    int f = 98;
    lista_t* lis = lista_crear();
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&a));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&b));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&c));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&d));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&e));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&f));
    size_t limite = 0;
    printf("uso de funcion en iterador interno (sumar 5 a los primeros 3 elementos)\n");
    lista_iterar(lis,sumar_cinco,&limite);
    printf("verificacion de la correcta modificacion de la lista\n");
    lista_iter_t* itera1 = lista_iter_crear(lis);
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == 10);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == 17);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == 357);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == d);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == e);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == f);
    print_test("el iterador avanza en la lista",lista_iter_avanzar(itera1));
    print_test("el iterador llega al final de la lista",lista_iter_al_final(itera1));
    lista_iter_destruir(itera1);
    lista_destruir(lis,NULL);
}


void prueba_interno_completo(){
    printf("\nPRUEBA A APLICAR FUNCION A TODA LA LISTA (I. INTERNO)\n");
    int a = 5;
    int b = 12;
    int c = 352;
    int d = 2431;
    int e = 9;
    int f = 98;
    lista_t* lis = lista_crear();
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&a));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&b));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&c));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&d));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&e));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&f));
    int total = 0;
    printf("se suma el total de los numeros en la lista con iterador interno\n");
    lista_iterar(lis,suma_total,&total);
    print_test("la suma total es correcta",total == 2907);
    lista_destruir(lis,NULL);
}


void prueba_interno_vacio(){
    printf("\nPRUEBA A ELIMINAR ELEMENTO EN MEDIO DE LA LISTA (I. EXTERNO)\n");
    int a = 5;
    int b = 12;
    int c = 352;
    lista_t* lis = lista_crear();
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&a));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&b));
    print_test("insertar elemento en ultima posicion (primitiva de lista)",lista_insertar_ultimo(lis,&c));
    printf("se utiliza una funcion para ningun elemento\n");
    lista_iterar(lis,no_hace_nada,&c);
    lista_iter_t* itera1 = lista_iter_crear(lis);
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == a);
    (lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == b);
    (lista_iter_avanzar(itera1));
    print_test("la lista mantuvo el orden",*(int*)lista_iter_ver_actual(itera1) == c);
    (lista_iter_avanzar(itera1));
    print_test("el iterador llega al final de la lista",lista_iter_al_final(itera1));
    lista_iter_destruir(itera1);
    lista_destruir(lis,NULL);
}


void pruebas_lista_alumno(void){
    prueba_crear_destruir();
    prueba_null_primero();
    prueba_null_ultimo();
    prueba_lista_nueva();
    prueba_insertar_eliminar_estaticos();
    prueba_destruir_estaticos();
    prueba_insertar_eliminar_dinamicos();
    prueba_destruir_dinamicos();
    prueba_destruir_pilas();
    prueba_volumen_primero();
    prueba_volumen_ultimo();
    prueba_iterador_insertar_primero();
    prueba_iterador_insertar_final();
    prueba_iterador_insertar_medio();
    prueba_iterador_eliminar_primero();
    prueba_iterador_eliminar_final();
    prueba_iterador_eliminar_medio();
    prueba_interno_rango();
    prueba_interno_completo();
    prueba_interno_vacio();
}
