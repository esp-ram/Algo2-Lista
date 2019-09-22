#include "lista.h"
#include <stdlib.h>



typedef struct nodo {
    void* dato;
    struct nodo* proximo;
} nodo_t;

struct lista{
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


nodo_t* nodo_crear(void* valor){
    nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
    if (nodo_nuevo == NULL){
        return NULL;
    }
    nodo_nuevo->dato = valor;
    nodo_nuevo->proximo = NULL;
    return nodo_nuevo;
}



lista_t* lista_crear(void){
    lista_t* lista_nueva = malloc(sizeof(lista_t));
    if (lista_nueva == NULL){
        return NULL;
    }
    lista_nueva->primero = NULL;
    lista_nueva->ultimo = NULL;
    lista_nueva->largo = 0;
    return lista_nueva;
}


bool lista_esta_vacia(const lista_t* lista){
    return(lista->primero == NULL);
}


bool lista_insertar_ultimo(lista_t* lista, void* dato){
    nodo_t* nodo_agregar = nodo_crear(dato);
    if (nodo_agregar == NULL){
        return false;
    }
    if (lista_esta_vacia(lista)){
        lista->primero = nodo_agregar;
        lista->ultimo = nodo_agregar;
        lista->largo += 1;
        }else{
        lista->ultimo->proximo = nodo_agregar;
        lista->ultimo = nodo_agregar;
        lista->largo += 1;
    }
    return true;
}


bool lista_insertar_primero(lista_t* lista, void* dato){
    nodo_t* nodo_agregar = nodo_crear(dato);
    if (nodo_agregar == NULL){
        return false;
    }
    if (lista_esta_vacia(lista)){
        lista->primero = nodo_agregar;
        lista->ultimo = nodo_agregar;
        lista->largo += 1;
    }else{
        nodo_agregar->proximo = lista->primero;
        lista->primero = nodo_agregar;
        lista->largo += 1;
    }
    return true;
}


void* lista_ver_primero(const lista_t* lista){
    return lista_esta_vacia(lista) ? NULL : lista->primero->dato;
}

void* lista_ver_ultimo(const lista_t* lista){
    return lista_esta_vacia(lista) ? NULL : lista->ultimo->dato;
}

size_t lista_largo (const lista_t* lista){
    return (lista->largo);
}


void* lista_borrar_primero(lista_t* lista){
    if (lista_esta_vacia(lista)){
        return NULL;
    }
    void* dato_devolver = lista_ver_primero(lista);
    nodo_t* nodo_borrar = lista->primero;
    lista->primero = lista->primero->proximo;
    free(nodo_borrar);
    lista->largo -= 1;
    if (lista_esta_vacia(lista)){
        lista->ultimo = NULL;
        lista->largo = 0;
    }
    return(dato_devolver);
}

void lista_destruir(lista_t* lista, void destruir_dato(void*)){
    while(!lista_esta_vacia(lista)){
        void* dato_eliminar = lista_borrar_primero(lista);
        if (destruir_dato != NULL){
            destruir_dato(dato_eliminar);
        }
    }
    free(lista);
}
