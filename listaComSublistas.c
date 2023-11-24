#include "lista.c"
#include "tabelaHash.c"

typedef struct sNodoListaCS {
    struct sNodoListaCS* prev;
    struct sNodoListaCS* next;
    int hash;
    Lista* sublista;
} NodoListaCS;

typedef struct {
    struct sNodoListaCS* head;
    struct sNodoListaCS* tail;
    int size;
} ListaComSublistas;

NodoListaCS* criaNodoListaCS(int);
ListaComSublistas* criaListaComSublistas(int);
void inserirNodoListaCS(ListaComSublistas*, int);
void inserirElementoHash(ListaComSublistas*, char*);
NodoListaCS* buscarNodoHash(ListaComSublistas*, int);
int buscarHashElemento(ListaComSublistas*, char*);
int listaCSVazia(ListaComSublistas*);
void removerListaCS(ListaComSublistas*);
char* removerCS(ListaComSublistas*, NodoListaCS*);
int tamSublistaHash(ListaComSublistas*, int);

NodoListaCS* criaNodoListaCS(int hash) {
    NodoListaCS* novo;
    novo = (NodoListaCS*) malloc(sizeof(NodoListaCS));
    if (novo != NULL) {
        novo->hash = hash;
        novo->sublista = criaLista();
        novo->prev = NULL;
        novo->next = NULL;
    }
    
    return novo;
}

ListaComSublistas* criaListaComSublistas(int tam) {
    ListaComSublistas* listaCS;
    listaCS = (ListaComSublistas*) malloc(sizeof(ListaComSublistas));
    if (listaCS != NULL) {
        listaCS->head = NULL;
        listaCS->tail = NULL;
        listaCS->size = 0;
    }
    
    for (int i=0; i<tam; i++) {
        inserirNodoListaCS(listaCS, i);
    }
    
    return listaCS;
}

void inserirNodoListaCS(ListaComSublistas* listaCS, int hash) { //nodo da lista CS inserido pelo tail
	NodoListaCS* novo_elemento;
	novo_elemento = criaNodoListaCS(hash);
	NodoListaCS* elemento_pivo = listaCS->tail;
	
	if (listaCSVazia(listaCS)) {
	    listaCS->head = novo_elemento;
	    listaCS->tail = novo_elemento;
	} else {
	    novo_elemento->next = elemento_pivo->next;
	    novo_elemento->prev = elemento_pivo;
	    
	    if (elemento_pivo->next == NULL)
	        listaCS->tail = novo_elemento;
	    else
	        elemento_pivo->next->prev = novo_elemento;
	        
        elemento_pivo->next = novo_elemento;
	}
	listaCS->size++;
}

void inserirElementoHash(ListaComSublistas* listaCS, char* dado) {
    int hash = calculaHash(dado);
    Lista* lista;
    lista = buscarNodoHash(listaCS, hash)->sublista;
    trataErro(inserir(lista, lista->tail, dado));
}

NodoListaCS* buscarNodoHash(ListaComSublistas* listaCS, int hash) {
    NodoListaCS* nodoListaCS;
    nodoListaCS = listaCS->head;
    while (nodoListaCS != NULL) {
        if (nodoListaCS->hash == hash) 
            return nodoListaCS;
        nodoListaCS = nodoListaCS->next;
    }
}

int buscarHashElemento(ListaComSublistas* listaCS, char* dado) {
    NodoListaCS* nodoListaCS;
    nodoListaCS = listaCS->head;
    
    Nodo* nodo;
    while (nodoListaCS != NULL) {
        nodo = nodoListaCS->sublista->head;
        while (nodo != NULL) {
            if (strcmp(nodo->dado, dado) == 0)
                return nodoListaCS->hash;
            nodo = nodo->next;
        }
        nodoListaCS = nodoListaCS->next;
    }
    return -1;
}

int listaCSVazia(ListaComSublistas* listaCS) {
    if (listaCS->size == 0) 
        return 1;
    return 0;
}

void removerListaCS(ListaComSublistas* listaCS) {
	if (listaCSVazia(listaCS))
		trataErro(".1"); 
	
	NodoListaCS* nodoListaCS;
    nodoListaCS = listaCS->head;
    NodoListaCS* nodoListaCSremover;
    
    Nodo* nodoRemover;
    Nodo* nodoProx;
    while (nodoListaCS != NULL) {
        nodoRemover = nodoListaCS->sublista->head;
        while (nodoRemover != NULL) {
            nodoProx = nodoRemover->next;
            trataErro(remover(nodoListaCS->sublista, nodoRemover));
            nodoRemover = nodoProx;
        }
        nodoListaCS = nodoListaCS->next;
    }

    nodoListaCS = listaCS->head;
    while (nodoListaCS != NULL) {
        nodoListaCSremover = nodoListaCS->next;
        trataErro(removerCS(listaCS, nodoListaCS));
        nodoListaCS = nodoListaCSremover;
    }
}

char* removerCS(ListaComSublistas* lista, NodoListaCS* elemento_pivo) {
	if (listaCSVazia(lista))
		return ".1";
	
	if ((elemento_pivo!=NULL) && (!listaCSVazia(lista))) {
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
	    
        free(elemento_pivo);
        return "-1"; 
    }
}

int tamSublistaHash(ListaComSublistas* listaCS, int hash) {
    return buscarNodoHash(listaCS, hash)->sublista->size;
}
