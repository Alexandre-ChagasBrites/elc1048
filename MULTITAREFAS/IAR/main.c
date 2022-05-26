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

/*
 * Configuracao dos tamanhos das pilhas
 */
#define TAM_PILHA_1		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_2		(TAM_MINIMO_PILHA + 24)
#define TAM_PILHA_OCIOSA	(TAM_MINIMO_PILHA + 24)

/*
 * Declaracao das pilhas das tarefas
 */
uint32_t PILHA_TAREFA_1[TAM_PILHA_1];
uint32_t PILHA_TAREFA_2[TAM_PILHA_2];
uint32_t PILHA_TAREFA_OCIOSA[TAM_PILHA_OCIOSA];

/*
 * Funcao principal de entrada do sistema
 */
int main(void)
{
	
	/* Criacao das tarefas */
	/* Parametros: ponteiro, nome, ponteiro da pilha, tamanho da pilha, prioridade da tarefa */
	
	CriaTarefa(tarefa_1, "Tarefa 1", PILHA_TAREFA_1, TAM_PILHA_1, 1);
	
	CriaTarefa(tarefa_2, "Tarefa 2", PILHA_TAREFA_2, TAM_PILHA_2, 2);
	
	/* Cria tarefa ociosa do sistema */
	CriaTarefa(tarefa_ociosa,"Tarefa ociosa", PILHA_TAREFA_OCIOSA, TAM_PILHA_OCIOSA, 0);
	
	/* Configura marca de tempo */
	ConfiguraMarcaTempo();   
	
	/* Inicia sistema multitarefas */
	IniciaMultitarefas();
	
	/* Nunca chega aqui */
	while (1)
	{
	}
}

#define TAM_BUFFER 32
uint8_t buffer[TAM_BUFFER];

semaforo_t cheio = { .contador = 0, .tarefaEsperando = 0 };
semaforo_t vazio = { .contador = TAM_BUFFER, .tarefaEsperando = 0 };

typedef struct {
        uint8_t num;
} gen_t;

uint8_t gen_valor(gen_t* gen)
{
        uint8_t val = gen->num;
        gen->num = gen->num * 11 + 13;
        return val;
}

uint8_t produz()
{
        static gen_t gen = { .num = 0 };
        TarefaEspera(5);
        return gen_valor(&gen);
}

void consome(uint8_t valor)
{
        TarefaEspera(10);
}

/* Produtor */
void tarefa_1(void)
{
	volatile uint16_t f = 0;
	for(;;)
	{
		SemaforoAguarda(&vazio);
                buffer[f] = produz();
                f = (f + 1) % TAM_BUFFER;
                SemaforoLibera(&cheio);
	}
}

/* Consumidor */
void tarefa_2(void)
{
	volatile uint16_t i = 0;
	for(;;)
	{
                SemaforoAguarda(&cheio);
                consome(buffer[i]);
                i = (i + 1) % TAM_BUFFER;
                SemaforoLibera(&vazio);
	}
}