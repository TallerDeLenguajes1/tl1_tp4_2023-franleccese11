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
void showTask(Tarea **task,Tarea **task_completed,int id);
void showTaskCompleted(Tarea **task_completed, int id);
void showOutStandingTask(Tarea **task,int id);


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
        showTask(array_task+id,task_completed+id,id);
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


void showTask(Tarea **task, Tarea **task_completed, int id){
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