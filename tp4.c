#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//DECLARACION DE ESTRUCTURAS43

struct{
int TareaID;//Numérico autoincremental comenzando en 1000
char *Descripcion; //
int Duracion; // entre 10 – 100
} typedef Tarea;


typedef struct Nodo{
Tarea T;
struct Nodo *Siguiente;
}Nodo;


//DECLARACION DE FUNCIONES
Nodo *CargarLista();
Nodo *CrearNodo(int *id);
void EnlazarEnLista(Nodo *nodo , Nodo **lista);
void MostrarLista(Nodo **Lista);
void MostrarTarea(Nodo *aux);
void MoverDeLista(Nodo **lista1 , Nodo **lista2 , int id);
void FiltarPorId(Nodo **Pendientes, Nodo **Realizados, int id);
void FiltarPorPalabraClave(Nodo **Pendientes, Nodo **Realizados, char *cadena);

//FUNCION PRINCIPAL

int main(){
    int selector;
    int IdRoot = 1000;
    Nodo *TareasPendientes = CargarLista();
    Nodo *TareasRealizadas = CargarLista();

    printf("Bienvenio empleado!\n\n");
    while (1)
    {
        printf("------------------------------------------------------\n");
        printf("Ingrese la tarea que desea realizar:\n");
        printf("1 - Ingresar tareas\n");
        printf("2 - Mover tareas\n");
        printf("3 - Filtrar tareas\n");
        printf("4 - Mostrar tareas\n");
        printf("0 - Salir\n");
        printf("------------------------------------------------------\n");
        scanf("%d", &selector);

        switch (selector)
        {
        case 1 :
        // CASO CREAR UNA NUEVA TAREA: se ingresa en la lista de tareas pendientes un nuevo nodo.
            int aux = 1;
            //Crear n tareas pendientes.
            while (aux)
            {
                //Crear 1 nodo y enlazarlo
                Nodo *nuevoNodo = CrearNodo(&IdRoot);
                EnlazarEnLista(nuevoNodo,&TareasPendientes);
                printf("Deseas ingresar otra tarea?\n");
                printf("1 - Si.\n");
                printf("0 - No.\n");
                scanf("%d", &aux);
            }

            break;
        
        case 2 :
            //Marcar tareas como realizadas segun id
            int idBusqueda, salir = 1;

            while (salir)
            {
                printf("Ingrese el id de la tarea que desea marcar como realizada:\n");
                scanf("%d", &idBusqueda);
                if (idBusqueda < IdRoot && idBusqueda > 1000)
                {
                    MoverDeLista(&TareasPendientes, &TareasRealizadas , idBusqueda);
                    printf("Desea mover otra tarea?\n");
                    printf("1 - SI.\n");
                    printf("0 - NO.\n");
                    scanf("%d", &salir);
                }
                else
                {
                    printf("El id ingresado es erroneo. Intente nuevamente.\n");
                }
            }
            break;
        
        case 3 :
            // Filtrar tareas
            int filtro;
            do
            {
                filtro = 0;
                printf("Ingrese el tipo de filtrado que desea hacer: \n");
                printf("1 - Por Id.\n");
                printf("2 - Por Cadena.\n");
                printf("0 - Salir.\n");
                scanf("%d", &filtro);
                switch (filtro)
                {
                case 1:
                    int idFiltro;
                    printf("Ingrese el id a buscar:\n"),
                    scanf("%d", &idFiltro);
                    if (idFiltro < IdRoot && idFiltro > 1000)
                    {
                        FiltarPorId(&TareasPendientes, &TareasRealizadas, idFiltro);
                    }
                    else{
                        printf("\nID INEXISTENTE\n");
                    }
                    break;
                case 2:
                    char *palabraClave = (char*) calloc(50 , sizeof(char));
                    printf("Ingrese la palabra clave:\n");
                    getchar();
                    gets(palabraClave);
                    FiltarPorPalabraClave(&TareasPendientes, &TareasRealizadas , palabraClave);
                    free(palabraClave);
                    break;
                default:
                    break;
                }
            }
            while(filtro == 1 || filtro == 2);
            break;
        case 4: 
            printf("\n\nTareas Pendientes:\n");
            MostrarLista(&TareasPendientes);
            printf("\n\nTareas Realizadas:\n");
            MostrarLista(&TareasRealizadas);
            break;
        case 0 : 
                return 1;
            break;
        default:
            printf("Opcion erronea, intente nuevamente.\n");
            break;
        }
    }
    
return 1;
}


//DEFINICION DE FUNCIONES
Nodo *CargarLista(){
    return NULL;
}

Nodo *CrearNodo(int *id)
{
    Nodo* aux = (Nodo*) malloc(sizeof(Nodo));
    char *desc = (char*) malloc(sizeof(char) * 100);

    //Pido que se ingrese la descripcion
    printf("Ingrese la descripción de la tarea:\n");
    getchar();
    fflush(stdin);
    fgets(desc, 100, stdin);
    aux->T.Descripcion = malloc(sizeof(char) * (strlen(desc) + 1));
    strcpy(aux->T.Descripcion, desc);
    //Genero una id 
    *id = *id + 1;
    aux->T.TareaID = *id;
    //Genero un numero aleatorio para la duración
    aux->T.Duracion = rand() % 90 + 10;
    //Enlazo el nodo a una lista vacia
    aux->Siguiente = NULL;

    return aux;
}

void EnlazarEnLista(Nodo *nodo, Nodo **lista)
{
    //ASIGNAR NODO AL INICIO DE LA LISTA

    nodo->Siguiente = *lista;
    *lista = nodo;  

    //ASIGNAR NODOS AL FINAL DE LA LISTA
    // if (*lista == NULL)
    // {
    //     *lista = nodo;
    // }
    // else
    // {
    //     Nodo *temp = *lista;
    //     while (temp->Siguiente != NULL)
    //     {
    //         temp = temp->Siguiente;

    //     }
    //     temp->Siguiente = nodo;
    // }
}

void MostrarLista(Nodo **Lista)
{
    Nodo *aux = *Lista;
    while (aux)
    {
        MostrarTarea(aux);
        aux = aux->Siguiente;
    }
}

void MostrarTarea(Nodo *aux)
{
    printf("\n------------------------------------------------\n");
    puts("Descripcion:");
    puts(aux->T.Descripcion);
    printf("Duración: %d.\n", aux->T.Duracion);
    printf("Id : %d.\n", aux->T.TareaID);
    printf("\n------------------------------------------------\n");
}

void MoverDeLista(Nodo **lista1, Nodo **lista2, int id)
{
    Nodo *aux = *lista1;// Lista a desinsertar.
    Nodo *aux2 = *lista2;// Lista a insertar. 
    Nodo *ant = NULL;//Nodo que nos permitira revincular la lista

    //Buscar en lista1 el nodo a mover
    while (aux->T.TareaID != id)
    {
        ant = aux;
        aux = aux->Siguiente;

    }
    //Desvincular el nodo con el id buscado

    ant->Siguiente = aux->Siguiente;//El nodo deja de estar vinculado a la lista
    aux->Siguiente = NULL;// El nodo está listo para ser insertado en otra lista

    //Enlazamos el nodo a la siguiente lista
    EnlazarEnLista(aux, lista2);
}

void FiltarPorId(Nodo **Pendientes, Nodo **Realizados, int id)
{
    Nodo *aux = *Pendientes;
    Nodo *aux2 = *Realizados;

    while (aux || aux2)
    {
        if (aux && aux->T.TareaID == id)
        {
            MostrarTarea(aux);
            printf("Perteneciente a PENDIENTES\n\n");
        }
        if (aux2 && aux2->T.TareaID == id)
        {
            MostrarTarea(aux2);
            printf("Perteneciente a REALIZADOS\n\n");
        }
        aux = aux ? aux->Siguiente : NULL;
        aux2 = aux2 ? aux2->Siguiente : NULL;
    }
}

void FiltarPorPalabraClave(Nodo **Pendientes, Nodo **Realizados, char *cadena)
{
    Nodo *aux = *Pendientes; 
    Nodo *aux2 = *Realizados;

    printf("Coincidencias en PENDIENTES:\n\n");
    while (aux != NULL)
    {
        if (strstr(aux->T.Descripcion, cadena))
        {
            MostrarTarea(aux);
        }
        aux = aux->Siguiente;
    }
    printf("Coincidencias en REALIZADAS:\n\n");
    while (aux2 != NULL)
    {
        if (strstr(aux2->T.Descripcion, cadena))
        {
            MostrarTarea(aux2);
        }
        aux2 = aux2->Siguiente;
    }
    
}
