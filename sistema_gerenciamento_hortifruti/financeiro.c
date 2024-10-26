#include <stdio.h>
#include "financeiro.h"

int financeiro;

void rotinaFinanceiro(int id){
    int idUser = -1;
    idUser = id;
    while (1) {
        printf("Escolha uma op��o:\n");
        printf("1- Emitir relat�rio financeiro\n");
        printf("2- Realizar pagamento\n");
        printf("3- Retornar ao menu anterior\n");
        scanf("%d", &financeiro);

        if (financeiro == 1) {
            printf("Digite o m�s e ano de refer�ncia (em desenvolvimento)...\n");
            // Implementar l�gica para emitir relat�rio financeiro
        } else if (financeiro == 2) {
            printf("1- Pagamento de funcion�rio\n");
            printf("2- Pagamento de fornecedor\n");
            printf("3- Despesas (Aluguel, luz, �gua, etc)\n");
            printf("4- Pagar clientes (Reembolso/Devolu��o)\n");
            printf("5- Retornar ao menu principal\n");
            scanf("%d", &financeiro);

            if (financeiro >= 1 && financeiro <= 4) {
                printf("Escolha a op��o %d (em desenvolvimento)...\n", financeiro);
                // Implementar l�gica para realizar pagamento
            } else if (financeiro == 5) {
                break; // Retorna ao menu anterior
            } else {
                printf("Op��o n�o encontrada, digite novamente.\n");
            }
        } else if (financeiro == 3) {
            break; // Retorna ao menu anterior
        } else {
            printf("Op��o n�o encontrada, digite novamente.\n");
        }
    }
}
