#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct
{
    int idPaciente;
    char nombrePaciente[30];
    char apellidoPaciente[30];
    char diagnostico[100];
    char fechaAtencion[11];
    char nombreDoctor[30];
}stPaciente;

typedef struct _nodo {
   stPaciente dato;
   struct _nodo *siguiente;
} nodo;

nodo* inicLista();
nodo* crearNodo(stPaciente dato);
void muestraUnPaciente (stPaciente a);
void muestraNodo(nodo *nodo);
void muestraLista(nodo* lista);
nodo* buscarUltimo(nodo* lista);
nodo* agregarAlFinal(nodo* lista, nodo* nuevo);
int buscarPaciente(nodo* lista, char nombre[], char apellido[]);

#endif // LISTA_H_INCLUDED
