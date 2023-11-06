#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

/// ESTRUCTURAS ///

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

nodo* agregar_pricipio(nodo* lista, nodo* nuevoNodo);
nodo* iniciar_lista();
nodo* crearNodo (notaAlumno info);
void mostrar_lista(nodo* lista);
void cargar_archivo(FILE* archivo);
void mostrar_archivo(FILE* archivo);
void pasarDeADLToArchivoDeAprobados(FILE* aprobados, celda arreglo[], int validos);
int agregar_materia(celda arreglo[], notaAlumno alumno, int validos, char materia[]);
int alta(celda arreglo[], notaAlumno alumno, int validos, char materia[]);
int ingresarNotas (celda arreglo[],FILE* archivo, int dimension);
int buscar_posicion(celda arreglo[], notaAlumno alumno, int validos, char materia[]);


int main()
{

    FILE* archivo_alumnos;
    celda arreglo_materias[30];
    int validos = 0;

    cargar_archivo(archivo_alumnos);
    mostrar_archivo(archivo_alumnos);


    validos = ingresarNotas(arreglo_materias, archivo_alumnos, 20);
    mostrar_arreglo(arreglo_materias, 0, validos);


}

void cargar_archivo(FILE* archivo)
{

    archivo = fopen("miArchivo.bin", "wb");
    char letra = 's';
    registroArchivo datos;

    if(archivo)
    {

        while(letra == 's')
        {
            system("cls");

            printf("Ingrese la #ID de la materia: ");
            fflush(stdin);
            scanf("%i", &datos.idMateria);

            printf("Ingresa el nombre de la materia: ");
            fflush(stdin);
            gets(&datos.materia);


            printf("Ingresa el legajo del alumno: ");
            fflush(stdin);
            scanf("%i", &datos.legajo);

            printf("Ingresa el nombre del alumno: ");
            fflush(stdin);
            gets(&datos.nombreApe);

            printf("Ingresa la nota del alumno: ");
            fflush(stdin);
            scanf("%i", &datos.nota);


            printf("Ingresa 's' para continuar: ");
            fflush(stdin);
            scanf("%c", &letra);

            fwrite(&datos, sizeof(registroArchivo), 1, archivo);

        }

        fclose(archivo);
    }
}

void mostrar_archivo(FILE* archivo)
{
    archivo = fopen("miArchivo.bin", "rb");
    registroArchivo a;

    if(archivo)
    {
        while(fread(&a, sizeof(registroArchivo), 1, archivo ) > 0)
        {
            printf("\n.....................\n");
            printf("ID#: %i\n",a.idMateria);
            printf("Materia %s\n",a.materia);
            printf("Legajo %i\n",a.legajo);
            printf("Nombre del alumno %s\n",a.nombreApe);
            printf("Nota %i\n",a.nota);
        }

        fclose(archivo);
    }
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

nodo* iniciar_lista()
{

    return NULL;
}

nodo* crearNodo (notaAlumno info)
{

    nodo* aux = (nodo*) malloc(sizeof(nodo));

    aux->dato = info;
    aux->siguiente = NULL;

    return aux;
}

void mostrar_lista(nodo* lista)
{

    if(lista)
    {

        printf("\nLegajo: %i\n", lista->dato.legajo);
        printf("Nombre: %s\n", lista->dato.nombreApe);
        printf("Nota: %i\n", lista->dato.nota);

        mostrar_archivo(lista->siguiente);
    }

}

void mostrar_arreglo(celda arreglo[],int i , int validos)
{

    if(i < validos)
        {

        printf("......................\n");
        printf("ARREGLO DE LISTAS: \n\n");
        printf("#ID Materia: %i\n", arreglo[i].idMateria);
        printf("Materia: %s\n", arreglo[i].materia);
        mostrar_lista(arreglo[i].listaDeNotas);
        printf("......................\n\n\n");


        mostrar_arreglo(arreglo, i+1, validos);
        }

}


int ingresarNotas (celda arreglo[], FILE* archivo, int dimension)
{
    archivo = fopen("miArchivo.bin", "rb");

    char letra = 's';
    char materia[20];
    int validos = 0;
    notaAlumno aux;
    registroArchivo alumno;

    if(archivo)
    {

        while(validos < dimension && fread(&alumno, sizeof(registroArchivo), 1, archivo) > 0)
        {

            aux.legajo = alumno.legajo;
            strcpy(aux.nombreApe, alumno.nombreApe);
            aux.nota = alumno.nota;
            strcpy(materia, alumno.materia);

            validos = alta(arreglo, aux, validos, materia);


        }

        fclose(archivo);
    }

    return validos;
}

int alta(celda arreglo[], notaAlumno alumno, int validos, char materia[])
{

    nodo* aux = crearNodo(alumno);

    int pos = buscar_posicion(arreglo, alumno, validos, materia);

    if(pos == -1)
    {

        validos = agregar_materia(arreglo, alumno, validos, materia);
        pos = validos-1;
    }

    arreglo[pos].listaDeNotas = agregar_pricipio(arreglo[pos].listaDeNotas, aux);

    return validos;
}

int buscar_posicion(celda arreglo[], notaAlumno alumno, int validos, char materia[])
{

    int pos = -1;
    int i = 0;

    while(i < validos && pos == -1)
    {
        if(strcmp(arreglo[i].materia, materia) == 0)
        {
            pos = i;
        }

        i++;
    }

    return pos;
}

int agregar_materia(celda arreglo[], notaAlumno alumno, int validos, char materia[])
{

    strcpy(arreglo[validos].materia, materia);

    arreglo[validos].listaDeNotas = iniciar_lista();

    validos++;

    return validos;
}

void pasarDeADLToArchivoDeAprobados(FILE* aprobados, celda arreglo[], int validos)
{

    aprobados = fopen("miAprobados.bin", "wb");
    registroArchivo alumno;
    notaAlumno datos;

    int i = 0;

    if(aprobados)
    {

        for(i = 0; i < validos; i++)
        {

            if(arreglo[i].listaDeNotas->dato.nota >= 6)
            {

                alumno.idMateria = arreglo[i].idMateria;
                strcpy(alumno.materia, arreglo[i].materia);
                alumno.legajo = arreglo[i].listaDeNotas->dato.legajo;
                alumno.nota = arreglo[i].listaDeNotas->dato.nota;
                strcpy(alumno.nombreApe, arreglo[i].listaDeNotas->dato.nombreApe);

                fwrite(&alumno, sizeof(registroArchivo), 1, aprobados);
            }
        }

        fclose(aprobados);
    }
}
