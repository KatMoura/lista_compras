#include "lista.h"
#include <stdio.h>
#include <string.h>

void ordenarPorNome(filaprioridade *fila) {
    if (fila->inicio == NULL || fila->inicio->proximo == NULL) return;
    
    int trocou;
    item *anterior, *atual, *proximo;
    
    do {
        trocou = 0;
        anterior = NULL;
        atual = fila->inicio;
        proximo = atual->proximo;
        
        while (proximo != NULL) {
            if (strcmp(atual->nome, proximo->nome) > 0) {
                if (anterior == NULL) {
                    fila->inicio = proximo;
                } else {
                    anterior->proximo = proximo;
                }
                atual->proximo = proximo->proximo;
                proximo->proximo = atual;
                
                item *temp = atual;
                atual = proximo;
                proximo = temp;
                
                trocou = 1;
            }
            
            anterior = atual;
            atual = proximo;
            proximo = proximo->proximo;
        }
        
        item *temp = fila->inicio;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        fila->fim = temp;
        
    } while (trocou);
    printf("Lista ordenada por nome.\n");
}

void ordenarPorCategoria(filaprioridade *fila) {
    if (fila->inicio == NULL || fila->inicio->proximo == NULL) return;
    
    int trocou;
    item *anterior, *atual, *proximo;
    
    do {
        trocou = 0;
        anterior = NULL;
        atual = fila->inicio;
        proximo = atual->proximo;
        
        while (proximo != NULL) {
            if (strcmp(atual->categoria, proximo->categoria) > 0) {
                if (anterior == NULL) {
                    fila->inicio = proximo;
                } else {
                    anterior->proximo = proximo;
                }
                atual->proximo = proximo->proximo;
                proximo->proximo = atual;
                
                item *temp = atual;
                atual = proximo;
                proximo = temp;
                
                trocou = 1;
            }
            
            anterior = atual;
            atual = proximo;
            proximo = proximo->proximo;
        }
        
        item *temp = fila->inicio;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        fila->fim = temp;
        
    } while (trocou);
    printf("Lista ordenada por categoria.\n");
}

void ordenarPorPrioridade(filaprioridade *fila) {
    if (fila->inicio == NULL || fila->inicio->proximo == NULL) return;
    
    int trocou;
    item *anterior, *atual, *proximo;
    
    do {
        trocou = 0;
        anterior = NULL;
        atual = fila->inicio;
        proximo = atual->proximo;
        
        while (proximo != NULL) {
            if (atual->prioridade > proximo->prioridade) {
                if (anterior == NULL) {
                    fila->inicio = proximo;
                } else {
                    anterior->proximo = proximo;
                }
                atual->proximo = proximo->proximo;
                proximo->proximo = atual;
                
                item *temp = atual;
                atual = proximo;
                proximo = temp;
                
                trocou = 1;
            }
            
            anterior = atual;
            atual = proximo;
            proximo = proximo->proximo;
        }
        
        item *temp = fila->inicio;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        fila->fim = temp;
        
    } while (trocou);
    printf("Lista ordenada por prioridade.\n");
}