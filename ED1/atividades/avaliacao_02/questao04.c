#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_RAND 10000
#define MAX 50

/* 
	O algoritmo consiste em ler o numero de linhas e colunas do usuario,
	alocar dinamicamente uma matriz com o tamanho especificado e em seguida
	e preenchida com valores aleatorio entre 0 e MAX_RAND 

	Apos preenchida e impressa, a funcao ocorrencias() itera por todos os valores
	e para cada valor, e chamada a funcao verificaQtdeIguais() que itera pela matriz
	novamente e conta os numeros iguis ao numero passado por parametro e retorna

	o retorno sera armazenado em um vetor que guardara as ocorrencias

	sera impresso a quantidade de ocorrencias e por fim a memoria é desalocada
*/

int **preencheMatriz(int l, int c);
int **alocaMatriz(int l, int c);
int *ocorrencias(int **mat, int l, int c);
void imprimeMatriz(int **m, int l, int c);
int sorteaNumero(int min, int max);
void desalocaMatriz(int **m, int c);

int verificaQtdeIguais(int **mat, int l, int c ,int valor);
int existeNoVetor(int* vet, int tam_vet, int valor);

int main() {
	int linhas, colunas, i;
	int **matriz = NULL;
	int *v = NULL;
	
	srand((unsigned) time(NULL));
	
	// leitura das linha e colunas da matriz
	printf("Digite o numero de linhas: ");
	scanf("%d", &linhas);
	
	printf("Digite o numero de colunas: ");
	scanf("%d", &colunas);
	
	// alocar a matriz dinamicamente
	alocaMatriz(linhas, colunas);
	
	// preencher a matriz com valores aleatorios
	matriz = preencheMatriz(linhas, colunas);
	
	// imprimir a matriz recem preenchida
	imprimeMatriz(matriz, linhas, colunas);
	
	// contar a quantidade de ocorrencias de cada valor e retornar
	// um vetor contendo todas as ocorrencias 
	v = ocorrencias(matriz, linhas, colunas);

	i = 0;
	// imprime todas as ocorrencias
	// a condicao de parada é -1 pois o vetor de ocorrencias
	// foi preenchido com -1 e nenhum valor valido será -1.
	while (v[i] != -1)
	{
		printf("Valor %d ocorrencias %d\n", v[i], v[i + 1]);
		i+=2;
	}

	// desalocar a memoria
	desalocaMatriz(matriz, linhas);
	
	return 0;
}

// funcao que aloca a matriz
int **alocaMatriz(int l, int c)
{
	int **ptrMatriz = NULL;
	int i, j;
	
	// alocando a matriz ponteiro para ponteiro dinamicamente  
	// de tamanho l (linhas da coluna) aponta para um ponteiro
	ptrMatriz = (int **) malloc(l * sizeof(int *)); 
	
	// verifica se o espaco de memoria foi realmente alocado
	if(ptrMatriz == NULL) {
		printf("ERRO: memoria insuficiente\n");
		exit(1);
	}
	
	// itera sobre cada posicao da matriz ponteiro para ponteiro alocada
	// e para cada uma dela aloca um vetor dinamico de tamanho c (coluna da matriz)
	for(i = 0; i < l; i++) {
		ptrMatriz[i] = (int *) malloc(c * sizeof(int)); 
		
		if(ptrMatriz[i] == NULL) {
			printf("ERRO: memoria insuficiente\n");
			// erro ao alocar, desalocar oq foi alocado até aqui;
			for (j = i - 1; j >= 0; j--)
			{
				free(ptrMatriz[j]);
				ptrMatriz[j] = NULL;
			}
			free(ptrMatriz);
			
			// finalizar o programa
			exit(1);
		}
	}
	return ptrMatriz;
}

// itera pela matriz alocada e preenche seu espacos com valores sorteados
int **preencheMatriz(int l, int c)
{
	int **Pmatriz = NULL;
	int i, j;
	
	Pmatriz = alocaMatriz(l, c);
	
	// itera sobre as linhas e colunas da matriz
	// preenchendo os espacos com valores sorteados
	// no intervalo definido por MAX_RAND
	for(i = 0; i < l; i++) {
		for(j = 0; j < c; j++) {
			Pmatriz[i][j] = sorteaNumero(0, MAX_RAND);
		}
	}
	printf("\n");
	
	return Pmatriz; // retorna o endereco novamente, dessa vez preenchido, que sera recebido por um ponteiro para ponteiro no main;
}

int *ocorrencias(int **mat, int l, int c) {
	int *vet = NULL;
	int i, j, num, i_vet = 0;
	int tam_vet = l*c*2 + 2;

	// alocacao dinamica do vetor com seu tamanho maximo	
	vet = (int*) malloc((tam_vet) * sizeof(int));


	// inicializar o vetor com -1 para não ocorrer conflito com valores
	// na hora da comparacao 
	for (i = 0; i < tam_vet; i++)
	{
		vet[i] = -1;
	}
	
	// iterar sobre a primeira matriz
	for (i = 0; i < l; i++)
	{
		for (j = 0; j < c; j++)
		{
			// verificar se o numero já está no vetor
			// ou seja, se ele estiver no vetor, significa que eu já calculei 
			// as ocorrencias dele
			
			if (!existeNoVetor(vet, tam_vet, mat[i][j]))
			{
				/* não existe no vetor */
				// contar ocorrencias
				// adicionar no vetor
				num = verificaQtdeIguais(mat, l, c,mat[i][j]);
				// adicionar o numero no vetor
				vet[i_vet++] = mat[i][j];
				// adicionar ocorrencia no vetor
				vet[i_vet++] = num;
			}
		}
	}
	
	return vet;	
}

// itera pela matriz verificando a quantidade de repeticoes do valor
// enviado por parametro
int verificaQtdeIguais(int **mat, int l, int c ,int valor){
	int i, j, cont_ocorrencia = 0;

	for (i = 0; i < l; i++)
	{
		for (j = 0; j < c; j++)
		{
			// testar se o valor é igual ao valor passado
			if (mat[i][j] == valor)
			{
				cont_ocorrencia++; // incrementa o contador
			}
		}
	}

	return cont_ocorrencia; // retorna a quantidade de ocorrencias daquele numero
}

// itera sobre a matriz, imprimindo seus valores  
void imprimeMatriz(int **m, int l, int c) // matriz dinaminaca, quantidade de linha, quantidade de colunas
{
	int i, j;
	for(i = 0; i < l; i++) {
		for(j = 0; j < c; j++) {
			printf(" %2d ", m[i][j]);	
		}
		printf("\n\n");
	}
}

// sorteia um numero no intervalo min e max, enviados por parametro
int sorteaNumero(int min, int max){
  return rand() % max + min;
}

// desaloca cada posicao em que a matriz e aponta (cada vetor ponteiro) e depois desaloca
// a matriz (vetor de ponteiro para ponteiro)
void desalocaMatriz(int **m, int c)
{
	int i; 
	for(i = 0; i < c; i++) {
		free(m[i]);  // desalocando cada posicao da matriz (vetor ponteiro)
		m[i] = NULL; // setando a memoria para NULL
	}
	
	free(m); // desalocando a matriz (vetor ponteiro para ponteiro)
	m = NULL; // setando o espaco de memoria para NULL
}

// verifica se eu ja calculei as ocorrencias de um numero
int existeNoVetor(int* vet, int tam_vet, int valor){
	int i;
	for (i = 0; i < tam_vet; i+=2)
	{
		if (valor == vet[i])
		{
			// já existe esse valor no vetor
			// ocorrencia desse valor já foi calculada
			return 1;
		}
	}
	return 0;
}