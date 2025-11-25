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
            retorno_funcoes = depositar(valores);
            if(retorno_funcoes == ERRO_VALOR_INVALIDO)
            {
                printf("Valor do deposito inválido.");
            }
            else if(retorno_funcoes == OK)
            {
                retorno_funcoes = registrar_transacao(DEP, valores);
            }
            break;

            case SAQ:
            
            printf("Digite o valor do saque: ");
            scanf("%lld", &valores);
            retorno_funcoes = sacar(valores);
            if(retorno_funcoes == ERRO_VALOR_INVALIDO)
            {
                printf("Valor do saque inválido.\n");
            }
            else if(retorno_funcoes == ERRO_SALDO_INSUFICIENTE)
            {
                printf("Saldo insuficiente.\n");
            }
            else if(retorno_funcoes == OK)
            {
                retorno_funcoes = registrar_transacao(SAQ, valores);
            }
            break;

            case 7:

                printf("Obrigado por utilizar o voidbank!\n");
                break;

            default:

                printf("Opção inválida\n");
                break;

        }
    }

    return 0;
}
