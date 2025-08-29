
#include "lista.h"
#include <stdio.h>

int main () {
    filaprioridade fila;
    inicializarfila(&fila);

    int opcao;
    do {
        printf("\n   Menu:   \n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Mostrar lista de compras\n");
        printf("4. Marcar item como comprado\n");
        printf("5. Mostrar itens urgentes\n");
        printf("6. Buscar item\n");
        printf("7. Relatório de compras\n");
        printf("8. Editar item\n");
        printf("9. Exportar lista para CSV\n");
        printf("10. Importar lista de CSV\n");
        printf("11. Desfazer ultima ação\n");
        printf("12. Ordenar lista por nome\n");
        printf("13. Ordenar lista por categoria\n");
        printf("14. Ordenar lista por prioridade\n");
        printf("15. Sair\n");
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
                printf("vou dar o fora daqui taligado mermão\n");
                break;
            default:
                printf("Opção inválida Tente novamente.(bote um numero direito rapaz deixe de mulekagem)\n");
        }
    } while (opcao != 15);

    while (fila.inicio != NULL) {
        removeritem(&fila);
    }
    return 0;
} 
