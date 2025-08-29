#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void inicializarfila(filaprioridade *fila){
    fila->inicio = NULL;
    fila->fim = NULL;
}


item *alocarLista() {
    return (item *)malloc(sizeof(item));
}

void additem(filaprioridade *fila) {
    item *novo = (item *)malloc(sizeof(item));
    if (novo == NULL) {
        printf("Erro de alocação\n");
        return;
    }
    printf("adicionar item\n");
    printf("Digite o nome do item: ");
    fgets(novo->nome, 50, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo->quantidade);

    printf("preço: R$");
    scanf("%f", &novo->preco); 

    printf("prioridade:(1-5, onde 1 é mais importante): ");
    scanf("%d", &novo->prioridade);
    getchar();

    printf("categoria: ");
    fgets(novo->categoria, 30, stdin);
    novo->categoria[strcspn(novo->categoria, "\n")] = '\0';
    novo->comprado = 0;

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
    empilharAcao("add", *novo);
        printf("Item adicionado com sucesso!\n");
}


void removeritem(filaprioridade *fila){
    if (fila->inicio == NULL) {
        printf("Fila de prioridade vazia\n");
        return;
    }
    
    if (fila->inicio != NULL) {
        empilharAcao("remove", *(fila->inicio));
    }
    item *removido = fila->inicio;
    fila->inicio = fila->inicio->proximo; 

    printf("Item removido: %s\n", removido->nome);
    printf("Nome: %s\n", removido->nome);
    printf("Quantidade: %d\n", removido->quantidade);
    printf("Preço: R$%.2f\n", removido->preco);
    printf("Prioridade: %d\n", removido->prioridade);

    free(removido);

    if (fila->inicio == NULL) {
        fila->fim = NULL; 
    }
}

void editarItem(filaprioridade *fila) {
    char nomeBusca[50];
    printf("Digite o nome do item a editar: ");
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    item *atual = fila->inicio;
    while (atual != NULL) {
        if (strcmp(atual->nome, nomeBusca) == 0) {
            printf("Novo nome: ");
            fgets(atual->nome, 50, stdin);
            atual->nome[strcspn(atual->nome, "\n")] = '\0';

            printf("Nova quantidade: ");
            scanf("%d", &atual->quantidade);

            printf("Novo preço: R$");
            scanf("%f", &atual->preco);

            printf("Nova prioridade (1-5): ");
            scanf("%d", &atual->prioridade);
            getchar();

            printf("Nova categoria: ");
            fgets(atual->categoria, 30, stdin);
            atual->categoria[strcspn(atual->categoria, "\n")] = '\0';

            printf("Item editado com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Item não encontrado.\n");
}
 
void mostrarlista(filaprioridade *fila) {
    if (fila->inicio == NULL) {
        printf("Fila de prioridade vazia\n");
        return;
    }
    printf("\n     Lista de Compras: (Ordenada por prioridade)     \n");
    item *atual = fila->inicio;
    while (atual != NULL) {
        printf("Nome: %s\n", atual->nome);
        printf("Quantidade: %d\n", atual->quantidade);
        printf("Preço: R$%.2f\n", atual->preco);
        printf("Prioridade: %d\n", atual->prioridade);
        printf("                              \n");
        atual = atual->proximo;
    }


}
void marcarComoComprado(filaprioridade *fila) {
    char nomeBusca[50];
    printf("Digite o nome do item a marcar como comprado: ");
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    item *atual = fila->inicio;
    while (atual != NULL) {
        if (strcmp(atual->nome, nomeBusca) == 0) {
            
            item copia = *atual;  
            empilharAcao("comprado", copia);
            atual->comprado = 1;
            printf("Item marcado como comprado!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Item não encontrado.\n");
}
void mostrarUrgentes(filaprioridade *fila) {
    item *atual = fila->inicio;
    printf("\nItens urgentes:\n");
    while (atual != NULL) {
        if (atual->prioridade <= 2 && atual->comprado == 0) {
            printf("Nome: %s | Qtd: %d | Prioridade: %d\n", atual->nome, atual->quantidade, atual->prioridade);
        }
        atual = atual->proximo;
    }
}
void buscarItem(filaprioridade *fila) {
    char termo[50];
    printf("Digite o termo de busca: ");
    fgets(termo, 50, stdin);
    termo[strcspn(termo, "\n")] = '\0';

    item *atual = fila->inicio;
    int encontrado = 0;
    while (atual != NULL) {
        if (strstr(atual->nome, termo) != NULL) {
            printf("Nome: %s | Qtd: %d | Prioridade: %d\n", atual->nome, atual->quantidade, atual->prioridade);
            encontrado = 1;
        }
        atual = atual->proximo;
    }
    if (!encontrado) {
        printf("Nenhum item encontrado com esse termo.\n");
    }
}