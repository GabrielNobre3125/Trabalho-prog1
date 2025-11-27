#include <stdio.h>
#include <time.h>
#include "conta.h"
#include <string.h>
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

int registrar_transacao(TipoTransacao tipo, long long valor)
{
    if(conta.nlog >= MAX_TRANS)
    {
        return ERRO_CAPACIDADE_LOG;
    }
    conta.log[conta.nlog].tipo = tipo;
    conta.log[conta.nlog].valor = valor;
    conta.log[conta.nlog].saldo_corrente_apos = conta.saldo_corrente;
    conta.log[conta.nlog].saldo_poupanca_apos = conta.saldo_poupanca;
    time_t agora = time(NULL);
    struct tm *tempo = localtime(&agora);
    strftime(conta.log[conta.nlog].quando, sizeof(conta.log[conta.nlog].quando), "%d/%m/%Y %H:%M:%S", tempo);
    conta.nlog++;
    return OK;
}

int aplicar_poupanca(long long valor){

    if (valor <= 0) {
        return ERRO_VALOR_INVALIDO;
    }

    if (valor > conta.saldo_corrente) {
        return ERRO_SALDO_INSUFICIENTE;
    }

    if (conta.nlog >= MAX_TRANS) {
        return ERRO_CAPACIDADE_LOG;
    }

    conta.saldo_corrente -= valor;
    conta.saldo_poupanca += valor;

    return OK;

}

int resgatar_poupanca(long long valor){

    if (valor <= 0) {
        return ERRO_VALOR_INVALIDO;
    }

    if (valor > conta.saldo_poupanca) {
        return ERRO_SALDO_INSUFICIENTE;
    }

    if (conta.nlog >= MAX_TRANS) {
        return ERRO_CAPACIDADE_LOG;
    }

    conta.saldo_corrente += valor;
    conta.saldo_poupanca -= valor;

    return OK;

}

void extrato_imprimir(void) {
    printf("\nEXTRATO VOIDBANK\n");

    for (int i = 0; i < conta.nlog; i++) {

        char tipo_str[20];
        switch (conta.log[i].tipo) {
            case DEP: 
                strcpy(tipo_str, "DEPÓSITO");
                break;
            case SAQ: 
                strcpy(tipo_str, "SAQUE");
                break;
            case APLI: 
                strcpy(tipo_str, "APLICAÇÃO");
                break;
            case RESG: 
                strcpy(tipo_str, "RESGATE");
                break;
            default: 
                strcpy(tipo_str, "NÃO REGISTRADO");
                break;
        }

        float valor_reais = conta.log[i].valor / 100.0f;

        printf("Data: %s | %s | R$ %.2f\n", conta.log[i].quando, tipo_str, valor_reais);
    }

    float saldo_corrente_final = conta.saldo_corrente / 100.0f;
    float saldo_poupanca_final = conta.saldo_poupanca / 100.0f;
    float saldo_total = saldo_corrente_final + saldo_poupanca_final;

    printf("\nSALDO FINAL\n");
    printf("Conta Corrente: R$ %.2f\n", saldo_corrente_final);
    printf("Poupança: R$ %.2f\n", saldo_poupanca_final);
    printf("TOTAL: R$ %.2f\n", saldo_total);
}
