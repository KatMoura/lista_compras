#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item {
    char nome[50];
    int quantidade;
    float preco;
    int prioridade;
    struct item *proximo;
} item;

typedef struct filaprioridade {
    item *inicio;
    item *fim;
} filaprioridade;


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
        printf("Item adicionado com sucesso!\n");
}
void  removeritem(filaprioridade *fila){
    if (fila->inicio == NULL) {
        printf("Fila de prioridade vazia\n");
        return;
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


int main () {
    filaprioridade fila;
    inicializarfila(&fila);

    int opcao;
    do {
        printf("\n   Menu:   \n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Mostrar lista de compras\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                additem(&fila);
                break;
            case 2:
                removeritem(&fila);
                break;
            case 3:
                mostrarlista(&fila);
                break;
            case 4:
                printf("vazando...\n");
                break;
            default:
                printf("Opção inválida Tente novamente.(bote um numero direito rapaz deixe de mulekagem)\n");
        }
    } while (opcao != 4);

    while (fila.inicio != NULL) {
        removeritem(&fila);
    }
    return 0;
} 
