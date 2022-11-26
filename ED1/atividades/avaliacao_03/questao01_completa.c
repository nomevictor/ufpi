#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define TAM 10
#define MAX_CHAR 10

// struct para criar cada veiculo
typedef struct{
	char placa[MAX_CHAR];
	int qtd_movi;
	int cont;
}Veiculo;

// struct para criar a fila que recebe como conteudo os veiculos e a informacao de fim da fila
typedef struct {
	Veiculo vagas[TAM]; // fila estatica com tamnaho pre-definido
	int fim;		
}Fila;

// funcoes
void inicializa_fila(Fila *f); // inicializa a fila com fim = -1
int EhCheia(Fila *f); // verifica se a fila ja esta cheia
int EhVazia(Fila *f); // verifica se a fila esta vazia
void insere_fila(Fila *f, Veiculo *pl); // insere um carro na fila
Veiculo remove_da_fila(Fila *f); // remove um carro da fila e retorna o carro removido (utilizada na funcao retira veiculo)
void imprime_fila(Fila *f); // imprime a fila
int procura_veiculo(Fila *f, Veiculo *pl); // itera pela fila procurando por um veiculo (procura pela placa)
void retira_veiculo(Fila *f, Veiculo *pl); // retira o veiculo que deseja sair do estacionamento, ttratando para manter a ordem do estacionamento
int verifica_placa(Veiculo *pl); // verifca se a placa digitada eh uma placa valida 


int main() {
	Fila f1; // delcara a fila
	Veiculo pl; // declara um veiculo para receber as informacoes
	char opc;
	int op;

	pl.cont = 0; // variavel que recebe a informacao de quantos carros foram manobrados para o veiculo sair
	pl.qtd_movi = 0; // recebe quantas vezes aquele veiculo foi movimentado par aoutros carros sairem
	
	inicializa_fila(&f1); // inicializa a fila
	
	do {
		// leitura da opcao escolhida pelo usuario
		printf("1 - movimentar estacinamento\n0 - sair\n");
		scanf("%d", &op);
		
		switch(op){
	 		case 1:
			 	// ler a placa e verifica se eh valida
	 			printf("Digite a placa do carro: ");
				setbuf(stdin, NULL);
				scanf("%[^\n]s", pl.placa);
				setbuf(stdin, NULL);
				if(verifica_placa(&pl))
				{
					// se for valida, verifica se o usuario quer sair ou entrar no estacionamento
					// um veiculo so pode sair se estiver dentro (confere pela placa)
					// um veiculo so pode entrar se ja n extiver dentro (confere pela placa)
					// carros nao possuem placas iguais
					do {
					setbuf(stdin, NULL);
					printf("Digite 'E' para entrar ou 'S' para sair do estacionamento: \n");
					scanf("%c", &opc);
					setbuf(stdin, NULL);
					opc = toupper(opc);
					
					}while(opc != 'E' && opc != 'S');
					
					// se deseja entrar no estacionamento
					if(opc == 'E') {
		
						// verificar se ja esta dentro
						if(procura_veiculo(&f1, &pl) == 1)
						{
							printf("Veiculo ja esta em uma vaga do estacionamento\n");
						}
						else{
							// nao esta dentro
							// inserir na fila (entrar no estacionamento)
							insere_fila(&f1, &pl);
							imprime_fila(&f1);
						}
					}
					// deseja sair
					else if(opc == 'S') {
						
						// verificar se esta la dentro
						if(procura_veiculo(&f1, &pl) == 0)
						{
							// veiculo nao esta dentro do estacionamento
							printf("Veiculo nao ocupa nehuma vaga do estacionamento\n");
						}
						else{
							// veiculo esta dentro
							// chamar funcao que retira o veiculo
							// imprime as informacoes de movimentacoes do veiculo removido
							retira_veiculo(&f1, &pl);
							printf("Veiculo %s foi manobrado %d vezes\n\n", pl.placa, pl.qtd_movi);
							printf("Foram manobrados %d veiculos para o veiculo sair\n", pl.cont);
							imprime_fila(&f1); // imprimea fila apos ter removido o carro
						}
					}
				}
				else{
					// placa digitada foi invalida
					printf("Placa invalida!('XXX'9999)\n");
					
				}
			break;
			case 0:
				// finalizar programa
				break;
			default:
				// opcao nao existe
				printf("Opcao invalida!");	
	 	}	
		
	}while(op != 0);

	return 0;
}

// inicializa a fila estatica
void inicializa_fila(Fila *f)
{
	// atribui ao fim da fila - valor -1
	f->fim = -1;
}

// verificas e a fila está cheia
int EhCheia(Fila *f)
{
	// com para o valor fim dentro da fila com o tamanho maximo da fila
	// que eh pre-definidio
	if(f->fim >= TAM - 1)
	{
		// fila cheia, retorna 1 (true)
		return 1;
	}
	
	return 0;
}

// verifica se a fila esta vazia
int EhVazia(Fila *f)
{
	// caso o fim da fila equival a -1 (valor incial quando ele eh inicializada)
	// ela esta vazia
	if(f->fim == -1)
	{
		// fila vazia, retorna 1 (true)
		return 1;
	}
	return 0;
}

// inseri um veiculo na fila
// verifica se tem espaco na fila
// caso sim, adiciona na fila
void insere_fila(Fila *f, Veiculo *pl)
{
	// verifica se a fila esta cheia
	if(!EhCheia(f))
	{
		// fila eh diferente de cheia (existe vagas)
		f->fim++;
		f->vagas[f->fim] = *pl;
	}
	else {
		printf("\nEstacionamento lotado!\n");
	}
}

// remove da fila um veiculo
// verifica se existe veiculo para remover
// remove o ultimo veiculo (o mais proximo da saida)
Veiculo remove_da_fila(Fila *f) {
	int i;
	Veiculo valor;
	
	// verifica se a fila nao esta vazia (se existe veiculos para remover)
	if(!EhVazia(f))
	{
		// caso sim
		// valor recebe o veiculo que sera removido
		valor = f->vagas[0];
		
		// itera por todas as posicoes e atualiza a posicao atual com o valor da proxima posicao
		for(i = 0; i <= f->fim; i++)
		{
			f->vagas[i] = f->vagas[i+1];
		}
		f->fim--;	
	}
	else{
		// estacionamento esta vazio
		printf("Estacionamento vazio!\n");
	}
	return valor;
}

// imprime todos os veiculos da fila
void imprime_fila(Fila *f)
{
	int i;
	
	// verifica se a fila nao esta vazia
	if(!EhVazia(f))
	{
		// nao esta vazia
		// imprime todas as posicoes da fila
		printf("Saida ");
		
		for(i = 0; i <= f->fim; i++)
		{
			printf("<-- %s ", f->vagas[i].placa);
		}
		
		printf("<-- Entrada\n\n");
	}
	else {
		// fila vazia
		printf("Fila esta vazia!\n");
	}
		
}

// itera pela fila procurando um veiculo por meio de sua placa
int procura_veiculo(Fila *f, Veiculo *pl)
{
	int i;

	// itera pelas posicoes da fila
	for(i = 0; i <= f->fim; i++)
	{
		// compara a placa do carro da iteracao com o carro que deja encontrar
		if(strcmp(f->vagas[i].placa, pl->placa) == 0)
		{
			// carro encontrado
			return 1;
			break;
		}
	}
	// iterou por todos os carros e nao encontrou o carro desejado
	// carro nao esta na fila
	return 0;
}

// a funcao retira veiculo ireta pelos veiculos e retira todos os veiculos 
// da frente do veiculo que saira do estacionamento
// se houver pelo menos um veiculo na frente do que desejo remover
// eles irao para o final da fila, mas depois, os carros que estao depois 
// do veiculo para ser removido precisam se movimentar para a ordem dos carros
// voltarem ao normal

// mas se para um carro sair, n existe outro carro na frente,
// quando ele sair, a ordem se manterá, portanto, os carros apos o veiculo removido
// n precisam se movimentar
void retira_veiculo(Fila *f, Veiculo *pl)
{
	int i = 0, contador = 0, flag = 1;
	Veiculo retorno;
	Fila aux;

	inicializa_fila(&aux); // inicializa a fila

	// itera por todos os carros
	for(i = 0; i <= f->fim;)
	{
		// remove o carro mais proximo da saida
		retorno = remove_da_fila(f);
		
		// verifica se este carro eh o que realmente saira do estacionamento
		if(strcmp(retorno.placa, pl->placa) != 0)
		{
			// nao eh o carro que desejo remover
			// verifica a flag que guarda a informacao de movimentacoes de um determinado carro para que outro possa sair
			// se essa flag eh true, significa que existe pelo menos um carro na frente do desejado para remover, logo,
			// depois de remover, todos os outros vao se movimentar (ganha o incremento da linha 281) para voltar a ordem original

			// essa flag so sera falsa se o carro que eu desejo remover for o primeiro, entao eu nao
			// preciso mover os demais carros, pois eles já estoa na ordem correta
			if (flag)
			{
				retorno.qtd_movi++;
			}
			
			// insiro o carro em uma fila auxiliar
			insere_fila(&aux, &retorno);
			contador++; // quantidade de carros que eu precisei mover para remover o carro desejado
		}
		else {
			// encontrei o carro que desejo remover
			retorno.cont = contador;
			*pl = retorno;
			

			// contador eh a quantidade de carros que eu precisei mover para remover o carro desejado
			// se contador == 0, nao movi nenhum carro, logo, encontrei o carro na primeira posicao
			// da fila (mais proximo da saida)
			// portanto, os carros restantes ja estao na ordem correta e nao preciso movimentar eles
			if (contador == 0)
			{
				flag = 0;
			}
		}
	}
	
	// fila principal recebe fila auxiliar onde ficou todos os carros que ainda estao no estacionamento
	*f = aux;
}


// verifica se a placa esta no padrao correto
int verifica_placa(Veiculo *pl) {
	
	int i = 0, flag1 = 0, flag2 = 0;

	// ASD3T25
	// itera por todos os caracteres da placa
	while (pl->placa[i] != '\0')
	{
		// se for uma letra
		// verifica para os 3 primeiros caracteres e o 5 quinto caracter se sao letras
		// padrao das placas
		if (i < 3 || i == 4)
		{
			// verifica se eh letra com a funcao isalpha que verifica se o caracter eh um caracter alfabetico
			if(isalpha(pl->placa[i]) != 0);
			{
				// incrementa a flag
				flag1++;
			}
		}

		// verifica para os demais caracteres da placa se sao numeros
		if (i == 3 || i > 4)
		{
			// isdigit retorna se o caracter eh um numero ou nao
			if(isdigit(pl->placa[i]) != 0)
			{
				// incrementa a flag
				flag2++;
			}
		}

		// para ser valida, a placa deve ter 4 letras (flag das letras = 4) e flag do numeros = 3
		// e nao pode passar disso, logo o somatorio deve ser = 7
		if (flag1 == 4 && flag2 == 3 && flag1 + flag2 == 7)
		{
			return 1;
		}
		i++;
	}
	
	return 0;
}

