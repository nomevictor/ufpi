#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
#define MAX_CHARACTERS 50

// struct responsavel por armazenar os dados dos jogadores
typedef struct 
{
	char nome[MAX_CHARACTERS];
	int idade;
	int num_camisa;
	char posicao[MAX_CHARACTERS];
	float altura;
}Jogador;


void inicializa(int n, Jogador** jogadores); // Funcao para atribuir NULL as posicoes do vetor de Struct Jogadores
void preenche(int n, Jogador** jogadores, int i); // aloca a memoria e preenche o vetor de struct com os dados do jogador
void desaloca_memoria(int n, Jogador** jogadores, int i); // Desaloca o vetor de struct Jogadores
void jogador_mais_alto(int n, Jogador** jogadores, float *mais_alto); // retorna o jogador mais alto por parametro
int idade_jogador_mais_baixo(int n, Jogador** jogadores); // retorna a idade do jogador mais baixo pela funcao

// retorna por parametro o nome de todos os jogadores com a altura igual a media 
// (ou o jogador com a altura mais proxima a media)
float media_altura(int n, Jogador** jogadores, char *jogador_altura_media[MAX_CHARACTERS], int* aux_nomes);  
void trunca_duas_casas(float *valor); // trunca um valor float em duas casas decimais

int main() {
	int i, qtd_jogadores, qtde_nomes = 0;
	int jg_m_baixo_idade = 0;
	char *nome_alt_media[MAX_CHARACTERS]; //seria onde receberia os jogadores com a altura media
	float mais_alto = 0, m_alturas = 0;

	Jogador *jogadores[MAX];
	
	// leitura da quantidade de jogadores
	printf("Quantidade de jogadores: \n");
	scanf("%d", &qtd_jogadores);
	
	// inicializando o vetor Jogadores com valores Nulos
	inicializa(qtd_jogadores, jogadores);


	// preeenche o vetor com as informacoes de todos os jogadores
	i = 0;
	while (i < qtd_jogadores) {
		preenche(qtd_jogadores, jogadores, i);
		i++;
	}
	
	// determinar o jogador mais alto 
	jogador_mais_alto(qtd_jogadores, jogadores, &mais_alto);
	printf("Jogador mais alto tem %.2f de altura\n", mais_alto);
	
	// Encontrar a idade do jogador mais baixo
	jg_m_baixo_idade = idade_jogador_mais_baixo(qtd_jogadores, jogadores);
	printf("Jogador mais baixo tem %d anos\n\n", jg_m_baixo_idade);
	
	// Determina a media da alturas e o nome dos jogadore com altura mediana
	m_alturas = media_altura(qtd_jogadores, jogadores, nome_alt_media, &qtde_nomes);
	printf("Media de todas as alturas eh %.2f\n\n", m_alturas);


	if (qtde_nomes == 0)
	{
		/* Apenas jogador proximo da media*/
		printf("Nome do jogador com altura mais proxima da media: \n");
		printf("%s\n", nome_alt_media[0]);
	}else
	{
		printf("Nome do(s) jogador(es) com altura igual a media: \n");
		// itera na matriz de caracteres nome_alt_media[i] e imprime o nome de 
		// todos os jogadores que tem a altura igual a media 
		for (i = 0; i < qtde_nomes; i++)
		{
			printf("%s" ,nome_alt_media[i]);
		}
	}
	
	// desaloca o vetor de struct jogadores
	while (i < qtd_jogadores) {
		desaloca_memoria(qtd_jogadores, jogadores, i);
		i++;
	}
	return 0;
}

// atribui nulo na struct jogadores baseando-se na quantidade de jogadores 
void inicializa(int n, Jogador** jogadores)
{
	int i;
	for (i = 0; i < n; i++){
		jogadores[i] = NULL;
	}                 
}

// Aloca dinamicamente em jogadore o espaco para armazenar um jogador e
// faz a leitura de seus dados
void preenche(int n, Jogador** jogadores, int i){
		// verifica que a posicao passa existe no vetor de  struct jogadores
    if(i < 0 || i >= n){
    	printf("Indice fora do limite do vetor\n");
    	exit(1);
    }

		// verifica se a posicao está livre	
    if(jogadores[i] == NULL) {
    	jogadores[i] = (Jogador*)malloc(sizeof(Jogador)); // alocacao dinamica
    	
			printf("Jogador %d\n", i + 1);
			printf("Nome: ");
			setbuf(stdin, NULL);
			fgets(jogadores[i]->nome, MAX_CHARACTERS, stdin);
			setbuf(stdin, NULL);
			printf("Idade: ");
			scanf("%d", &jogadores[i]->idade);;
			printf("Numero da camisa: ");
			scanf("%d", &jogadores[i]->num_camisa);
			setbuf(stdin, NULL);
			printf("Posicao: ");
			fgets(jogadores[i]->posicao, MAX_CHARACTERS, stdin);
			setbuf(stdin, NULL);
			printf("Altura: ");
			scanf("%f", &jogadores[i]->altura);
			// trunca a altura em duas casas decimais
			trunca_duas_casas(&jogadores[i]->altura);
			printf("\n");
	}
}

// itera sobre o vetor Jogadores e retorna o mais alto
void jogador_mais_alto(int n, Jogador** jogadores, float *mais_alto)
{
	int i;
	// atribui a primeira altura a altura mais alta
	*mais_alto = jogadores[0]->altura;
  
	// itera sobre todos os jogadores (exceto o primeiro)
	// e verifica se existe alguma altura maior que a primeira
	// (do jogador do indice 0)
	for(i = 1; i < n; i++) {
		// verifica se a proxima altura é maior que a anterior
		if(jogadores[i]->altura > *mais_alto){
			// É maior, atribui a variavel mais alto
			*mais_alto = jogadores[i]->altura;
    }
	}
}

int idade_jogador_mais_baixo(int n, Jogador** jogadores){

	int i;
	// atribui a idade, a idade do jogador da primeira posicao
	int idade = jogadores[0]->idade;
	// atribui a m_baixo, a altura do jogador da primeira posicao
	float m_baixo = jogadores[0]->altura;
  
	for(i = 1; i < n; i++) {
		// verifica se a altura do jogador da iteracao é maior que a de m_baixo
		if(jogadores[i]->altura < m_baixo){
			// É maior
			// m_baixo recebe a nova altura mais baixa
			m_baixo = jogadores[i]->altura;
			// idade recebe a idade do jogador mais baixo
			idade = jogadores[i]->idade;
    }
	}
	// é retornado a idade
	return idade;
}


float media_altura(int n, Jogador** jogadores, char *jogador_altura_media[MAX_CHARACTERS], int* aux_nomes) 
{
	int i;
	float media = 0, diferenca = 0;
	float aproxima = 0;
	
	// soma todas as alturas em media
	for(i = 0; i < n; i++){
		media += jogadores[i]->altura;
	}
	// calcula a media
	media = media / n;
	// Truncar media em duas casas decimais para poder fazer a comparação
	trunca_duas_casas(&media);

	/* ENCONTRAR JOGADORES COM ALTURA IGUAL A MEDIA 
	(caso encontre igual, não será executado o para encontrar altura proxima da media) */
	for (i = 0; i < n; i++)
	{
		// verifica se existe alguma altura igual a media
		if (media == jogadores[i]->altura)
		{
			// caso sim, a matriz de caracteres recebe o nome do jogador 
			jogador_altura_media[*aux_nomes] = jogadores[i]->nome;
			*aux_nomes = *aux_nomes + 1; // incremento do iterador da matriz de caracteres
		}
	}
	
	// significa que não encontrei altura igual a media 
	// procurar a mais proxima
	if (*aux_nomes == 0) 
	{
		/* ENCONTRAR O MAIS PROXIMO DA MEDIA */

		// verificacao para conseguir o valor absoluto da subtração da media pela
		// altura do jogador da posicao 0
		if (media > jogadores[0]->altura)
		{
			diferenca = media - jogadores[0]->altura;
		}else {
			diferenca = jogadores[0]->altura - media;
		}

		int indice, aux = 0;
		// varialvel que guardará o indice que se encontra o jogador com
		// a media mais proxima da media
		indice = 0;

		for(i = 1; i < n; i++) {
			// verificacao para conseguir o valor absoluto da subtração da media pela
			// altura do jogador da iteracao
			if (media > jogadores[i]->altura)
			{
				aproxima = media - jogadores[i]->altura;
			}else {
				aproxima = jogadores[i]->altura - media;
			}
			// verifica se a diferenca do ultimo jogador é menor que a do anterior
			if(aproxima < diferenca) {
				// caso sim, atualiza a menor diferenca
				diferenca = aproxima;
				// Indice recebe a posicao do novo jogador com a altura mais proxima da media
				indice = i;
			}
		} 
		// matriz de caracteres recebe o nome do jogador com altura mais proxima da media
		jogador_altura_media[*aux_nomes] = jogadores[indice]->nome;
	}
	return media;
}

void desaloca_memoria(int n, Jogador** jogadores, int i)
{
	// verifica se o indice enviado está é válido (é maior que 1 e menor que o tamanho da struct)
	if(i < 0 || i >= n){
		printf("Indice fora do limite do vetor\n");
		exit(1);  
  }

	// verifica se a memoria está ocupada (diferente de NULL)
	if(jogadores[i]!= NULL) {
		// caso sim, libera
		free(jogadores[i]);
		jogadores[i] = NULL;
	}
}

/* TRUNCAR EM DUAS CASAS */
/* 
	Seja 1.8894000000848 o valor a ser truncado em duas casas decimais 
	1 - multiplicar por 100, movendo a virgula duas casas para a direita (188.94000000848)
	2 - Tranformar o valor em inteiro para que as casas decimais se percam (188)
	3 - retornar o valor para float (188.000)
	4 - Dividir por 100 para retornar as duas caas decimais (1.88)
*/

// trunca em duas casas
void trunca_duas_casas(float *valor){
	*valor *= 100;
	*valor = (int) *valor;
	*valor = (float) *valor;
	*valor /= 100;
}
