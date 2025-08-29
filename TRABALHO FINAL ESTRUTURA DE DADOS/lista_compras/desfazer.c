#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

acao *topo = NULL;

void empilharAcao(const char *tipo, item dados) {
    acao *nova = (acao *)malloc(sizeof(acao));
    if (nova == NULL) {
        printf("Erro ao alocar memória para desfazer.\n");
        return;
    }
    strcpy(nova->tipo, tipo);
    nova->dados = dados;
    nova->proximo = topo;
    topo = nova;
}
void desfazer(filaprioridade *fila) {
    if (topo == NULL) {
        printf("Nada para desfazer.\n");
        return;
    }

    acao *ultima = topo;
    topo = topo->proximo;

    if (strcmp(ultima->tipo, "add") == 0) {
        
        item *atual = fila->inicio, *anterior = NULL;
        while (atual != NULL && strcmp(atual->nome, ultima->dados.nome) != 0) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual != NULL) {
            if (anterior == NULL) fila->inicio = atual->proximo;
            else anterior->proximo = atual->proximo;
            free(atual);
            printf("Desfeita adição de %s\n", ultima->dados.nome);
        }
    } else if (strcmp(ultima->tipo, "remove") == 0) {
        item *restaurado = (item *)malloc(sizeof(item));
        *restaurado = ultima->dados;
        restaurado->proximo = fila->inicio;
        fila->inicio = restaurado;
        printf("Desfeita remoção de %s\n", restaurado->nome);
    } else if (strcmp(ultima->tipo, "comprado") == 0) {
        item *atual = fila->inicio;
        while (atual != NULL && strcmp(atual->nome, ultima->dados.nome) != 0) {
            atual = atual->proximo;
        }
        if (atual != NULL) {
            atual->comprado = 0;
            printf("Desfeita marcação de %s como comprado\n", atual->nome);
        }
    }

    free(ultima);
}
