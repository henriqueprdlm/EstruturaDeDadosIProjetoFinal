#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 53

int calculaHash(char* dado) { //hash modular
    int hash = 0;
    for (int i = 0; i < strlen(dado); i++) {
        hash = (13 * hash + dado[i]) % M; //M=53 (professor), R=13 (primo)
    }
    return hash;
}