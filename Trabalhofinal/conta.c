#include "conta.h"

Conta conta;

void conta_init(void)
{
    conta.saldo_corrente = 0;
    conta.saldo_poupanca = 0;
    conta.nlog = 0;
}

int depositar(long long valor) 
{
    if (valor <= 0) 
    {
        return ERRO_VALOR_INVALIDO;
    }

    if (conta.nlog >= MAX_TRANS) {
        return ERRO_CAPACIDADE_LOG;
    };
    conta.saldo_corrente += valor;
    return OK;
}