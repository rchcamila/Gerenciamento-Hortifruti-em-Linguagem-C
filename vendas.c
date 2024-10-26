#include <stdio.h>
#include "vendas.h"

int opcaovenda;

void rotinaVendas(int id){
    int idUser = -1;
    idUser = id;
    while (1) {
        printf("Escolha uma opção:\n");
        printf("1- Registrar pedido de venda\n");
        printf("2- Cancelar pedido de venda\n");
        printf("3- Retornar ao menu anterior\n");
        scanf("%d", &opcaovenda);

        if (opcaovenda == 1) {
            printf("Registrar pedido de venda (em desenvolvimento)...\n");
            // Implementar lógica para registrar pedido de venda
        } else if (opcaovenda == 2) {
            printf("Qual pedido deseja cancelar? (em desenvolvimento)...\n");
            // Implementar lógica para cancelar pedido de venda
        } else if (opcaovenda == 3) {
            break; // Retorna ao menu anterior
        } else {
            printf("Opção não encontrada, digite novamente.\n");
        }
    }
}
