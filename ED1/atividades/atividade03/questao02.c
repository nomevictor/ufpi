#include<stdio.h>
#include<stdlib.h>
#define MAX 50

/* 
	A logica de solução consiste em encontrar o meio
	do vetor e imprimilo.

	A partir desse ponto, é criado dois novos iteradores chamados
	de l (left) e r (right) que serão decrementado e incrementado, respectivamente.

	A condicao de parada será quando os iteradores chegarem 
	nas extremidades do vetor (l no inicio e r no final). Como 
	farao isso simultaneamente, bas utilizar um dos dois

	E para cada iteracao, é impresso os valores nas posicoes l e r do vetor.
*/

void inicializa (int n, int** v); // inicializa o vetor com valores NULL
void preenche(int n, int** v, int i); // faz a leitura dos valores
void imprime_do_meio_para_fora(int n, int** v); // faz o processo
// de dividir o vetor ao meio e imprimir do meio para as extremidades
void desaloca_memoria(int n, int** v, int i); // desaloca a memoria alocada anteriormente

int main() {
	int i, tam;
	int *v[MAX];
	
	do 
	{
		printf("Digite o tamanho do vetor: \n");
		scanf("%d", &tam); // leitura do tamanho do vetor
		// condicao para garantir que o tamanho do vetor seja o valor impar
		if (tam % 2 != 0) {
			inicializa(tam, v); // atribuindo NULL a todas as posicoes que serao usadas
		} else{
			printf("\nO tamanho do vetor deve ser impar\nRepita a operacao!\n\n");
		}
		// isso se repete enquanto o usuario digitar valores errados (vetor de tamanho par)
  } while (tam % 2 == 0);
	
	// leitura dos dados
	while (i < tam) {
		preenche(tam, v, i);
		i++;
	}
	
	// impressao do meio para as extremidades
	imprime_do_meio_para_fora(tam, v);
	
	// desalocando o vetor
	while (i < tam) {
		desaloca_memoria(tam, v, i);
		i++;
	}
	
	return 0;
}

// itera sobre v até a posicao n e atribui NUL a todas essa posicoes
void inicializa (int n, int** v){
    int i;
    for (i = 0; i < n; i++)                 
    	v[i] = NULL;
}


void preenche(int n, int** v, int i) {
 
	// verifica se o indice esta dentro do tamanho do vetor
	if(i < 0 || i >= n){
		printf("Indice fora do limite do vetor\n");
		exit(1);
	}
 
	// verifica se o valor da posicao é NULL
	if(v[i] == NULL) {
		// caso sim, faz o alocamento de uma posicao
		v[i] = (int*) malloc(sizeof(int));
		
		printf("Digite o %d valor: ", i+1);
		scanf("%d", v[i]); // ler o valor
	}
    	    
}

void imprime_do_meio_para_fora(int n, int** v) {
	int meio = n / 2; // encontra o meio do vetor
	// iteradores l e r que partem da posicoes ao lado do meio
	int l = meio - 1, r = meio + 1; 
	
	printf("\n");
	printf(" %d\n", *v[meio]); // imprime o meio 
	
	// verifica se ja foi impresso todas as posicoes da esquerda do vetor
	while (l >= 0){
		// imprime os valores a esquerda e direita do meio, respectivamente
		printf("%d %d\n", *v[l], *v[r]);
		// decrementa e incrementa l e r, respectivamente
		l--;
		r++;
	}
  printf("\n");
}

// desaloca o vetor
void desaloca_memoria(int n, int** v, int i) {
	
	// verifica se o i passado esta dentro do tamanho do vetor
	if(i < 0 || i >= n){
		printf("Indice fora do limite do vetor\n");
		exit(1);  
    }
    
		// verifica se a posicao possue algum valor
    if(v[i]!= NULL) {
			// caso sim, desaloca
    	free(v[i]);
    	v[i] = NULL;
	}   
}