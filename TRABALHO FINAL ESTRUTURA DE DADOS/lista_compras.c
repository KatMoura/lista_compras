#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item
{
    char nome[50];
    int quantidade;
    float preco;
    int prioridade; 
    char categoria[30];
    int comprado;
    struct item *proximo;
} item;

typedef struct acao{
    char tipo[20]; 
    item dados;    
    struct acao *proximo;
} acao;

typedef struct filaprioridade
{
    item *inicio;
    item *fim;
} filaprioridade;

acao *topo = NULL;

void inicializarfila(filaprioridade *fila)
{
    fila->inicio = NULL;
    fila->fim = NULL;
}

void empilharAcao(const char *tipo, item dados)
{
    acao *nova = (acao *)malloc(sizeof(acao));
    if (!nova)
    {
        printf("Erro ao alocar memória para desfazer.\n");
        return;
    }
    strncpy(nova->tipo, tipo, sizeof(nova->tipo));
    nova->tipo[sizeof(nova->tipo) - 1] = '\0';
    nova->dados = dados; 
    nova->proximo = topo;
    topo = nova;
}

void additem(filaprioridade *fila){
    item *novo = (item *)malloc(sizeof(item));
    if (!novo){
        printf("Erro de alocaçao.\n");
        return;
    }

    printf("Digite o nome do item: ");
    fgets(novo->nome, sizeof(novo->nome), stdin);
    novo->nome[strcspn(novo->nome, "\n")] = '\0';

    printf("Digite a quantidade: ");
    if (scanf("%d", &novo->quantidade) != 1){
        getchar();
        free(novo);
        printf("Entrada inválida.\n");
        return;
    }

    printf("Preco: R$");
    if (scanf("%f", &novo->preco) != 1){
        getchar();
        free(novo);
        printf("Entrada invalida.\n");
        return;
    }

    printf("Prioridade (1-5): ");
    if (scanf("%d", &novo->prioridade) != 1){
        getchar();
        free(novo);
        printf("Entrada invalida.\n");
        return;
    }
    getchar(); 
    printf("Categoria: ");
    fgets(novo->categoria, sizeof(novo->categoria), stdin);
    novo->categoria[strcspn(novo->categoria, "\n")] = '\0';

    novo->comprado = 0;
    novo->proximo = NULL;

    if (fila->inicio == NULL){
        fila->inicio = fila->fim = novo;
    }
    else{
        item *atual = fila->inicio, *anterior = NULL;
        while (atual && atual->prioridade <= novo->prioridade){
            anterior = atual;
            atual = atual->proximo;
        }
        if (!anterior){
            novo->proximo = fila->inicio;
            fila->inicio = novo;
        } else {
            anterior->proximo = novo;
            novo->proximo = atual;
            if (!atual)
                fila->fim = novo;
        }
    }
    empilharAcao("add", *novo);
    printf("Item adicionado com sucesso!\n");
}

void removeritem(filaprioridade *fila){
    if (!fila->inicio){
        printf("Lista vazia.\n");
        return;
    }

    empilharAcao("remove", *(fila->inicio));

    item *removido = fila->inicio;
    fila->inicio = removido->proximo;
    if (!fila->inicio){
        fila->fim = NULL;
    }
    printf("Item removido: %s\n", removido->nome);
    free(removido);
}

void editarItem(filaprioridade *fila){
    char nomeBusca[50];
    printf("Digite o nome do item a editar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    item *atual = fila->inicio, *anterior = NULL;
    while (atual){
        if (strcmp(atual->nome, nomeBusca) == 0)
        {
            if (anterior)
                anterior->proximo = atual->proximo;
            else
                fila->inicio = atual->proximo;
            if (!fila->inicio)
                fila->fim = NULL;

            printf("Novo nome: ");
            fgets(atual->nome, sizeof(atual->nome), stdin);
            atual->nome[strcspn(atual->nome, "\n")] = '\0';
            printf("Nova quantidade: ");
            scanf("%d", &atual->quantidade);
            printf("Novo preco: R$");
            scanf("%f", &atual->preco);
            printf("Nova prioridade (1-5): ");
            scanf("%d", &atual->prioridade);
            getchar();
            printf("Nova categoria: ");
            fgets(atual->categoria, sizeof(atual->categoria), stdin);
            atual->categoria[strcspn(atual->categoria, "\n")] = '\0';

            // Reinsere ordenado por prioridade
            atual->proximo = NULL;
            if (fila->inicio == NULL){
                fila->inicio = fila->fim = atual;
            } else {
                item *p = fila->inicio, *ant = NULL;
                while (p && p->prioridade <= atual->prioridade){
                    ant = p;
                    p = p->proximo;
                }

                if (!ant){
                    atual->proximo = fila->inicio;
                    fila->inicio = atual;
                } else {
                    ant->proximo = atual;
                    atual->proximo = p;
                    if (!p)
                        fila->fim = atual;
                }
            }
            printf("Item editado e reposicionado pela prioridade.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item nao encontrado.\n");
}

void mostrarlista(filaprioridade *fila){
    item *atual = fila->inicio;
    if (!atual){
        printf("Lista vazia.\n");
        return;
    }
    printf("\n=== Lista de Compras (por prioridade) ===\n");
    while (atual){
        printf("Nome: %s | Qtd: %d | Preço: R$%.2f | Prioridade: %d | Categoria: %s | Comprado: %s\n",
               atual->nome, atual->quantidade, atual->preco, atual->prioridade,
               atual->categoria, atual->comprado ? "Sim" : "Não");
        atual = atual->proximo;
    }
}

void marcarComoComprado(filaprioridade *fila){
    char nomeBusca[50];
    printf("Digite o nome do item: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    item *atual = fila->inicio;
    while (atual){
        if (strcmp(atual->nome, nomeBusca) == 0){
            empilharAcao("comprado", *atual);
            atual->comprado = 1;
            printf("Item marcado como comprado!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Item nao encontrado.\n");
}

void mostrarUrgentes(filaprioridade *fila){
    item *atual = fila->inicio;
    printf("\nItens urgentes (prioridade <= 2 e não comprados):\n");
    while (atual){
        if (atual->prioridade <= 2 && !atual->comprado)
            printf("%s (Qtd %d, Prioridade %d)\n", atual->nome, atual->quantidade, atual->prioridade);
        atual = atual->proximo;
    }
}

void buscarItem(filaprioridade *fila){
    char termo[50];
    printf("Digite o termo de busca: ");
    fgets(termo, sizeof(termo), stdin);
    termo[strcspn(termo, "\n")] = '\0';

    item *atual = fila->inicio;
    int achou = 0;
    while (atual){
        if (strstr(atual->nome, termo)){
            printf("%s (Qtd %d, Prioridade %d, Categoria %s)\n", atual->nome, atual->quantidade, atual->prioridade, atual->categoria);
            achou = 1;
        }
        atual = atual->proximo;
    }

    if (!achou)
        printf("Nenhum item encontrado.\n");
}

void relatorioCompras(filaprioridade *fila){
    typedef struct{
        char nome[30];
        int total;
        int comprados;
    } CatStats;
    CatStats stats[50];
    int ncat = 0;

    int totalItens = 0, totalComprados = 0;

    for (item *p = fila->inicio; p != NULL; p = p->proximo){
        totalItens++;
        if (p->comprado)
            totalComprados++;

            int idx = -1;
        for (int i = 0; i < ncat; i++){
            if (strcmp(stats[i].nome, p->categoria) == 0){
                idx = i;
                break;
            }
        }
        if (idx == -1 && ncat < 50){
            strncpy(stats[ncat].nome, p->categoria, sizeof(stats[ncat].nome));
            stats[ncat].nome[sizeof(stats[ncat].nome) - 1] = '\0';
            stats[ncat].total = 0;
            stats[ncat].comprados = 0;
            idx = ncat++;
        }

        if (idx != -1){
            stats[idx].total++;
            if (p->comprado)
                stats[idx].comprados++;
        }
    }

    if (totalItens == 0){
        printf("Nenhum item na lista.\n");
        return;
    }

    printf("\n=== RELATÓRIO RÁPIDO ===\n");
    printf("Total de itens: %d\n", totalItens);
    printf("Itens comprados: %d (%.2f%%)\n", totalComprados, (totalComprados * 100.0f) / totalItens);

    printf("\n--- Por categoria ---\n");
    for (int i = 0; i < ncat; i++){
        float perc = stats[i].total ? (stats[i].comprados * 100.0f) / stats[i].total : 0.0f;
        printf("%s: %d/%d (%.2f%%) comprados\n", stats[i].nome, stats[i].comprados, stats[i].total, perc);
    }
}

void exportarCSV(filaprioridade *fila){
    FILE *arq = fopen("lista.csv", "w");
    if (!arq){
        printf("Erro ao abrir arquivo para escrita.\n");
        return;
    }

    for (item *p = fila->inicio; p != NULL; p = p->proximo){
        fprintf(arq, "%s,%d,%.2f,%d,%s,%d\n",
                p->nome, p->quantidade, p->preco, p->prioridade, p->categoria, p->comprado);
    }

    fclose(arq);
    printf("Lista exportada para 'lista.csv'.\n");
}

void importarCSV(filaprioridade *fila){
    FILE *arq = fopen("lista.csv", "r");
    if (!arq){
        printf("Arquivo 'lista.csv' não encontrado.\n");
        return;
    }

    char linha[256];
    int l = 0, inseridos = 0;
    while (fgets(linha, sizeof(linha), arq)){
        l++;
        item *novo = (item *)malloc(sizeof(item));
        if (!novo)
        {
            printf("Erro de alocação na linha %d.\n", l);
            continue;
        }
        novo->proximo = NULL;
        if (sscanf(linha, "%49[^,],%d,%f,%d,%29[^,],%d",
                   novo->nome, &novo->quantidade, &novo->preco, &novo->prioridade,
                   novo->categoria, &novo->comprado) != 6)
        {
            printf("Linha %d invalida, ignorada.\n", l);
            free(novo);
            continue;
        }

        if (fila->inicio == NULL){
            fila->inicio = fila->fim = novo;
        } else {
            item *atual = fila->inicio, *anterior = NULL;
            while (atual && atual->prioridade <= novo->prioridade) {
                anterior = atual;
                atual = atual->proximo;
            }
            if (!anterior){
                novo->proximo = fila->inicio;
                fila->inicio = novo;
            }
            else {
                anterior->proximo = novo;
                novo->proximo = atual;
                if (!atual)
                    fila->fim = novo;
            }
        }
        inseridos++;
    }
    fclose(arq);
    printf("Importaçao concluída: %d itens inseridos.\n", inseridos);
}

void desfazer(filaprioridade *fila){
    if (!topo){
        printf("Nada para desfazer.\n");
        return;
    }
    acao *ultima = topo;
    topo = topo->proximo;

    if (strcmp(ultima->tipo, "add") == 0){
        item *atual = fila->inicio, *ant = NULL;
        while (atual && strcmp(atual->nome, ultima->dados.nome) != 0){
            ant = atual;
            atual = atual->proximo;
        }
        if (atual){
            if (!ant)
                fila->inicio = atual->proximo;
            else
                ant->proximo = atual->proximo;
            if (!fila->inicio)
                fila->fim = NULL;
            free(atual);
            printf("Desfeita adiçao de %s\n", ultima->dados.nome);
        }
    }
    else if (strcmp(ultima->tipo, "remove") == 0){
        item *rest = (item *)malloc(sizeof(item));
        if (!rest){
            free(ultima);
            return;
        }
        *rest = ultima->dados;
        rest->proximo = fila->inicio;
        fila->inicio = rest;
        if (!fila->fim)
            fila->fim = rest;
        printf("Desfeita remoçao de %s\n", rest->nome);
    }
    else if (strcmp(ultima->tipo, "comprado") == 0){
        item *p = fila->inicio;
        while (p && strcmp(p->nome, ultima->dados.nome) != 0)
            p = p->proximo;
        if (p){
            p->comprado = 0;
            printf("Desfeita marcaçao de %s como comprado\n", p->nome);
        }
    }

    free(ultima);
}

void ordenarPorNome(filaprioridade *fila){
    if (!fila->inicio)
        return;
    int trocou;
    do{
        trocou = 0;
        item **p = &fila->inicio;
        while ((*p) && (*p)->proximo){
            if (strcmp((*p)->nome, (*p)->proximo->nome) > 0){
                item *a = *p, *b = a->proximo;
                a->proximo = b->proximo;
                b->proximo = a;
                *p = b;
                trocou = 1;
            }
            p = &((*p)->proximo);
        }
    } while (trocou);

    item *t = fila->inicio;
    while (t && t->proximo)
        t = t->proximo;
    fila->fim = t;
    printf("Ordenado por nome.\n");
}

void ordenarPorCategoria(filaprioridade *fila){
    if (!fila->inicio)
        return;
    int trocou;
    do{
        trocou = 0;
        item **p = &fila->inicio;
        while ((*p) && (*p)->proximo){
            if (strcmp((*p)->categoria, (*p)->proximo->categoria) > 0){
                item *a = *p, *b = a->proximo;
                a->proximo = b->proximo;
                b->proximo = a;
                *p = b;
                trocou = 1;
            }
            p = &((*p)->proximo);
        }
    } while (trocou);
    item *t = fila->inicio;
    while (t && t->proximo)
        t = t->proximo;
    fila->fim = t;
    printf("Ordenado por categoria.\n");
}

void ordenarPorPrioridade(filaprioridade *fila){
    if (!fila->inicio)
        return;
    int trocou;
    do{
        trocou = 0;
        item **p = &fila->inicio;
        while ((*p) && (*p)->proximo){
            if ((*p)->prioridade > (*p)->proximo->prioridade){
                item *a = *p, *b = a->proximo;
                a->proximo = b->proximo;
                b->proximo = a;
                *p = b;
                trocou = 1;
            }
            p = &((*p)->proximo);
        }
    } while (trocou);
    item *t = fila->inicio;
    while (t && t->proximo)
        t = t->proximo;
    fila->fim = t;
    printf("Ordenado por prioridade.\n");
}

void liberarLista(filaprioridade *fila){
    item *p = fila->inicio;
    while (p){
        item *prox = p->proximo;
        free(p);
        p = prox;
    }
    fila->inicio = fila->fim = NULL;
    while (topo){
        acao *q = topo->proximo;
        free(topo);
        topo = q;
    }
}

int main(){
    filaprioridade fila;
    inicializarfila(&fila);
    int op;
    do{
        printf("\nMenu:\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Mostrar lista\n");
        printf("4. Marcar como comprado\n");
        printf("5. Mostrar urgentes\n");
        printf("6. Buscar item\n");
        printf("7. Relatorio rapido (categorias)\n");
        printf("8. Editar item\n");
        printf("9. Exportar CSV\n");
        printf("10. Importar CSV\n");
        printf("11. Desfazer ultima açao\n");
        printf("12. Ordenar por nome\n");
        printf("13. Ordenar por categoria\n");
        printf("14. Ordenar por prioridade\n");
        printf("15. Sair\n");
        printf("Opçao: ");
        if (scanf("%d", &op) != 1){
            getchar();
            printf("Opção inválida.\n");
            continue;
        }
        getchar(); 
        switch (op){
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
            marcarComoComprado(&fila);
            break;
        case 5:
            mostrarUrgentes(&fila);
            break;
        case 6:
            buscarItem(&fila);
            break;
        case 7:
            relatorioCompras(&fila);
            break;
        case 8:
            editarItem(&fila);
            break;
        case 9:
            exportarCSV(&fila);
            break;
        case 10:
            importarCSV(&fila);
            break;
        case 11:
            desfazer(&fila);
            break;
        case 12:
            ordenarPorNome(&fila);
            break;
        case 13:
            ordenarPorCategoria(&fila);
            break;
        case 14:
            ordenarPorPrioridade(&fila);
            break;
        case 15:
            printf("Encerrando...\n");
            break;
        default:
            printf("Opção inválida.\n");
        }
    } while (op != 15);

    liberarLista(&fila);
    return 0;
}