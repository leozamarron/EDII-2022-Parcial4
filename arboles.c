#include <stdio.h>
#include <stdlib.h>

//Estructuras

typedef struct nodoAB
{
    struct nodoAB *izq;
    int info;   //<tipo> info;
    struct nodoAB *der;
}*AB;

/*
Operaciones básicas
	- Inicialización 
	- Crear nodo AB
	- Insertar (guiada, ordenada) + captura
	- Recorrido
	- Eliminación (guiada, ordenada)
*/

// Inicialización
void iniGrafo(AB *cab)
{
    *cab = NULL;
}

// Crea nodo AB
int creaNodo(AB *nodo, int dato)
{
    int res = 0;
    *nodo = (AB)malloc(sizeof(struct nodoAB));

    if(*nodo)
    {
        (*nodo)->der = NULL;
        (*nodo)->izq = NULL;
        (*nodo)->info = dato;
        res = 1;
    }
    return res;
}

// *Inserción (guiada)
int insGuiada(AB *a, int dato)
{
    int res;
    char resp;

    if(!*a)
        res = creaNodoAB(a, dato);
    else{
        printf("Hacia donde (i/d)?");
        scanf("%c", &resp);
        if(resp == 'i')
            res = insGuiada(&(*a)->izq, dato);
        else
            res = insGuiada(&(*a)->der, dato);
    }
    return res;
}

// *Ins. ordenada
int insOrd(AB *a, int dato)
{
    int res;

    if(!*a)
        res = creaNodoAB(a, dato);
    else if(dato < (*a)->info)
        res = insOrd(&(*a)->izq, dato);
    else if(dato > (*a)->info)
        res = insOrd(&(*a)->der, dato);
    else
        res = 0;

    return res;
}

// Captura los datos del arbol
int capturaDatosAB(AB *a)
{
    int dato, res;
    char resp;

    do
    {
        printf("Dame un dato: ");
        scanf("%d", &dato);
        insOrd(a, dato);
        printf("Quieres seguir introduciendo un dato?, \"n\" si no: ");
        scanf("%c", &resp);

    } while (resp = 's');

    return res;
}