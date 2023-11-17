#include "listaComSublistas.c"

void quicksortListaCS(ListaComSublistas*);
void quicksort(Nodo*, Nodo*);
Nodo* particao(Nodo*, Nodo*);
void troca(Nodo*, Nodo*);

void quicksortListaCS(ListaComSublistas* listaCS) {
    NodoListaCS* nodoListaCS;
    nodoListaCS = listaCS->head;
    
    while (nodoListaCS != NULL) {
        quicksort(nodoListaCS->sublista->head, nodoListaCS->sublista->tail);
        nodoListaCS = nodoListaCS->next;
    }
}

void quicksort(Nodo* inicio, Nodo* fim) {
    if ((fim != NULL) && (inicio != fim) && (inicio != fim->next)) {
        Nodo* pivo = particao(inicio, fim);
        quicksort(inicio, pivo->prev);
        quicksort(pivo->next, fim);
    }
}

Nodo* particao(Nodo* inicio, Nodo* fim) {
    char* pivo = fim->dado;
    Nodo* i = inicio->prev;

    for (Nodo* j=inicio; j!=fim; j=j->next) {
        if (strcmp(j->dado, pivo) < 0) {
            if (i == NULL) 
                i = inicio;
            else
                i = i->next;
                
            troca(i, j);
        }
    }

    if (i == NULL) 
        i = inicio;
    else
        i = i->next;
                
    troca(i, fim);

    return i;
}

void troca(Nodo* a, Nodo* b) {
    char* aux = a->dado;
    a->dado = b->dado;
    b->dado = aux;
}