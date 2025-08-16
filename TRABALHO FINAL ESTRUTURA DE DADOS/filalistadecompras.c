#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct  filadecompras {
    int dado;
    struct filadecompras *proximo;


}filadecompras;

typedef struct fila {
    filadecompras *inicio;
    filadecompras *fim;
}fila;


void inicializarFila(fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

void enfileirar(int dado, fila *f) {
    filadecompras *ptr = (filadecompras *)malloc(sizeof(filadecompras));
    if(ptr == NULL){
        printf("Erro ao alocar memoria\n");
        return;
    } else {
        ptr->dado = dado;
        ptr->proximo = NULL;
        if(f->inicio ==  NULL){
            f->inicio = ptr;
        
        
        } else {
            f->fim->proximo = ptr;
        }
   

        f->fim = ptr;
        return;
   
   
    }

}
int desenfileirar (fila *f) {
     filadecompras *ptr = f->inicio;
    int dado;
    if(ptr != NULL){
        f->inicio = ptr->proximo;
        ptr->proximo = NULL;
        dado = ptr->dado;
        free(ptr);
        if(f->inicio == NULL) {
            f->fim = NULL; 
        }
        return dado;
    } else {
        printf("Fila vazia\n");
        return -1;
    }



}

void exibirFila(fila *f) {
    filadecompras *ptr = f->inicio;
    if(ptr != NULL) {
        while(ptr != NULL) {
            printf("%d ", ptr->dado);
            ptr = ptr->proximo;
        }
        printf("\n");
    
    }else {
        printf("Lista vazia\n");
        return;
    }
}

int main(){
    fila *f1 = (fila *)malloc(sizeof(fila));
    if(f1 == NULL) {
        printf("Erro de aloxação\n");
        exit(-1);
        
    }else {
        
        inicializarFila(f1);
        enfileirar(5, f1);
        
        enfileirar(10, f1);
        enfileirar(20, f1);
        enfileirar(30, f1);

        exibirFila(f1);

        
        printf("\nApós desenfileirar: %d\n", desenfileirar(f1));
        exibirFila(f1);
        printf("\nApós desenfileirar: %d\n", desenfileirar(f1));
        exibirFila(f1);
        printf("\nApós desenfileirar: %d\n", desenfileirar(f1));
        exibirFila(f1);
        printf("\nApós desenfileirar: %d\n", desenfileirar(f1));
        exibirFila(f1); 
    }


}