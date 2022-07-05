#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int info;
    struct nodo *sigNodo;
}*QUEUE;

typedef struct 
{
    QUEUE frente;
    QUEUE final;
}QUEUE_CA; //QUEUEs agrupadas

int crearNodo(QUEUE *cab, int dato) {
    int res = 0;
    *cab = (QUEUE)malloc(sizeof(struct nodo));

    if (*cab) {
        (*cab)->info = dato;
        (*cab)->sigNodo = NULL;
        res = 1;
    }
    return res;
}

void iniQueueCA(QUEUE_CA *f)
{
    f->frente = f->final = NULL;
}

int insQueue(QUEUE_CA *cab, int dato) {
    int res = 0;
    QUEUE nuevo;
    res = crearNodo(&nuevo, dato);
    if (res) {
        if(cab->frente)
            cab->final->sigNodo = nuevo;
        else
            cab->frente = nuevo;
        cab->final = nuevo;
        res = 1;
    }
    return res;
}

int eliminaQueueCA(QUEUE_CA *f, int *dato)
{
    QUEUE aux;
    int res = 0;
    if (f->frente)
    {
        aux = f->frente;
        f->frente = aux->sigNodo;
        *dato = aux->info;
        free (aux);
        res = 1;
        if(!f->frente)
            f->final = f->frente;
    }
    return res;
}