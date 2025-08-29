#include "lista.h"
#include <stdio.h>
#include <string.h>

void relatorioCompras(filaprioridade *fila) {
    struct CategoriaStats {
        char nome[30];
        int total;
        int comprados;
    } stats[20] = {0};
    
    int categoriasCount = 0;
    int total = 0, comprados = 0;
    item *atual = fila->inicio;
    
    while (atual != NULL) {
        total++;
        if (atual->comprado == 1) {
            comprados++;
        }
        
        int encontrada = 0;
        for (int i = 0; i < categoriasCount; i++) {
            if (strcmp(stats[i].nome, atual->categoria) == 0) {
                stats[i].total++;
                if (atual->comprado == 1) stats[i].comprados++;
                encontrada = 1;
                break;
            }
        }
        
        if (!encontrada && categoriasCount < 20) {
            strcpy(stats[categoriasCount].nome, atual->categoria);
            stats[categoriasCount].total = 1;
            stats[categoriasCount].comprados = (atual->comprado == 1) ? 1 : 0;
            categoriasCount++;
        }
        
        atual = atual->proximo;
    }
    
    if (total == 0) {
        printf("Nenhum item na lista.\n");
    } else {
        float porcentagem = ((float)comprados / total) * 100;
        printf("\n=== RELATÓRIO GERAL ===\n");
        printf("Total de itens: %d\n", total);
        printf("Itens comprados: %d (%.2f%%)\n", comprados, porcentagem);
        
        printf("\n=== POR CATEGORIA ===\n");
        for (int i = 0; i < categoriasCount; i++) {
            float porcCat = (stats[i].comprados * 100.0) / stats[i].total;
            printf("%s: %d/%d (%.2f%%) comprados\n", 
                   stats[i].nome, stats[i].comprados, stats[i].total, porcCat);
        }
    }
}