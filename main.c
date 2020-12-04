#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listaSimple.h"
#include "registroArchivo.h"

#define DIM 10
#define AR_NEUMONOLOGIA "neumonologia.dat"


/// EJERCICIO 1

typedef struct{
    int idEspecialidad;
    char especialidadMedica[30];
    nodo* listaDePacientes;
} stEspecialidadMedica;

int agregarCelda (stEspecialidadMedica adl[], int v, char especialidad[]);
int buscaPosEspecialidad (stEspecialidadMedica adl[], int v, char especialidad[]);
int altaArreglo (stEspecialidadMedica adl[], int v, char especialidad[], stPaciente p);
int pasaArchivoToArreglo (char archivo[], stEspecialidadMedica adl[], int v, int dim);
void mostrarArrgeloEspecialidades (stEspecialidadMedica adl[], int v);
void pasaArregloToArchivo (stEspecialidadMedica adl[], int v, char especialidad[]);
void mostrarArchivoNeumonologia ();


int main()
{
    stEspecialidadMedica arregloEspecialidad [DIM];
    int validos = 0, bandera;

    validos = pasaArchivoToArreglo(arRegistro, arregloEspecialidad, validos, DIM);

    mostrarArrgeloEspecialidades(arregloEspecialidad, validos);

    /// EJERCICIO 7. FUNCION EN LA LIBRERIA DE LISTA SIMPLE
    bandera = buscarPaciente(arregloEspecialidad[2].listaDePacientes, "Maria", "Gil");

    if (bandera == 1){
        printf("\nEl paciente se encuentra en la especialidad\n");
    } else {
        printf("\nEl paciente no esta en la especialidad\n");
    }


    system("pause");
    system("cls");
    printf("EJERCICIO 8\n");
    pasaArregloToArchivo(arregloEspecialidad, validos, "Neumologia general");

    mostrarArchivoNeumonologia ();


    return 0;
}

/// EJERCICIO 2

int agregarCelda (stEspecialidadMedica adl[], int v, char especialidad[]){
    adl[v].idEspecialidad = v;
    strcpy(adl[v].especialidadMedica, especialidad);
    adl[v].listaDePacientes = inicLista();
    v++;
    return v;
}

/// EJERCICIO 3

int buscaPosEspecialidad (stEspecialidadMedica adl[], int v, char especialidad[]){
    int pos = -1;
    int i=0;

    while (i<v && pos == -1){
        if (strcmp(adl[i].especialidadMedica, especialidad)==0){
            pos=i;
        }
        i++;
    }
    return pos;
}

/// EJERCICIO 4

int altaArreglo (stEspecialidadMedica adl[], int v, char especialidad[], stPaciente p)
{
    nodo* aux = crearNodo(p);
    int pos = buscaPosEspecialidad(adl, v, especialidad);
    if (pos==-1){
        v = agregarCelda(adl, v, especialidad);
        pos = v-1;
    }
    adl[pos].listaDePacientes = agregarAlFinal(adl[pos].listaDePacientes, aux);
    return v;
}

/// EJERCICIO 5

int pasaArchivoToArreglo (char archivo[], stEspecialidadMedica adl[], int v, int dim)
{
    FILE * arch = fopen(archivo, "rb");
    if (arch!=NULL){
        stRegistroMedico aux;
        stPaciente pacienteAux;
        while (fread(&aux, sizeof(stRegistroMedico), 1, arch)>0 && v<dim){
            pacienteAux.idPaciente = aux.idPaciente;
            strcpy(pacienteAux.apellidoPaciente, aux.apellidoPaciente);
            strcpy(pacienteAux.nombrePaciente, aux.nombrePaciente);
            strcpy(pacienteAux.diagnostico, aux.diagnostico);
            strcpy(pacienteAux.fechaAtencion, aux.fechaAtencion);
            strcpy(pacienteAux.nombreDoctor, aux.nombreDoctor);
            v = altaArreglo(adl, v, aux.especialidadMedica, pacienteAux);
        }
        fclose(arch);
    }
    return v;
}

/// EJERCICIO 6

void mostrarArrgeloEspecialidades (stEspecialidadMedica adl[], int v){
    for (int i=0; i<v; i++){
        printf("\n--------------------------------------------------------\n");
        printf("\nID DE LA ESPECIALIDAD.......: %d\n", adl[i].idEspecialidad);
        printf("\nESPECIALIDAD MEDICA.........: %s\n", adl[i].especialidadMedica);
        muestraLista(adl[i].listaDePacientes);
    }
}

/// EJERCICIO 8

void pasaArregloToArchivo (stEspecialidadMedica adl[], int v, char especialidad[])
{
    stRegistroMedico r;
    int i=0;
    nodo* aux = NULL;
    FILE* pArchivo = fopen(AR_NEUMONOLOGIA, "ab");
    if (pArchivo){
        while (i<v){
            aux = adl[i].listaDePacientes;
            r.idEspecialidad = adl[i].idEspecialidad;
            strcpy(r.especialidadMedica, adl[i].especialidadMedica);
            while (aux){
                if ( strcmp(adl[i].especialidadMedica, especialidad) == 0){
                    r.idPaciente = aux->dato.idPaciente;
                    strcpy(r.apellidoPaciente, aux->dato.apellidoPaciente);
                    strcpy(r.nombrePaciente, aux->dato.nombrePaciente);
                    strcpy(r.diagnostico, aux->dato.diagnostico);
                    strcpy(r.fechaAtencion, aux->dato.fechaAtencion);
                    strcpy(r.nombreDoctor, aux->dato.nombreDoctor);
                    fwrite(&r, sizeof(stRegistroMedico), 1, pArchivo);
                }
                aux = aux->siguiente;
            }
            i++;
        }
        fclose(pArchivo);
    }
}

/// MOSTRAR EJERCICIO 8

void mostrarArchivoNeumonologia ()
{
    stRegistroMedico a;
    FILE *pArch = fopen(AR_NEUMONOLOGIA, "rb");

    if (pArch){
        while (fread(&a, sizeof(stRegistroMedico), 1, pArch)>0){
            mostrarUnRegistro(a);
        }
        fclose(pArch);
    }
}
