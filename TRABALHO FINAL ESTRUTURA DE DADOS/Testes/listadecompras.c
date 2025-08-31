#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listadecompras {
    char nome[50];
    int quantidade;
    float preco;
    struct listadecompras *proximo;
} listadecompras;

listadecompras *alocarLista() {
    return (listadecompras *)malloc(sizeof(listadecompras));
}

void additem(listadecompras *cabeca) {
    listadecompras *aux, *novoItem;

    aux = cabeca;
    while (aux->proximo != NULL) {
        aux = aux->proximo;
    }

    novoItem = alocarLista();
    printf("Digite o nome do item: ");
    fgets(novoItem->nome, sizeof(novoItem->nome), stdin);
    novoItem->nome[strcspn(novoItem->nome, "\n")] = 0; 
    novoItem->proximo = NULL;

    aux->proximo = novoItem;
}

int main () {
    listadecompras cabeca;
    cabeca.proximo = NULL;

    additem(&cabeca);
    additem(&cabeca);
    printf("Item adicionado: %s\n", cabeca.proximo->nome);
    printf("Item adicionado: %s\n", cabeca.proximo->proximo->nome);

    return 0;
}
