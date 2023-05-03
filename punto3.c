#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#define MAX 120
struct Tarea{
int TareaID; //Numerado en ciclo iterativo
char *Descripcion; //
int Duracion; // entre 10 – 100
};
typedef struct Tarea Tarea;
typedef struct Nodo Nodo;
struct Nodo{
Tarea T;
Nodo *Siguiente;
};


//FUNCIONES
Nodo* crearListaVacia();
Tarea cargarTarea(int id);
Nodo* CrearNodo(Tarea tarea);
void insertarNodoAlComienzo(Nodo** start,Nodo* nuevo);
void mostrarTarea(Tarea t);
void mostrarTareas(Nodo *start);
void eliminarNodo(Nodo* n);
Nodo* quitarNodo(Nodo **start,int id);
void ListarTareasPendientes(Nodo **start,Nodo **startRealizadas);
Nodo* buscarPorPalabra(Nodo *start,Nodo* startRealizadas,char *palabraBuscada);
Nodo* buscarNodoPorId(Nodo* start, Nodo* startRealizadas,int id);
//MAIN
int main(){
    srand(time(NULL));
    Nodo *startPendientes = crearListaVacia();
    Nodo *startRealizadas = crearListaVacia();
 
    int opcion;
    int id=0;
    int opcion_2;
    
    do
    {   
        printf("    <<<< MENU PRINCIPAL >>>>\n");
        printf("seleccione que operacion quiere realizar\n");
        printf("/1: añadir una tarea/\n");
        printf("/2: listar y actualizar las tareas pendientes/\n");
        printf("/3: mostrar tareas pendientes/\n");
        printf("/4: mostrar tareas realizadas/\n");
        printf("/5: buscar tarea por id/\n");
        printf("/6: buscar tarea por palabra clave/\n");
        scanf("%d",&opcion);
        switch (opcion)
        {
        case 1:
            do
            {
                Tarea tarea;
                id++;
                tarea = cargarTarea(id);
                Nodo* nuevoNodo = CrearNodo(tarea);
                insertarNodoAlComienzo(&startPendientes,nuevoNodo);
                printf("Desea agregar una nueva tarea? (0: no // 1: Sí)\n");
                scanf("%d",&opcion_2);   
            } while (opcion_2 != 0);
            break;
        case 2:
            ListarTareasPendientes(&startPendientes,&startRealizadas);
            break;
        case 3:
            mostrarTareas(startPendientes);
            break;
        case 4:
            mostrarTareas(startRealizadas);
            break;
        case 5:
            int id_buscado;
            printf(" **** MENU DE BUSQUEDA POR ID ****\n");
            printf("ingrese el ID de la tarea que esta buscando:\n");
            scanf("%d",&id_buscado);
            Nodo *buscado = buscarNodoPorId(startPendientes,startRealizadas,id_buscado);
            if (buscado)
            {
                mostrarTarea(buscado->T);
            }
            free(buscado);
            break;   
        case 6:
            char *buff;
            buff=(char*)malloc(sizeof(char)*MAX);
            char *palabraBuscada;
            printf("ingrese la palabra clave que busca:\n");
            fflush(stdin);
            gets(buff);
            palabraBuscada =(char*)malloc(sizeof(char)*(strlen(buff)+1));
            strcpy(palabraBuscada,buff);
            free(buff);
            Nodo *resultado_x = buscarPorPalabra(startPendientes,startRealizadas,palabraBuscada);
            if (resultado_x)
            {
                mostrarTarea(resultado_x->T);
            } else{
                printf("no se encontro la tarea\n");
            }
            free(resultado_x);
            break;
        default:
            break;
        }
    } while (opcion != 0);
    
    
}

// ALGORITMO DE LOS MODULOS

Nodo* crearListaVacia()
{
    return NULL;
}

Tarea cargarTarea(int id)
{
    Tarea T;
    char *buff;
    buff = (char*)malloc(sizeof(char)*MAX);
    T.TareaID = id;
    printf("***menu de carga de Tarea***\n");
    printf("ingrese la descripcion de la tarea:\n");
    fflush(stdin);
    gets(buff);
    T.Descripcion = (char*)malloc(sizeof(char)*(strlen(buff)+1));
    strcpy(T.Descripcion,buff);
    free(buff);
    T.Duracion = (rand() %91) + 10;
    return(T);
}
    
    


Nodo* CrearNodo(Tarea tarea)
{
    Nodo* NNodo = (Nodo*)malloc(sizeof(Nodo));
    NNodo->T.TareaID = tarea.TareaID;
    NNodo->T.Descripcion = tarea.Descripcion;
    NNodo->T.Duracion = tarea.Duracion;
    NNodo->Siguiente = NULL;
    return(NNodo);
}

void insertarNodoAlComienzo(Nodo** start,Nodo* nuevo)
{
    nuevo->Siguiente = *start;
    *start = nuevo;
}


void mostrarTarea(Tarea t)
{
    printf("ID de la tarea:%d\n",t.TareaID);
    printf("Descripcion:");
    puts(t.Descripcion);
    printf("Duracion de la tarea:%d\n",t.Duracion);

}

void mostrarTareas(Nodo *start)
{   
    Nodo *aux = start;
    while (aux)
    {
        mostrarTarea(aux->T);
        aux = aux->Siguiente;
        printf("------------------\n");
    }
    
 
}

Nodo* quitarNodo(Nodo **start,int id)
{
    Nodo *aux = *start;
    Nodo *auxAnterior = *start;
    while (aux && aux->T.TareaID != id)
    {
        auxAnterior = aux;
        aux = aux->Siguiente;    
    }
    if (aux)
    {
        if (aux == *start)
        {             
            *start = aux->Siguiente;
        }
        else
        {
            auxAnterior->Siguiente = aux->Siguiente;
        }
        aux->Siguiente = NULL;
    }
    return aux;
}

// Nodo* quitarNodo(Nodo **start,int id)
// {
//     Nodo *aux = *start;
//     Nodo *auxAnterior = *start;
//     while (aux && aux->T.TareaID != id)
//     {
//         auxAnterior = aux;
//         aux = aux->Siguiente;
//     }

//     if (aux)
//     {
//         if (aux == *start)
//         {
//             *start = aux->Siguiente;
//         }
//         else
//         {
//             auxAnterior->Siguiente = aux->Siguiente;
//         }
//         aux->Siguiente = NULL;
//     }
//     return aux;
// }


void eliminarNodo(Nodo* n){
    if(n){
        if(n->T.Descripcion){
            free(n->T.Descripcion); 
        }
        free(n);
    }
}

// void ListarTareasPendientes(Nodo **start,Nodo **startRealizadas){
//     Nodo *aux = *start;
//     int preg;
//     while (aux)
//     {
//         mostrarTarea(aux->T);
        
//         printf("realizo esta tarea? / 1: si / 0: no\n");
//         scanf("%d",&preg);
//         if (preg ==1)
//         {
//           Nodo* quitar = quitarNodo(start,aux->T.TareaID);
//           insertarNodoAlComienzo(startRealizadas,quitar);  
//         }
//         aux = aux->Siguiente;
//         printf("-------------------\n");

//     }
// }


void ListarTareasPendientes(Nodo **start,Nodo **startRealizadas){
    Nodo* aux = *start;
    Nodo* k;
    int preg;
    while (aux)
    {
        mostrarTarea(aux->T);
        printf("realizo esta tarea? / 1: si / 0: no\n");
        scanf("%d",&preg);
        if (preg ==1)
        {
            k = aux;
            aux = aux->Siguiente;
            Nodo* quitar = quitarNodo(start,k->T.TareaID);
            insertarNodoAlComienzo(startRealizadas,quitar); 
            
        }else
        {
            aux = aux->Siguiente;
        }
        printf("-------------------\n");
    }
}


Nodo* buscarNodoPorId(Nodo* start, Nodo* startRealizadas,int id){
    Nodo* auxPendiente = start;
    Nodo* auxRealizadas = startRealizadas;

    while (auxPendiente)
    {
        if (auxPendiente->T.TareaID == id)
        {   
            printf("La tarea fue satisfactoriamente encontrada entre la lista de tareas pendientes:\n");
            return(auxPendiente);
        }
        auxPendiente = auxPendiente->Siguiente;
    }

    while (auxRealizadas)
    {
        if (auxRealizadas->T.TareaID == id)
        {
            printf("La tarea fue satisfactoriamente encontrada entre la lista de tareas realizadas\n:");
            return(auxRealizadas);
        }
        auxRealizadas = auxRealizadas->Siguiente;
    }

    return (NULL);
}


Nodo* buscarPorPalabra(Nodo *start,Nodo* startRealizadas,char *palabraBuscada)
{
    Nodo* auxpend = start;
    while (auxpend)
    {
        if (strstr(auxpend->T.Descripcion,palabraBuscada))
        {
            printf("La tarea fue satisfactoriamente encontrada entre la lista de tareas pendientes:\n");
            return(auxpend);
        }
        auxpend = auxpend->Siguiente;
    }

    Nodo* auxrealizadas = startRealizadas;
    while (auxrealizadas)
    {
        if (strstr(auxrealizadas->T.Descripcion,palabraBuscada))
        {
            printf("La tarea fue satisfactoriamente encontrada entre la lista de tareas realizadas\n:");
            return(auxrealizadas);
        }
        auxrealizadas = auxrealizadas->Siguiente;
    } 
}

//ESTA IMPLEMENTACION FUNCIONARIA IGUAL QUE LA DE LA TEORIA?
// no deberia poner nuevo->siguiente = NULL??
void insertarNodoAlFinal(Nodo* start,Nodo* nuevo)
{
    Nodo* aux = start;
    while (aux)
    {
        aux = aux->Siguiente;
    }
    aux = nuevo;
}



void liberarMemoria(Nodo**start)
{
    Nodo *aux;
    while (*start != NULL)
    {
        aux = *start; 
        *start = (*start)->Siguiente; 
        free(aux->T.Descripcion); 
        free(aux); 
    }
    //se libera start??
}