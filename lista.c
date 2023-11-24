#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo {
    struct sNodo* prev;
    struct sNodo* next; 
    char* dado;
} Nodo;

typedef struct {
    struct sNodo* head;
    struct sNodo* tail;
    int size;
} Lista;

Nodo* criaNodo(char*);
Lista* criaLista();
int listaVazia(Lista*);
void trataErro(char*);
char* inserir(Lista*, Nodo*, char*);
char* remover(Lista*, Nodo*);
void escreveLista(Lista*);
void escreveListaContrario(Lista*);
Nodo* buscar(Lista*, char*);
int buscarPosicaoNodo(Lista*, Nodo*);
int existe(Lista*, char*);

Nodo* criaNodo(char* dado) {
    Nodo* novo;
    novo = (Nodo*) malloc(sizeof(Nodo));
    if (novo != NULL) {
        novo->dado = (char*) malloc(sizeof(dado));
        strcpy(novo->dado, dado);
        novo->prev = NULL;
        novo->next = NULL;
    }
    
    return novo;
}

Lista* criaLista() {
    Lista* lista;
    lista = (Lista*) malloc(sizeof(Lista));
    if (lista != NULL) {
        lista->head = NULL;
        lista->tail = NULL;
        lista->size = 0;
    }
    
    return lista;
}

int listaVazia(Lista* lista) {
    if (lista->size == 0) 
        return 1;
    return 0;
}

void trataErro(char* erro) {
    if (strcmp(erro, ".1") == 0) 
        printf("\n\tLista vazia!\n");
    if (strcmp(erro, ".2") == 0)
        printf("\n\tFim da lista!\n");
    if (strcmp(erro, ".3") == 0)
        printf("\nO pivô só pode ser NULL na inserção do primeiro elemento!\n");
    if (strcmp(erro, ".4") == 0)
        printf("\nElemento não encontrado!\n");
    if (strcmp(erro, ".5") == 0)
        printf("\nOverflow!\n");
}

char* inserir(Lista* lista, Nodo* elemento_pivo, char* dado) {
	Nodo* novo_elemento;
	novo_elemento = criaNodo(dado);
	
	if (novo_elemento == NULL)
	    return ".5";

	if ((elemento_pivo == NULL) && (!listaVazia(lista))) 
		return ".3";
	
	if (listaVazia(lista)) {
	    lista->head = novo_elemento;
	    lista->tail = novo_elemento;
	} else {
	    novo_elemento->next = elemento_pivo->next;
	    novo_elemento->prev = elemento_pivo;
	    
	    if (elemento_pivo->next == NULL)
	        lista->tail = novo_elemento;
	    else
	        elemento_pivo->next->prev = novo_elemento;
	        
        elemento_pivo->next = novo_elemento;
	}
	lista->size++;
}

char* remover(Lista* lista, Nodo* elemento_pivo) {
	if (listaVazia(lista))
		return ".1";
	
	if ((elemento_pivo!=NULL) && (!listaVazia(lista))) {
        if (elemento_pivo == lista->head) {
            lista->head = elemento_pivo->next;
            
            if (lista->head == NULL)
                lista->tail = NULL;
            else
                elemento_pivo->next->prev = NULL;
        } else {
            elemento_pivo->prev->next = elemento_pivo->next;
            
            if (elemento_pivo->next == NULL) 
                lista->tail = elemento_pivo->prev;
            else
                elemento_pivo->next->prev = elemento_pivo->prev;
        }
	    lista->size--;
	    
	    Nodo* removido;
	    removido = elemento_pivo;
        free(elemento_pivo);
        return removido->dado; 
    }
}

void escreveLista(Lista* lista) {
    Nodo* nodo;
    
    if (listaVazia(lista)) 
        trataErro(".1");
    else {
        nodo = lista->head;
        while (nodo != NULL) {
            printf("\n\t%s", nodo->dado);
            nodo = nodo->next;
        }
    }
}

void escreveListaContrario(Lista* lista) {
    Nodo* nodo;
    
    if (listaVazia(lista)) 
        trataErro(".1");
    else {
        nodo = lista->tail;
        while (nodo != NULL) {
            printf("\n\t%s", nodo->dado);
            nodo = nodo->prev;
        }
    }
}

Nodo* buscar(Lista* lista, char* dado) {
    Nodo* nodo;
    int cont = 1;
    nodo = lista->head;
    while (nodo != NULL) {
        if (strcmp(dado, nodo->dado) == 0) 
            return nodo;
        nodo = nodo->next;
        cont++;
    }
}

int buscarPosicaoNodo(Lista* lista, Nodo* nodo) {
    Nodo* aux;
    int cont = 1;
    aux = lista->head;
    while (aux != NULL) {
        if (aux == nodo) 
            return cont;
        aux = aux->next;
        cont++;
    }
}

int existe(Lista* lista, char* dado) {
    Nodo* nodo;
    int cont = 1;
    nodo = lista->head;
    while (nodo != NULL) {
        if (strcmp(dado, nodo->dado) == 0) 
            return 1;
        nodo = nodo->next;
        cont++;
    }
}
