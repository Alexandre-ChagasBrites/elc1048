#include <stdint.h>
#include <stdio.h>

#include "multitarefas.h"

/*
 * Prototipos das tarefas
 */
void tarefa_1(void);
void tarefa_2(void);
void tarefa_3(void);
void tarefa_4(void);
void tarefa_5(void);
void tarefa_6(void);

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_3		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_4		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_5		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_6		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_TAREFA_3[TAM_PILHA_3];
uint32_t PILHA_TAREFA_4[TAM_PILHA_4];
uint32_t PILHA_TAREFA_5[TAM_PILHA_5];
uint32_t PILHA_TAREFA_6[TAM_PILHA_6];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];

/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa(tarefa_1, "Tarefa 1", PILHA_TAREFA_1, TAM_PILHA_1, PRONTA, 1);
	CriaTarefa(tarefa_2, "Tarefa 2", PILHA_TAREFA_2, TAM_PILHA_2, ESPERA, 2);
	CriaTarefa(tarefa_3, "Tarefa 3", PILHA_TAREFA_3, TAM_PILHA_3, ESPERA, 3);
	CriaTarefa(tarefa_4, "Tarefa 4", PILHA_TAREFA_4, TAM_PILHA_4, ESPERA, 4);
	CriaTarefa(tarefa_5, "Tarefa 5", PILHA_TAREFA_5, TAM_PILHA_5, ESPERA, 5);
	CriaTarefa(tarefa_6, "Tarefa 6", PILHA_TAREFA_6, TAM_PILHA_6, PRONTA, 6);
	
	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, PRONTA, 0);
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
	{
	}
}

uint16_t i1 = 0;
uint16_t i2 = 0;
uint16_t i3 = 0;
uint16_t i4 = 0;
uint16_t i5 = 0;

void tarefa_1(void)
{
	for(;;)
	{
                i1 = i1 + 1;
                TarefaContinua(2);
	}
}

void tarefa_2(void)
{
	for(;;)
	{
                i2 = i2 + 1;
                TarefaContinua(3);
                TarefaSuspende(2);
	}
}

void tarefa_3(void)
{
	for(;;)
	{
                i3 = i3 + 1;
                TarefaContinua(4);
                TarefaSuspende(3);
	}
}

void tarefa_4(void)
{
	for(;;)
	{
                i4 = i4 + 1;
                TarefaContinua(5);
                TarefaSuspende(4);
	}
}

void tarefa_5(void)
{
	for(;;)
	{
                i5 = i5 + 1;
                TarefaSuspende(5);
	}
}

void tarefa_6(void)
{
	volatile uint32_t i = 0;
	for(;;)
	{
                TarefaEspera(30000);
                i = i1 + i2 + i3 + i4 + i5;
	}
}