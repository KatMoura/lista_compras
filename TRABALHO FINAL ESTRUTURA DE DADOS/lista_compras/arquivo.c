#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void exportarCSV(filaprioridade *fila) {
    FILE *arquivo = fopen("lista.csv", "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    item *atual = fila->inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%s,%d,%.2f,%d,%s,%d\n",
                atual->nome, atual->quantidade, atual->preco,
                atual->prioridade, atual->categoria, atual->comprado);
        atual = atual->proximo;
    }

    fclose(arquivo);
    printf("Lista exportada com sucesso!\n");
}

void importarCSV(filaprioridade *fila) {
    FILE *arquivo = fopen("lista.csv", "r");
    if (!arquivo) {
        printf("Arquivo não encontrado.\n");
        return;
    }
    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo)) {
        item *novo = (item *)malloc(sizeof(item));
        if (novo == NULL) {
            printf("Erro de alocação de memória!\n");
            continue;
        }
        
        sscanf(linha, "%[^,],%d,%f,%d,%[^,],%d",
               novo->nome, &novo->quantidade, &novo->preco,
               &novo->prioridade, novo->categoria, &novo->comprado);

        novo->proximo = NULL;

        if (fila->inicio == NULL) {
            fila->inicio = novo;
            fila->fim = novo;
        } else {
            item *atual = fila->inicio;
            item *anterior = NULL;

            while (atual != NULL && atual->prioridade <= novo->prioridade) {
                anterior = atual;
                atual = atual->proximo;
            }
            
            if (anterior == NULL) {
                novo->proximo = fila->inicio;
                fila->inicio = novo;
            } else {
                anterior->proximo = novo;
                novo->proximo = atual;
                
                if (atual == NULL) {
                    fila->fim = novo;
                }
            }
        }
    }

    fclose(arquivo);
    printf("Lista importada com sucesso!\n");
}