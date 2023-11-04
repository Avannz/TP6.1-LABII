#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

typedef struct
{
    int nota;
    int legajo;
    char nombreApe[40];
    char materia[40];
    int idMateria;
} registroArchivo;

typedef struct
{
    int nota;
    int legajo;
    char nombreApe[40];
} notaAlumno;

typedef struct _nodo
{
    notaAlumno dato;
    struct _nodo *siguiente;
} nodo;

typedef struct
{
    int idMateria;
    char materia[40];
    nodo * listaDeNotas;
} celda;

/// PROTOTIPADO ///

int buscar_posicion(celda arreglo[], int dim, registroArchivo alumno);
int agregar_materias(celda arreglo[], int dim, FILE* archivo);
void cargar_archivo(FILE* archivo);
void mostrar_archivo(FILE* archivo);
nodo* inic_nodo();
nodo* crear_nodo(notaAlumno dato);
nodo* agregar_pricipio(nodo* lista, nodo* nuevoNodo);
nodo* crear_lista_alumno(nodo* lista, notaAlumno dato);

/// MAIN ///

int main()
{

    FILE* archivo;
    celda sistema_de_materias[30];
    int validos_materias;
    char materia[30];

    /*cargar_archivo(archivo);
    mostrar_archivo(archivo);*/


    validos_materias = agregar_materias(sistema_de_materias, 10, archivo);


    printf("Ingresa el nombre de la materia: ");
    fflush(stdin);
    gets(&materia);

    mostrar_arreglo(sistema_de_materias, validos_materias, materia);


}

/// FUNCIONES ///

void cargar_archivo(FILE* archivo)
{

    archivo = fopen("miArchivo.bin", "ab");

    char letra = 's';
    registroArchivo aux;

    if(archivo)
    {
        while(letra == 's')
        {
            system("cls");

            printf("Ingresa el #ID de la materia: ");
            fflush(stdin);
            scanf("%i", &aux.idMateria);

            printf("Ingresa el nombre de la materia: ");
            fflush(stdin);
            gets(&aux.materia);

            printf("Ingresa el legajo del alumno: ");
            fflush(stdin);
            scanf("%i", &aux.legajo);

            printf("Ingresa el nombre del alumno: ");
            fflush(stdin);
            gets(&aux.nombreApe);

            printf("Ingresa la nota del alumo: ");
            fflush(stdin);
            scanf("%i", &aux.nota);

            fwrite(&aux, sizeof(registroArchivo), 1, archivo);

            printf("Ingresa 's' para continuar: ");
            fflush(stdin);
            scanf("%c", &letra);

        }

        fclose(archivo);
    }
}
void mostrar_archivo(FILE* archivo)
{

    archivo = fopen("miArchivo.bin", "rb");
    registroArchivo aux;

    if(archivo)
    {

        while(fread(&aux, sizeof(registroArchivo), 1, archivo) > 0)
        {

            printf("\n......................");
            printf("\nMateria #ID: %i\n", aux.idMateria);
            printf("Materia: %s\n", aux.materia);
            printf("Legajo: %i\n", aux.legajo);
            printf("Nombre y Apellido: %s\n", aux.nombreApe);
            printf("Nota: %i\n", aux.nota);
            printf("........................");

        }
    }
}
nodo* inic_nodo()
{

    return NULL;
}
nodo* crear_nodo(notaAlumno dato)
{
    nodo* aux = (nodo*) malloc(sizeof(nodo));

    aux->dato = dato;
    aux->siguiente = NULL;

    return aux;
}
nodo* agregar_pricipio(nodo* lista, nodo* nuevoNodo)
{
    if(!lista)
    {
        lista = nuevoNodo;
    }
    else
    {

        lista->siguiente = lista;
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }

    return lista;
}
nodo* cargar_lista_alumno(nodo* lista, notaAlumno dato)
{
    if(lista)
    {

        nodo* nuevoNodo = inic_nodo();

        nuevoNodo = crear_nodo(dato);

        lista = agregar_pricipio(lista, nuevoNodo);
    }

    return lista;
}
int agregar_materias(celda arreglo[], int dim, FILE* archivo)
{

    archivo = fopen("miArchivo.bin", "rb");
    registroArchivo aux;
    notaAlumno alumno;

    int i = 0;
    int pos = -1;

    if(archivo)
    {

        while(fread(&aux, sizeof(registroArchivo), 1, archivo) > 0)
        {

            pos = buscar_posicion(arreglo, dim, aux);

            if(pos == -1)
            {

                arreglo[i].idMateria = aux.idMateria;
                strcpy(arreglo[i].materia, aux.materia);
            }
            else
            {
                alumno.legajo = aux.legajo;
                strcpy(alumno.nombreApe, aux.nombreApe);
                alumno.nota = aux.nota;

                arreglo[i].listaDeNotas = crear_lista_alumno(arreglo[i].listaDeNotas, alumno);
            }

            i++;
        }

        fclose(archivo);
    }

    return i;
}


int buscar_posicion(celda arreglo[], int dim, registroArchivo alumno)
{
    int i = 0;
    int pos = -1;

    while(i < dim)
    {

        if(strcmp(arreglo[i].materia, alumno.materia) == 0)
        {

            pos = i;
        }

        i++;
    }

    return pos;
}
void recorrer_lista_de_alumnos(nodo* lista)
{

    if(lista)
    {
        printf("........................");
        printf("Legajo: %i\n", lista->dato.legajo);
        printf("Nombre y Apellido: %s\n", lista->dato.nombreApe);
        printf("Nota: %i\n", lista->dato.nota);
        printf("........................");

        recorrer_lista_de_alumnos(lista->siguiente);
    }
}
void mostrar_arreglo(celda arreglo[], int validos, char materia)
{

    int i = 0;

    for(i=0; i < validos; i++)
    {

        if(strcmp(arreglo[i].materia, materia) == 0)
        {

            printf("\n#ID de la materia: %i", arreglo[i].idMateria);
            printf("\nMateria: %s", arreglo[i].materia);
            printf("\nAlumnos inscriptos: \n\n");

            recorrer_lista_de_alumnos(arreglo[i].listaDeNotas);


        }
    }
}

