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

void cargar_archivo(FILE* archivo);
void mostrar_archivo(FILE* archivo);

/// MAIN ///

int main()
{

    FILE* archivo;

    cargar_archivo(archivo);
    mostrar_archivo(archivo);

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

    return NULL
}
nodo* crear_nodo(registroArchivo dato)
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

nodo* crear_nodo_alumno(nodo* lista, registroArchivo dato)
{
    if(lista)
    {

        nodo* nuevoNodo = inic_nodo();

        nuevoNodo = crear_nodo(dato);

        lista = agregar_pricipio(lista, nuevoNodo);
    }

    return lista;
}
int archivo_a_arreglo(celda arreglo[], int dim, FILE* archivo)
{

    fopen = ("miArchivo.bin", "rb");
    registroArchivo aux;

    int i = 0;
    int falg = 0;

    if(archivo)
    {

        while(fread(&aux, sizeof(registroArchivo), 1, archivo) > 0)
        {


        }

        fclose(archivo);
    }


    return validos;
}


int buscar_posicion(celda arreglo[], registroArchivo alumno)
{
    int i = 0;

   while(i<dimension)
   {

    if((strcmp(celda[i].materia, alumno.materia) != 0))
    {


    }

}
}
