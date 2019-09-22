#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>


struct lista;
typedef struct lista lista_t;


// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void);


// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void*));


// Devuelve verdadero si la lista no tiene elementos enlistados, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);


// Agrega un nuevo elemento al principio de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al comienzo de la lista, se incrementa en
// uno la longitud de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);


// Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento al final de la lista, se incrementa en uno
// la longitud de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);


// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista);


// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t *lista);


// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void* lista_borrar_primero(lista_t *lista);


// Devuelve el largo de la lista. Se devuelve la cantidad de elementos que contiene la lista.
// Pre: la lista fue creada.
// Post: se devolvio el largo de la lista.
size_t lista_largo(const lista_t *lista);





void pruebas_lista_alumno(void);



#endif // LISTA_H
