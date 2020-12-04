#include "listaSimple.h"
#include <string.h>

nodo* inicLista(){
    return NULL;
}

nodo* crearNodo(stPaciente dato){
    nodo* nuevo = (nodo*) malloc(sizeof(nodo));
    nuevo->dato = dato;
    nuevo->siguiente = NULL;
    return nuevo;
}

void muestraUnPaciente (stPaciente p)
{
    printf("-----------------------------\n");
    printf("\nID DEL PACIENTE:...: %d", p.idPaciente);
    printf("\nNOMBRE.............: %s", p.nombrePaciente);
    printf("\nAPELLIDO...........: %s", p.apellidoPaciente);
    printf("\nDIAGNOSTICO........: %s", p.diagnostico);
    printf("\nFEHCA ATENCION.....: %s", p.fechaAtencion);
    printf("\nNOMBRE DOCTOR......: %s", p.nombreDoctor);
}

void muestraNodo(nodo *nodo){
    printf("\n nodo: %p - nodo->siguiente: %p\n",  nodo, nodo->siguiente);
    muestraUnPaciente(nodo->dato);
}

void muestraLista(nodo* lista){
    nodo* seg = lista;
    while(seg){
        muestraNodo(seg);
        seg = seg->siguiente;
    }
}

nodo* buscarUltimo(nodo* lista){
    nodo* seg = lista;
    while(seg->siguiente!=NULL){
        seg = seg->siguiente;
    }

    return seg;
}

int buscarPaciente(nodo* lista, char nombre[], char apellido[]){
    nodo* seg = lista;
    int flag = 0;
    while(seg && flag == 0){
        if (strcmp(nombre, seg->dato.nombrePaciente) == 0 && strcmp(apellido, seg->dato.apellidoPaciente) == 0){
            flag = 1;
        }
        seg = seg->siguiente;
    }
    return flag;
}

nodo* agregarAlFinal(nodo* lista, nodo* nuevo){
    if(lista==NULL){
        lista = nuevo;
    }else{
        nodo* ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevo;
    }
    return lista;
}
