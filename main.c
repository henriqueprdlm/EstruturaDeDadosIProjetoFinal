#include <time.h>
#include <string.h>
#include "quicksort.c"

void lerArquivo(ListaComSublistas*);
void escreverArquivo(ListaComSublistas*);

int main() {
    ListaComSublistas* tabelaHash;
    tabelaHash = criaListaComSublistas(M);

    lerArquivo(tabelaHash);
    quicksortListaCS(tabelaHash);
    escreverArquivo(tabelaHash);
    removerListaCS(tabelaHash); 
}

void lerArquivo(ListaComSublistas* listaCS) {
    FILE *arq;
    char linha[100];
    
    arq = fopen("../nomes.txt", "r"); 
    if (arq == NULL) {
        printf("Problemas na abertura do arquivo\n");
        return;
    }
    
    while (!feof(arq)) {
        fgets(linha, 100, arq); 
        strcpy(linha, strtok(linha, "\n"));
        inserirElementoHash(listaCS, linha);
    }

    fclose(arq);
}

void escreverArquivo(ListaComSublistas* listaCS) {
    FILE *arq;
    
    arq = fopen("ArqGrav.txt", "wt");
    if (arq == NULL) {
        printf("Problemas na CRIACAO do arquivo\n");
        return;
    }

    NodoListaCS* nodoListaCS;
    nodoListaCS = listaCS->head;
    Nodo* nodo;

    fprintf(arq, "***PROJETO FINAL DE ESTRUTURA DE DADOS I***");
    fprintf(arq, "\n\nQUANTIDADE DE ELEMENTOS POR HASH:");
    while (nodoListaCS != NULL) {
        fprintf(arq, "\n\tHash %i: %i", nodoListaCS->hash, tamSublistaHash(listaCS, nodoListaCS->hash));
        nodoListaCS = nodoListaCS->next;
    }

    fprintf(arq, "\n\n*******************************************");
    fprintf(arq, "\n\nELEMENTOS EM CADA HASH:");
    nodoListaCS = listaCS->head;
    while (nodoListaCS != NULL) {
        fprintf(arq, "\n\nHASH %i:", nodoListaCS->hash);
        nodo = nodoListaCS->sublista->head;
        while (nodo != NULL) {
            fprintf(arq, "\n\t%s", nodo->dado);
            nodo = nodo->next;
        }
        nodoListaCS = nodoListaCS->next;
    }

    fclose(arq);
}
