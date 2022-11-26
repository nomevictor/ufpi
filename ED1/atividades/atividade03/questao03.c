#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 40

/* 
	O algoritmo consiste em fazer a leitura 
	dos dados dos alunos e armazenar em um vetor de struct.

	Em seguida, a funcao imprime_aprovados calcula a media do aluno e caso 
	a media do aluno for maior que 7, será impresso as informações do aluno 
	pela funcao imprime

	em seguida, apos o usuario escolher qual turma deseja saber a media, a funcao
	media_turma calculará a media de todos os alunos pertecente a turma escolhida
	e retornará pela funcao a media das medias desses alunos
*/
 
struct aluno{
	char nome[81];
	char matricula[8];
	char turma[2];
	float p1;
	float p2;
	float p3;
};

typedef struct aluno Aluno;
 
void inicializa (int n, Aluno** turmas);
void preenche(int n, Aluno** turmas, int i);
void imprime(int n, Aluno** turmas, int i);
void imprime_aprovados(int n, Aluno** turmas);
float media_turma(int n, Aluno** turmas, char turma);
void desaloca_memoria(int n, Aluno** turmas, int i);

int main(){
	
	int i = 0, qtd_alunos = 0;
	Aluno *turmas[MAX]; 
	float media_turmas = 0;
	char opcao;
	
	printf("Digite a quantidade de alunos: ");
	scanf("%d", &qtd_alunos);
	
	inicializa(qtd_alunos, turmas); // inicializa o vetor NULL
	
	// itera sobre a quantidade de alunos e ler as informacoes dos aluno
	while (i < qtd_alunos){
		setbuf(stdin, NULL);
		preenche(qtd_alunos, turmas , i);
		i++;
	}

	// imprime a media dos alunos aprovados
	imprime_aprovados(qtd_alunos, turmas);
	
	// Pergunta ao usuario qual turma ele deseja saber a media
	printf("Escolha qual turma deseja saber a media final dos alunos: \n");
	printf("Turma - A \nTurma - B \nTurma - C\n");
	setbuf(stdin, NULL);
	scanf("%c", &opcao);
	opcao = toupper(opcao); // transforma o caracter digitado em maiusculo
	setbuf(stdin, NULL);

	// verifica se a letra digita é de uma turma existente
	if(opcao != 'A' && opcao != 'B' && opcao != 'C') {
		// diferente das turmas existentes
		// imprime mensagem de erro e pede para o usuario digitar novamente
		printf("Opcao invalida! digite novamente:\n");
		// do while repetirá até que o usuario digite uma turma válida
		do {
			scanf("%c", &opcao);
			opcao = toupper(opcao);
			setbuf(stdin, NULL);
		}while(opcao != 'A' && opcao != 'B' && opcao != 'C');    
	}
	
	// calcula a media da turma escolhida
	media_turmas = media_turma(qtd_alunos, turmas, opcao);
	
	if(media_turmas > 0) {
		// Não foi adicionado alunos na turma
	printf("Media final da turma %c = %.2f\n", opcao, media_turmas);
	}
	else {
		// foi adicionado alunos, imprime a media dos alunnos
		printf("Media da turma %c: sem media\nNenhum aluno cadastrado nessa turma\n", opcao);
	}
 
 // itera no vetor preenchido e desaloca cada posicao
 	while (i < qtd_alunos) {
 		desaloca_memoria(qtd_alunos, turmas, i);
 		i++;
	}
  return 0;
}

// inicializa as posicoes ques serao usadas com NULL
void inicializa (int n, Aluno** turmas){
    int i;
    for (i = 0; i < n; i++)                 
    	turmas[i] = NULL;
}

// ler as informacoes dos alunos e adiciona no vetor turmas
void preenche(int n, Aluno **turmas, int i){
	
	if(i < 0 || i >= n){
		printf("Indice fora do limite do vetor\n");
		exit(1);
	}
 
	if(turmas[i] == NULL) {
		turmas[i] = (Aluno*)malloc(sizeof(Aluno)); // aloca a memoria para adicionar 1 aluno
	
		setbuf(stdin, NULL);
		printf("Entre com o nome: ");
		scanf("%[^\n]s", turmas[i]->nome);
		setbuf(stdin, NULL);       
		printf("Entre com a matricula: ");
		scanf("%s", turmas[i]->matricula);
		setbuf(stdin, NULL); 
		printf("Entre com a turma (A, B, C): ");
		scanf("%s", turmas[i]->turma);
		*turmas[i]->turma = toupper(*turmas[i]->turma); // deixa a turma digitada em maiusculo
		// verifica se a turma digitada pelo usuario existe
		while(*turmas[i]->turma != 'A' && *turmas[i]->turma != 'B' && *turmas[i]->turma != 'C') {
			printf("Turma nao existe, digite novamente: ");
			scanf("%s", turmas[i]->turma);
			*turmas[i]->turma = toupper(*turmas[i]->turma);
		}

		setbuf(stdin, NULL);
		printf("Entre com a primeira nota: ");
		scanf("%f", &turmas[i]->p1);
		printf("Entre com a segunda nota: ");
		scanf("%f", &turmas[i]->p2);
		printf("Entre com a terceira nota: ");
		scanf("%f", &turmas[i]->p3);
		printf("\n");
	}
        
}


void imprime(int n, Aluno** turmas, int i){
 
	// verifica se o indice esta dentro do tamanho do vetor
	if(i < 0 || i >= n){
		printf("Indice fora do limite do vetor\n");
		exit(1);  
  }

	// verifica se o valor da posicao é NULL
	if(turmas[i]!= NULL){
		printf("Matricula: %s\n", turmas[i]->matricula);
		printf("Nome: %s\n", turmas[i]->nome);
		printf("Turma: %s\n", turmas[i]->turma);
	}	
}


void imprime_aprovados (int n, Aluno** turmas){ 

	int i, qtd_alunos = 0;
	float media = 0, media_total = 0;        

	// itera por todos os alunos e faz o calculo da media do aluno
	for (i = 0; i < n; i++) {

		media = ((turmas[i]->p1 + turmas[i]->p2 + turmas[i]->p3) / 3); 

		// verifica se o aluno foi aprova (media igual ou maior que 7)
		if(media >= 7.0)  {
			// imprime o aluno aprovado
			imprime(n,turmas,i);
			printf("Media do aluno: %.2f\n\n", media);
			media_total += media;
			qtd_alunos++;
		}	
	}

	// verifica se houve algum aluno aprovado
	if(qtd_alunos > 0)
		// Houve aprovados, imprime a media dos alunos aprovados
		printf("Media total dos alunos aprovados eh %.2f\n\n", media_total/qtd_alunos);
	else
		// Sem aprovados
		printf("Nenhum aluno aprovado!");
}

// itera sobre todos os alunos de um turma e calcula a media de cada aluno
// e faz a media de todas as medias dos alunos
float media_turma(int n, Aluno** turmas, char turma) {
	int i, n_alunos = 0;
	float media = 0;
	
	// itera sobre todos os alunos de um turma e calcula a media de cada aluno
	for(i = 0; i < n; i++) {
		if(*turmas[i]->turma == turma) {
			media += ((turmas[i]->p1 + turmas[i]->p2 + turmas[i]->p3) / 3);
			n_alunos++; 
		}
	}

	// retorna a media de todas as medias
	return media / n_alunos;
}

// desaloca o vetor turmas
void desaloca_memoria(int n, Aluno** turmas, int i) {
	
	if(i < 0 || i >= n){
		printf("Indice fora do limite do vetor\n");
		exit(1);  
    }
    
    if(turmas[i]!= NULL) {
    	free(turmas[i]);
    	turmas[i] = NULL;
	}
    
}























