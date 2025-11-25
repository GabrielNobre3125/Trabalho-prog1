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

int sacar(long long valor) 
{
    if (valor <= 0) 
    {
        return ERRO_VALOR_INVALIDO;
    }

    if (valor > conta.saldo_corrente) 
    {
        return ERRO_SALDO_INSUFICIENTE;
    }

    if (conta.nlog >= MAX_TRANS) 
    {
        return ERRO_CAPACIDADE_LOG;
    }

    conta.saldo_corrente -= valor;
    return OK;
}

int registrar_transacao(TipoTransacao tipo, long long valores)
{
    if(conta.nlog >= MAX_TRANS)
    {
        return ERRO_CAPACIDADE_LOG;
    }
    conta.log[conta.nlog].tipo = tipo;
    conta.log[conta.nlog].valor = valores;
    conta.log[conta.nlog].saldo_corrente_apos = conta.saldo_corrente;
    conta.log[conta.nlog].saldo_poupanca_apos = conta.saldo_poupanca;
    time_t agora = time(NULL);
    struct tm *tempo = localtime(&agora);
    strftime(conta.log[conta.nlog].quando, sizeof(conta.log[conta.nlog].quando), "%d/%m/%Y %H:%M:%S", tempo);
    conta.nlog++;
    return OK;
}