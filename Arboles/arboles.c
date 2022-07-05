#include "CA.h"

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
void capturaDatosABO(AB *a)
{
    int dato, res;
    char resp;

    do
    {
        printf("Dame un dato: ");
        scanf("%d", &dato);
        res = insOrd(a, dato);
        if(res)
        {
            printf("Dato ingresado quieres seguir introduciendo un dato?, \"n\" si no: ");
            scanf("%c", &resp);
        } else {
            printf("No hay memoria\n");
        }
    } while (resp == 's' && res);
}

//-------------------------------------------------------------//
//---------------------------RECORRIDOS------------------------//
//-------------------------------------------------------------//

// Recorido en pre_orden
void preOrden(AB a)
{
    if(a)
    {
        printf("%d\t", a->info);
        preOrden(a->izq);
        preOrden(a->der);
    }
}

// Recorrido en_orden
void enOrden(AB a)
{
    if(a)
    {
        enOrden(a->izq);
        printf("%d\t", a->info);
        enOrden(a->der);

    }
}

// Recorrido en pos_orden
void posOrden(AB a)
{
    if(a)
    {
        posOrden(a->izq);
        posOrden(a->der);
        printf("%d\t", a->info);
    }
}

// Recorrido por niveles
void porNivel(AB a)
{
    QUEUE_CA q;
    iniQueueCA(&q);
    insQueue(&q, a);
    while (eliminaQueueCA(&q, &a))
    {
        printf("%d\t", a->info);
        if (a->izq)
            insQueue(&q, a->izq);
        if(a->der)
            insQueue(&a, a->der);
    }
    
}

// Calcula peso
int calcPeso(AB a)
{
    int peso;
    if(!a)
        peso = 0;
    else
        peso = 1 + calcPeso(a->izq) + calcPeso(a->der);
    return peso;
}

// Calcula costo
int calcCosto(AB a)
{
    int costo;
    if(!a)
        costo = 0;
    else
        costo = a->info + calcCosto(a->izq) + calcCosto(a->der);
    return costo;
}

// Calcula peso de un arbol, entregarlo vía param ref
void calculaPeso(AB a, int *peso)
{
    int pIzq, pDer;

    if(!a)
        *peso = 0;
    else{
        calculaPeso(a->izq, &pIzq);
        calculaPeso(a->der, &pDer);
        *peso = 1 + pIzq + pDer;
    }
}

// Contar el no. de hojas
int cuentaHojas(AB a)
{
    int hojas;
    if(!a)
        hojas = 0;
    else if(!a->izq && !a->der)
        hojas = 1;
    else
        hojas = cuentaHojas(a->izq) + cuentaHojas(a->der);
    return hojas;
}

// Cuenta los elementos internos de un arbol
int cuentaInt(AB a)
{
    int nInt, p = calcPeso(a);

    if(p < 3)
        nInt = 0;
    else
        nInt = p-cuentaHojas(a) - 1;
    return nInt;
}

int buscaAB(AB a,  int buscado)
{
    int res;

    if(!a)
        res = 0;
    else if(buscado == a->info)
        res = 1;
    else{
        res = buscaAB(a->izq, buscado);
        if(!res)
            res = buscaAB(a->der, buscado);
    }
    return res;
}
