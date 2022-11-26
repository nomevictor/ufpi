// gcc main.c jogador.c -o main

/* 
	O algoritmo consiste em pedir ao usuario para informar
	a quantidade de jogadores e em seguida, e lido todos
	os dados de todos os jogadores inseridos

	A funcao imprime_jogador() itera sobre a vetor struct jogador e 
	imprime todos os jogadores adicionados
	
	Soma
	Para a soma, é lido o nome de dois jogadores e enviado
	para soma_estatistica que verifica se os jogadores
	foram realmente adicionados 

	caso não: é impresso a informacao de erro para o usuario
	caso sim: é impresso a soma das estatisticas dos jogadores

	ehBom
	Para definir se o jogador é bom, é lido o nome do jogador
	e é verificado se ele foi adicionado
	caso nao: imprime mensagem de erro
	caso sim: é feita a media de gols por partida 
	(condicao para determinar se ele é bom)

	se ele obtiver media maior ou igual a 1 de gols por
	partida, ele é bom

	por fim, é liberado a memoria
*/

#include<stdio.h>
#include<stdlib.h>
#include "jogador.h"
#define MAX_caracter 50
#define MAX 25

int main() {
	int qtd_jogadores = 0, i = 0;
	char nome[MAX_caracter];
	int jogos = 0, gols = 0, assistencia = 0;
	char nome1[MAX_caracter], nome2[MAX_caracter];
	char nomejg[MAX_caracter];
	
	Jogador* jogador[MAX]; // cria o vetor para armazenar os jogadores
	
	printf("Quantidade de jogadores: ");
	scanf("%d", &qtd_jogadores);
	
	// leitura dos dados dos jogadores
	while(i < qtd_jogadores) {
		printf("Nome: ");
		setbuf(stdin, NULL);
		scanf("%[^\n]s", nome);
		printf("Quantidade de jogos: ");
		scanf("%d", &jogos);
		printf("Quantidade de gols: ");
		scanf("%d", &gols);
		printf("Numero de assistencias: ");
		scanf("%d", &assistencia);
		printf("\n");
		jogador[i] = atribui(nome, jogos, gols, assistencia);
		
		i++;
	}
	
	// imprime os jogadores
	imprime_jogador(qtd_jogadores,jogador);
	
	printf("\nDigite o nome dos jogadores para somar estatisticas deles: \n");
	printf("Nome do primeiro jogador: ");
	setbuf(stdin, NULL);
	scanf("%[^\n]s", nome1);
	setbuf(stdin, NULL);
	printf("Nome do segundo jogador: ");
	scanf("%[^\n]s", nome2);
	 
	// soma as estatisticas dos dois jogadores
	soma_estatistica(jogador, nome1, nome2, qtd_jogadores);
	
	printf("\nDigite o nome de um jogador para saber se ele eh bom: ");
	setbuf(stdin, NULL);
	scanf("%[^\n]s", nomejg);
	
	// Verifica se o jogador é bom
	ehbom(jogador, nomejg, qtd_jogadores);
	
	// libera a memoria aloca
	libera_memoria(qtd_jogadores, jogador);	
	return 0;
}
