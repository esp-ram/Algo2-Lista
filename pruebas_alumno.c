#include "lista.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "pila.h"
#define ELEMENTOS_PRUEBA_VOLUMEN 100




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
}
