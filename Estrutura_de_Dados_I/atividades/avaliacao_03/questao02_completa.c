#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_CHAR 10

// struct para criar cada veiculo
typedef struct {
	int qtd_movi;
	int cont;
	char placa[MAX_CHAR];
}Veiculo;

typedef struct fila Fila;

// struct para criar a fila que recebe como conteudo os veiculos e a informacao de fim da fila
struct fila{
	Veiculo info;
	Fila* prox;		
};

Fila* inicializa_fila();
int EhVazia(Fila *f);
Fila* insere_fila(Fila* f, Veiculo pl);
Veiculo remove_da_fila(Fila** f);
void imprime_fila(Fila *f);
int procura_veiculo(Fila *f, Veiculo pl);
Veiculo retira_veiculo(Fila *f, char* pl);
int verifica_placa(Veiculo pl);

int main() {
	Fila* f; // delcara a fila
	Veiculo pl; // declara um veiculo para receber as informacoes
	int op;
	char opc;
	
	pl.cont = 0;  // variavel que recebe a informacao de quantos carros foram manobrados para o veiculo sair
	pl.qtd_movi = 0;  // recebe quantas vezes aquele veiculo foi movimentado par aoutros carros sairem
	
	f = inicializa_fila(); // inicializa a fila
	
	do {
		printf("1 - movimentar estacinamento\n0 - sair\n");
		scanf("%d", &op);
		
		switch(op){
	 		case 1:
	 			printf("Digite a placa do carro: ");
				setbuf(stdin, NULL);
				scanf("%[^\n]s", pl.placa);
				setbuf(stdin, NULL);
				
				printf("%s\n", pl.placa);
				
				if(verifica_placa(pl))
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
						if(procura_veiculo(f, pl) == 1)
						{
							printf("Veiculo ja esta em uma vaga do estacionamento\n");
						}
						else{
							// nao esta dentro
							// inserir na fila (entrar no estacionamento)
							f = insere_fila(f, pl);
								imprime_fila(f);
						}
					}
					// deseja sair
					else if(opc == 'S') {
						
						if(procura_veiculo(f, pl) == 0)
						{
							printf("Veiculo nao ocupa nehuma vaga do estacionamento\n");
						}
						else{
							// veiculo esta dentro
							// chamar funcao que retira o veiculo
							// imprime as informacoes de movimentacoes do veiculo removido
							pl = retira_veiculo(f, pl.placa);
							printf("Veiculo %s foi manobrado %d vezes\n\n", pl.placa, pl.qtd_movi);
							printf("Foram manobrados %d veiculos para o veiculo sair\n", pl.cont);
							imprime_fila(f); // imprimea fila apos ter removido o carro
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
			defalt:
				printf("Opcao invalida!");	
	 	}	
		
	}while(op != 0);
	
	return 0;
}


// inicializa a fila estatica
Fila* inicializa_fila(){
  return NULL;
}

// verificas e a fila está cheia
int EhVazia(Fila *f)
{
	if(f == NULL)
	{
		return 1;
	}
	
	return 0;
}

Fila* filaD_alocaNo(Veiculo valor){
  Fila* no = (Fila*) malloc(sizeof(Fila));
  
	strcpy(no->info.placa, valor.placa);
	no->info.cont = 0;
	no->info.qtd_movi = 0;
  no->prox = NULL;
  
  return no;
}

// inseri um veiculo na fila
// verifica se tem espaco na fila
// caso sim, adiciona na fila
Fila* insere_fila(Fila *f, Veiculo pl)
{
	Fila *novo = filaD_alocaNo(pl);

	if (EhVazia(f)){
    // fila vazia, basta inserir
    f = novo; 
  } else{
    // fila possui outros NOs
    Fila* atual = f;
  
    // iterar até a ultima posicao e adicionar o novo no fim da fila
    while (atual->prox != NULL){
      atual = atual->prox;
    }
    atual->prox = novo;

  }
  
  return f;
}

// remove da fila um veiculo
// verifica se existe veiculo para remover
// remove o ultimo veiculo (o mais proximo da saida)
Veiculo remove_da_fila(Fila** f){
  
  Fila* aux;
  Veiculo valor;
  // verifica se a fila nao esta vazia
  if (!EhVazia(*f)){
    // nao esta vazia
    aux = *f; 
    valor =(*f)->info; 
    *f = (*f)->prox; 
    free(aux);
  }else{
  
  exit(1);
  }
  // retorna o valor removido
  return valor;
}


// imprime todos os veiculos da fila
void imprime_fila(Fila *f)
{
	Fila *v = f;
	// verifica se a fila nao esta vazia
	if(!EhVazia(f))
	{
				// nao esta vazia
		// imprime todas as posicoes da fila
		printf("Saida ");

		while(v != NULL)
		{
			printf(" <-- %s ", v->info.placa);
			v = v->prox;
		}

		printf("<-- Entrada\n\n");
	}
	else {
		printf("Fila esta vazia\n");
	}
	printf("\n");
	
}

// itera pela fila procurando um veiculo por meio de sua placa
int procura_veiculo(Fila *f, Veiculo pl)
{
	Fila *v;
	v = f;
	// itera pelas posicoes da fila
	if(!EhVazia(f)) {
		while(v != NULL)
		{
				// compara a placa do carro da iteracao com o carro que deja encontrar
			if(strcmp(v->info.placa, pl.placa) == 0) 
			{
				return 1;
				break;
			}
			v = v->prox;
		}
			// iterou por todos os carros e nao encontrou o carro desejado
	// carro nao esta na fila
		return 0;
	}
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

Veiculo retira_veiculo(Fila *f, char* pl) 
{
	int i = 0, contador = 0, flag = 1;
	Fila *v = f;
	Veiculo retorno;
	Fila* aux;

	aux = inicializa_fila();  // inicializa a fila
		// itera por todos os carros
	if(!EhVazia(f))
	{
		while(v != NULL) 
		{
			retorno = remove_da_fila(&f); 
		
			if(strcmp(retorno.placa, pl) != 0) 
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
			
				aux = insere_fila(aux, retorno); 
				contador++; 
			}
			else { 
			
				retorno.cont = contador; 
			// contador eh a quantidade de carros que eu precisei mover para remover o carro desejado
			// se contador == 0, nao movi nenhum carro, logo, encontrei o carro na primeira posicao
			// da fila (mais proximo da saida)
			// portanto, os carros restantes ja estao na ordem correta e nao preciso movimentar eles
			
				if (contador == 0) 
				{
					flag = 0;
				}
			}
			v = v->prox;
		}
	
		f = aux; 
	}
	else
	{
		printf("Fila esta vazia\n");
	}
	return retorno;
	
}

// verifica se a placa esta no padrao correto
int verifica_placa(Veiculo pl) {  
	
	int i = 0, flag1 = 0, flag2 = 0;


	// ASD3T25
	// itera por todos os caracteres da placa
	while (pl.placa[i] != '\0') 
	{
				// se for uma letra
		// verifica para os 3 primeiros caracteres e o 5 quinto caracter se sao letras
		// padrao das placas
		if (i < 3 || i == 4)
		{
					// verifica se eh letra com a funcao isalpha que verifica se o caracter eh um caracter alfabetico
			if(isalpha(pl.placa[i]) != 0); 
			{
				// incrementa a flag
				flag1++;
			}
		}
	// verifica para os demais caracteres da placa se sao numeros
		if (i == 3 || i > 4)
		{
			if(isdigit(pl.placa[i]) != 0)
			{
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













