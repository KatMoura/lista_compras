#ifndef LISTA_H
#define LISTA_H
typedef struct item {
    char nome[50];
    int quantidade;
    float preco;
    int prioridade;
    char categoria[30];
    int comprado; 
    struct item *proximo;
} item;

typedef struct acao {
    char tipo[20]; 
    item dados;
    struct acao *proximo;
} acao;

extern acao *topo; 

typedef struct filaprioridade {
    item *inicio;
    item *fim;
} filaprioridade;
void inicializarfila(filaprioridade *fila);
void additem(filaprioridade *fila);
void removeritem(filaprioridade *fila);
void editarItem(filaprioridade *fila);
void mostrarlista(filaprioridade *fila);
void marcarComoComprado(filaprioridade *fila);
void mostrarUrgentes(filaprioridade *fila);
void buscarItem(filaprioridade *fila);
void relatorioCompras(filaprioridade *fila);
void exportarCSV(filaprioridade *fila);
void importarCSV(filaprioridade *fila);
void ordenarPorNome(filaprioridade *fila);
void ordenarPorCategoria(filaprioridade *fila);
void empilharAcao(const char *tipo, item dados);
void desfazer(filaprioridade *fila);
void ordenarPorPrioridade(filaprioridade *fila);
#endif