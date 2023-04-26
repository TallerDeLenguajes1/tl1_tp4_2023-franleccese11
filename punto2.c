#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MAX 120

struct Tarea {
int TareaID; //Numerado en ciclo iterativo
char *Descripcion;
int Duracion; // entre 10 – 100
}typedef Tarea;

//FUNCIONES

void initializeArray(Tarea **task, int n);
void chargeTask(Tarea **task, int id);
void showTaskQuest(Tarea **task,Tarea **task_completed,int id);
void showTask(Tarea **task);
void showTaskCompleted(Tarea **task_completed, int id);
void showOutStandingTask(Tarea **task,int id);
Tarea* searchTaskWord(Tarea **task, Tarea **task_completed,int quantity);
Tarea* searchTaskId(Tarea **task,Tarea **task_completed,int id,int id_searched);
void menu(Tarea **task, Tarea **task_completed, int quantity);


int main(){
    srand(time(NULL));
    int quantity;
    printf("cuantas tareas debe realizar?\n");
    scanf("%d",&quantity);
    Tarea **array_task;
    Tarea **task_completed;
    array_task = (Tarea**)malloc(sizeof(Tarea*)*quantity);
    task_completed = (Tarea**)malloc(sizeof(Tarea*)*quantity);
    int bool_task;

    initializeArray(array_task,quantity);
    initializeArray(task_completed,quantity);
    for (int id = 0; id < quantity; id++)
    {
        chargeTask(array_task+id,id);
        
    }
    printf("******Tareas pendientes******\n");
    for (int id = 0; id < quantity; id++)
    {
        showTaskQuest(array_task+id,task_completed+id,id);
    }
    puts("*/*/* TAREAS COMPLETADAS */*/*\n");
    for (int id = 0; id < quantity; id++)
    {
      showTaskCompleted(task_completed+id,id);  
    }
    for (int id = 0; id < quantity; id++){ 
        showOutStandingTask(array_task+id,id);
    }
}

 //MODULOS QUE USE

void initializeArray(Tarea **task, int n){
    for (int i = 0; i < n; i++)
    {
        task[i] = NULL;
    }
}

void chargeTask(Tarea **task, int id){
    char *buff;
    buff = (char*)malloc(sizeof(char)*MAX);
    *task = (Tarea*) malloc(sizeof(Tarea));
    (*task)->TareaID = id+1;
    printf("ingrese la descripcion de la tarea numero:%d\n",id+1);
    fflush(stdin);
    gets(buff);
    int length = strlen(buff);
    (*task)->Descripcion = (char*)malloc(sizeof(char)*(length+1));
    strcpy((*task)->Descripcion,buff);
    printf("ingrese la duracion estimada de la tarea:\n");
    fflush(stdin);
    scanf("%d",&(*task)->Duracion);
    free(buff);
}


void showTaskQuest(Tarea **task, Tarea **task_completed, int id){
    int question;
    printf("Tarea numero:%d\n",id+1);
    printf("descripcion de la tarea:");
    puts((*task)->Descripcion);
    printf("la duracion estimada de la tarea es:%d\n",(*task)->Duracion);
    printf("esta tarea fue realizada? (si=1 // no = 0)\n");
    scanf("%d",&question);
    if (question)
    {
        *task_completed = *task;
        *task = NULL;
    }  
}

void showTask(Tarea **task){
    printf("descripcion de la tarea:");
    puts((*task)->Descripcion);
    printf("la duracion estimada de la tarea es:%d\n",(*task)->Duracion);
}


void showTaskCompleted(Tarea **task_completed, int id){
    if (*task_completed != NULL)
    {
        printf("Tarea numero:%d\n",id+1);
        printf("descripcion de la tarea:");
        puts((*task_completed)->Descripcion);
        printf("la duracion estimada de la tarea es:%d\n",(*task_completed)->Duracion);
    }   
}

void showOutStandingTask(Tarea **task,int id){
    if (*task != NULL)
    {
        printf("Tarea numero:%d\n",id+1);
        printf("descripcion de la tarea:");
        puts((*task)->Descripcion);
        printf("la duracion estimada de la tarea es:%d\n",(*task)->Duracion);
    } 
}

Tarea* searchTaskWord(Tarea **task, Tarea **task_completed,int quantity){
    char *buff;
    char *needle;
    buff = (char*) malloc(sizeof(char)*MAX);
    printf("ingrese la palabra clave de la tarea que busca:\n");
    gets(buff);
    needle = (char*)malloc(sizeof(char)*(strlen(buff)+1));
    strcpy(needle,buff);
    free(buff);
    for (int id = 0; id < quantity; id++)
    {
        char *result = strstr((*(task+id))->Descripcion,needle);
        char *result_x = strstr((*(task_completed+id))->Descripcion,needle);
        if (*result != NULL)
        {
            return(*task);
        }else
        {
            if (*result_x != NULL)
            {
                return(*task_completed);
            }
        } 
    }
    Tarea *aux=(Tarea*) malloc(sizeof(Tarea));    
    (aux)->TareaID = -1;
    return(aux);  
} 

Tarea* searchTaskId(Tarea **task,Tarea **task_completed,int quantity,int id_searched){
    for (int i = 0; i < quantity; i++)
    {
        if (*(task+i) != NULL)
        {
        
            if((*(task+i))->TareaID == id_searched) { 
                return(*(task+i));
            }
        }

        if (*(task_completed+i) != NULL)
        {
            if ((*(task_completed+i))->TareaID == id_searched){
                return (*(task_completed+i))
            }
        }  
    }
    Tarea *aux=(Tarea*) malloc(sizeof(Tarea));    
    (aux)->TareaID = -1;
    return(aux);   
}

void menu(Tarea **task, Tarea **task_completed,int quantity){
    int option;
    do
    {
        puts("<<<<<< MENU >>>>>>\n");
        puts("seleccione una de las siguientes opciones:\n");
        puts("<< 0: salir del menu>>\n");
        puts("<< 1: buscar tarea por ID\n");
        puts("<< 2: buscar tarea por palabra clave\n");
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            int id_searched;
            puts("**busqueda por ID**\n");
            puts("ingrese el ID de la tarea que busca:\n");
            scanf("%d",&id_searched);
            Tarea* aux = searchTaskId(task,task_completed,quantity,id_searched);
            break;
        
        case 2:
            puts("**busqueda de la tarea por palabra clave:\n");
            puts("ingrese la palabra clave:\n");
            Tarea* aux = searchTaskWord(task,task_completed,quantity);
            break;
        default:
            puts("numero ingresado no valido, vuelva a ingresar un numero valido:\n");
            scanf("%d",&option);
            break;    
        }
        if (aux->TareaID != -1)
        {
            printf("la tarea fue encontrada satisfactoriamente:\n");
            showTask(aux);
        }else
        {
            printf("no se encontro la tarea");
        }
        
        
    } while (option != 0);
}

void freeMemory(Tarea **task, Tarea **task_completed,int quantity){
    for (int i = 0; i < quantity; i++)
    {
        if (*(task+i) != NULL)
        {
            free((*(task+i))->Descripcion);
        }

        if (*(task_completed+i) != NULL)
        {
            free((*(task_completed+i))->Descripcion);
        }
        free(*(task+i));
        free(*(task_completed+i))
    }
    free(task);
    free(task_completed);
}






//printf("su tarea solicitada fue encontrada\n");
        //    printf("La tarea se encuentra entre la lista de tareas pendientes\n");
          //  printf("descripcion de la tarea:");