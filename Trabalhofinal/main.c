#include <stdio.h>
#include <time.h>
#include <string.h>
#include "conta.h"

int main(void)
{
    conta_init();
    long long valores = 0;
    int opcao = 0;
    int situacaotransacao = 0;

    while (opcao != 7)
    {
        if(situacaotransacao == 3)
        {
            printf("Capacidade máxima de transações atingidas. Obrigado por usar o Voidbank!\n");
            break;
        }
        printf("\n\nOperações Disponíveis:\n");
        printf("1. Depositar (conta corrente)\n");
        printf("2. Sacar (sem cheque especial)\n");
        printf("3. Aplicar na poupança\n");
        printf("4. Resgatar da poupança\n");
        printf("5. Consultar saldo\n");
        printf("6. Extrato\n");
        printf("7. Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);
        switch(opcao)
        {
            case DEP:

            printf("Digite o valor do depósito: ");
            scanf("%lld", &valores);
            situacaotransacao = depositar(valores);
            if(situacaotransacao == ERRO_VALOR_INVALIDO)
            {
                printf("Valor do depósito inválido.");
            }
            else if(situacaotransacao == ERRO_CAPACIDADE_LOG)
            {
                printf("Capacidade máxima de transações atingidas. Obrigado por usar o Voidbank!\n");
                break;  
            }
            else if(situacaotransacao == OK)
            {
                conta.log[conta.nlog].tipo = DEP;
                conta.log[conta.nlog].valor = valores;
                conta.log[conta.nlog].saldo_corrente_apos = conta.saldo_corrente;
                conta.log[conta.nlog].saldo_poupanca_apos = conta.saldo_poupanca;
                time_t agora = time(NULL);
                struct tm *tempo = localtime(&agora);
                strftime(conta.log[conta.nlog].quando, sizeof(conta.log[conta.nlog].quando), "%d/%m/%Y %H:%M%S", tempo);
                conta.nlog++;
                break;
            }

            case 7:

                printf("Obrigado por utilizar o voidbank!\n");
                break;

            default:

                printf("Opção inválida");
                break;

        }
    }

    return 0;
}
