#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "jogador.h"
#define MAX_caracter 50
#define MAX 25

struct jogador{
	char nome[MAX_caracter];
	int jogos;
	int gols;
	int assistencias;
};

typedef struct jogador Jogador;


Jogador* atribui(char nome[], int jogos, int gols, int assistencias) {
	// alocando espaco para guardar um jogador
	Jogador* jogador = (Jogador *) malloc(sizeof(Jogador));
	
	// verifica se foi realmente alocado
	if(jogador == NULL) {
		printf("Memoria insulficiente!\n");
		exit(1);
	}
	
	// atribui os parametros a struct que foi alocada
	strcpy(jogador->nome, nome);
	jogador->jogos = jogos;
	jogador->gols= gols;
	jogador->assistencias = assistencias;
	
	// retorna a struct
	return jogador;
}

// Imprime todas as informacoes de todos os jogadores dentro
// da struct
void imprime_jogador(int n, Jogador** jogador) {
 	int i;
 	
 	for(i = 0; i < n; i++) {
 		printf("\nNome: %s\n", jogador[i]->nome);
		printf("Jogos: %d\n", jogador[i]->jogos);
		printf("Gols: %d\n", jogador[i]->gols);
		printf("Assistencias: %d\n", jogador[i]->assistencias);
	}
 		
}

// Soma as estatisticas de dois jogadores presente na struct
// caso ambos existam
void soma_estatistica(Jogador** jogador, char nome1[], char nome2[], int n) {
	int i, j1gols = 0, j1assiste = 0;
	int j2gols = 0, j2assiste = 0;
	int flag1 = 0, flag2 = 0;
	
	// Busca o jogador 01 na struct
	// se existir, copia os dados para as variaveis
	// atualiza a flag para usar na comparacao da linha 80
	for(i = 0; i < n; i++) {
		if(strcmp(jogador[i]->nome, nome1) == 0) {
			j1gols = jogador[i]->gols;
			j1assiste = jogador[i]->assistencias;
			flag1 = 1;
		}
	}
	
	// Busca o jogador 02 na struct
	// se existir, copia os dados para as variaveis
	// atualiza a flag para usar na comparacao da linha 80
	for(i = 0; i < n; i++) {
		if(strcmp(jogador[i]->nome, nome2) == 0) {
			j2gols = jogador[i]->gols;
			j2assiste = jogador[i]->assistencias;
			flag2 = 1;
		}
	}
	
	// Verifica se os dois jogadores foram encontrado
	if(flag1 == 1 && flag2 == 1) {
		// foram encontrados, imprime a soma das estatisticas
		printf("\nTotal de gols dos jogadores %s e %s: %d gols\n",nome1, nome2, j1gols + j2gols);
		printf("Total de assistencias: %d assistencias\n", j1assiste + j2assiste);
	}
	else if(flag1 == 0 && flag2 == 1) {
		// jogador 01 nao foi adicionado, imprime erro
		printf("\nNao eh possivel ter as estatisticas\nJogador %s nao faz parte do time!\n", nome1);
	}
	else if(flag1 == 1 && flag2 == 0) {
		// jogador 02 nao foi adicionado, imprime erro
		printf("\nNao eh possivel ter as estatisticas\nJogador %s nao faz parte do time!\n", nome2);
	}
	else {
		// jogador 01 e jogador 02 nao foi adicionado, imprime erro
		printf("\nNao eh possivel ter as estatisticas\n%s e %s nao fazem parte desse time\n", nome1, nome2);
	}
}

// verifica se o jogador informado é bom
void ehbom(Jogador** jogador, char nomejg[], int n) {
	int i, flag=0;
	float bom = 0;
	
	// Verifica se o jogador informado foi adicionado
	for(i = 0; i < n; i++) {
		if(strcmp(jogador[i]->nome, nomejg) == 0) {
			// jogador encontrado, calcula a media de gols por jogo
			bom = jogador[i]->gols / jogador[i]->jogos;
			flag = 1; // flag para comparar
		} 
	}

	// flag = 0 -> jogador nao existe
	// flag = 1 -> jogador existe

	// verifica situacao da flag
	if (flag)
	{
		// Ele é bom se sua media de gols por jogos for maior que
		// 1.0
		if(bom >= 1.0) {
			// ele é bom
			printf("Jogador %s eh bom\nMedia de gols por partida: %.1f\n",nomejg, bom);
		}
		else{
			// ele nao é bom
			printf("Jogador %s precisa melhorar o rendimento\nMedia de gols por partida: %.1f\n", nomejg, bom);
		}
	} else {
		// jogador não existe
		printf("Jogador %s nao existe.\n", nomejg);
	}
}

// Desaloca a memoria e seta para NULL
void libera_memoria(int n, Jogador** jogador) {
	int i;
	
	for(i = 0; i < n; i++) {
		free(jogador[i]);
		jogador[i] = NULL;
	}
}
