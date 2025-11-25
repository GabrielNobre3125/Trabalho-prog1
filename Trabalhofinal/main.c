#include <stdio.h>
#include <time.h>
#include <string.h>
#include "conta.h"

int main(void)
{
    conta_init();
    long long valores = 0;
    int opcao = 0;
    int retorno_funcoes = 0;

    while (opcao != 7)
    {

        if(retorno_funcoes == ERRO_CAPACIDADE_LOG)
        {
            printf("\n\nCapacidade máxima de transações atingidas. Obrigado por usar o Voidbank!\n\n");
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
            retorno_funcoes = depositar(valores);
            if(retorno_funcoes == ERRO_VALOR_INVALIDO)
            {
                printf("\n\nValor do deposito inválido.\n\n");
            }
            else if(retorno_funcoes == OK)
            {
                printf("\n\nDeposito efetuado!\n\n");
                retorno_funcoes = registrar_transacao(DEP, valores);
            }
            break;

            case SAQ:
            
            printf("Digite o valor do saque: ");
            scanf("%lld", &valores);
            retorno_funcoes = sacar(valores);
            if(retorno_funcoes == ERRO_VALOR_INVALIDO)
            {
                printf("\n\nValor do saque inválido.\n\n");
            }
            else if(retorno_funcoes == ERRO_SALDO_INSUFICIENTE)
            {
                printf("\n\nSaldo insuficiente.\n\n");
            }
            else if(retorno_funcoes == OK)
            {
                 printf("\n\nSaque efetuado!\n\n");
                retorno_funcoes = registrar_transacao(SAQ, valores);
            }
            break;

            case 7:

                printf("\n\nObrigado por utilizar o voidbank!\n\n");
                break;

            default:

                printf("\n\nOpção inválida\n\n");
                break;

        }
    }

    return 0;
}
