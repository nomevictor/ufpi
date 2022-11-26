#include <stdio.h>
#include <stdlib.h>


/* 

  A logica de solucao consiste em remover um valor da pilha e um valor da fila,
  verificar se o valor da fila eh ou nao par

  caso seja par, empilhe primeiro o valor da fila e em seguida, o valor da pilha
  caso não seja par, empilhe primeiro o valor da pilha e em seguida, o valor da fila

  apos isso, pode ocorrer de restar valores na fila ou na pilha, entao
  basta enviar todos para pilha resultado

*/

#define TAM 10

// decalracao da struct da pilha dinâmica
typedef struct pilhaD PilhaD;

struct pilhaD{
  int info;
  PilhaD* prox;
};

// declaracao da struc da fila
typedef struct filaD FilaD;

struct filaD{
  int info;
  FilaD* prox;
};

// funcoes para a fila
FilaD* filaD_inicializa(); // inicializar com NULL
FilaD* filaD_alocaNo(int valor); // alocar um NO na fila (funcao chamada pela funcao filaD_insere)
FilaD* filaD_insere(FilaD* f, int valor); // insere um NO na fila
int filaD_vazia(FilaD* f); // verifica se a fila esta vazia
int filaD_remove(FilaD** f); // remove um item da fila
void filaD_imprime(FilaD* fila); // imprime todos os NOs da fila
FilaD* libera_fila(FilaD* l); // libera a memoria alocada da fila


// pilha
PilhaD* pilhaD_inicializa(); // inicializar com NULL
PilhaD* pilhaD_alocaNo(int valor); // alocar um NO na fila (funcao chamada pela funcao filaD_insere)
PilhaD* pilhaD_push(PilhaD* p, int valor); // insere um NO na pilha
PilhaD* libera_pilha(PilhaD* l); // libera a memoria alocada da pilha
int pilhaD_vazia(PilhaD* p); // verifica se a pilha esta vazia
int pilhaD_pop(PilhaD** p); // remove um item da pilha
void pilhaD_imprime(PilhaD* pilha); // imprime todos os NOs da pilha
// falta liberar a pilha

// combina os valores da fila com a pilha com base nas condicoes 
PilhaD* montarPilhaResultado(FilaD* fila, PilhaD* pilha);

int main(){

  FilaD* fila; // declaracao da fila
  PilhaD* pilha; // declaracao da pilha
  PilhaD* pilha_resultado; // declaracao da pilha que recebera os valores resultantes
  int op, valor;
  char finalizar;
  

  // inicializando com NULL as pilhas
  pilha_resultado = pilhaD_inicializa();
  fila = filaD_inicializa();
  pilha = pilhaD_inicializa();


  // inserir na fila
  /* 
  
    Itera ate que o usuario escolha para finalizar a insercao de dados
    da fila
  */
  printf("------INSERIR VALORES NA FILA-----");
  do
  {
    // ler a escolha do usuario
    printf("\n1 - Inserir valor na fila\n0 - Finalizar insercao na fila\n\n");
    scanf("%d", &op);
    if (op == 1)
    {
      // ler o valor para ser inserido
      printf("Digite o valor que deseja inserir na fila: ");
      scanf("%d", &valor);
      // insere na pilha
      fila = filaD_insere(fila, valor); 
      printf("\nValor inserido na fila\n\n");
      printf("FILA - ");
      filaD_imprime(fila); // imprime o estado atual da fila
    }
    
  } while (op != 0);

  // atualiza op para poder reutilizar no while sequinte
  op = -1;
  
  // inserir na pilha
  printf("\n------INSERIR VALORES NA PILHA-----\n\n");

  // itera ate que o usuario decida finalizar o processo de insercao dentro da pilha
  
  do
  {
    // ler a escolha do usuario
    printf("\n1 - Inserir valor na pilha\n0 - Finalizar insercao na pilha\n\n");
    scanf("%d", &op);
    
    if (op == 1)
    {
      // deseja inserir na pilha
      // ler valor
      printf("Digite o valor que deseja inserir na pilha: ");
      scanf("%d", &valor);
      // insere na pilha
      pilha = pilhaD_push(pilha, valor);
      printf("\nValor inserido na pilha\n\n");
      pilhaD_imprime(pilha);
    }
    

  } while (op != 0);


  // mostrar pilha resultante
  // envia a fila e a pilha para a funcao montarPilhaResultado
  // que fara a juncao com base nas condicoes e retornara a pilha resultado
  // contendo os valores da fila e da pilha

  pilha_resultado =  montarPilhaResultado(fila, pilha);

  // imprimir a pilha resultado
  printf("\n----PILHA RESULTADO-----\n");
  printf("\n");
  pilhaD_imprime(pilha_resultado);
  printf("\n");
  printf("------------------------\n");

  return 0;
}



PilhaD* montarPilhaResultado(FilaD* fila, PilhaD* pilha){
  int valor_removido_fila;
  int  valor_removido_pilha;

  PilhaD* pilha_resultado;
  pilha_resultado = pilhaD_inicializa();

  // itera enquanto nao encontrar o final da pilha ou da fila
  while (fila != NULL && pilha != NULL)
  {
    // retirar valor da filha
    valor_removido_fila = filaD_remove(&fila);

    // retirar valor da pilha
    valor_removido_pilha = pilhaD_pop(&pilha);

    // compara esse valores e empilhar
    // verifica se o valor removido da fila eh par
    if (valor_removido_fila % 2 == 0)
    {
      // valor da filha é par
      // empilha primeiro o valor da fila e depois do da pilha
      pilha_resultado = pilhaD_push(pilha_resultado, valor_removido_fila);
      pilha_resultado = pilhaD_push(pilha_resultado, valor_removido_pilha);
    }else {
      //  valor da filha é impar, empilhar primeiro o valor da pilha
      pilha_resultado = pilhaD_push(pilha_resultado, valor_removido_pilha);
      pilha_resultado = pilhaD_push(pilha_resultado, valor_removido_fila);
    }
  }
  
  // Empilhar os valores restantes (caso haja) da fila na pilha_resultado
  while (fila != NULL)
  {
    valor_removido_fila = filaD_remove(&fila);
    pilha_resultado = pilhaD_push(pilha_resultado, valor_removido_fila);
  }
  
  // Empilhar os valores restantes (caso haja) da pilha na pilha_resultado 
  while (pilha != NULL)
  {
    valor_removido_pilha = pilhaD_pop(&pilha);
    pilha_resultado = pilhaD_push(pilha_resultado, valor_removido_pilha);
  }  

  return pilha_resultado;
}


// -------FUNCORES DA FILA---------

// inicializa a fila com NULL
FilaD* filaD_inicializa (){
  return NULL;
}

// aloca um espaco de memoria para o NO e atribui ao ponteiro info o valor 
// enviado pelo ususario 
FilaD* filaD_alocaNo(int valor){
  FilaD* no = (FilaD*) malloc(sizeof(FilaD));
  
  no->info = valor;
  no->prox = NULL;
  
  return no;
}

// insere um novo NO na fila
FilaD* filaD_insere(FilaD* f, int valor){
  // aloca um NO
  FilaD *novo = filaD_alocaNo(valor);
  
  // verifica se a fila esta vazia ou ja possui valores (necessario para fazer o encadeamento)
  if (filaD_vazia(f)){
    // fila vazia, basta inserir
    f = novo; 
  }else{
    // fila possui outros NOs
    FilaD* atual = f;
  
    // iterar até a ultima posicao e adicionar o novo no fim da fila
    while (atual->prox != NULL){
      atual = atual->prox;
    }
    atual->prox = novo;
  }
  
  return f;
}

// verifica se a fila esta vazia (se a f aponta para NULL)
int filaD_vazia(FilaD* f){
  if(f == NULL){
    return 1;
  }

  return 0;
}

// remove um NO da fila (o no que a fila aponta)
int filaD_remove(FilaD** f){
  
  FilaD* aux;
  int valor;
  // verifica se a fila nao esta vazia
  if (!filaD_vazia(*f)){
    // nao esta vazia
    aux = *f; // auxiliar para liberar a memoria
    valor =(*f)->info; // valor da posicao que esta sendo removida (sera retornado pela funcao)
    *f = (*f)->prox; // atualiza o apontamento da fila para o proximo NO
    free(aux);
  }else{
  
  exit(1);
  }
  // retorna o valor removido
  return valor;
}

// itera pela fila e imprime todos os nos
void filaD_imprime(FilaD* fila){
  FilaD* p; // ponteiro auxiliar para nao comprometer o apontamento da fila

  // itera por cada posicao da fila (atualizando a posicao apartir do ponteiro ->prox que guarda o endereco do proximo NO)
  for (p = fila; p != NULL; p = p->prox)
  {
    // imprime a informacao do no
    printf("%d ", p->info);
  }
  printf("\n");
}

// -------PILHA--------
// inicializa a pilha com NULL
PilhaD* pilhaD_inicializa (){
return NULL;
}

// aloca um espaco de memoria para o NO e atribui ao ponteiro info o valor 
// enviado pelo ususario 
PilhaD* pilhaD_alocaNo(int valor){
  PilhaD* no = (PilhaD*) malloc(sizeof(PilhaD));
  no->info = valor;
  no->prox = NULL;
  return no;
}

// insere um novo NO na pilha  
PilhaD* pilhaD_push(PilhaD* p, int valor){
  PilhaD *novo = pilhaD_alocaNo(valor);
  novo->prox = p;
  return novo;
}

// verifica se a fila esta vazia (vazia se apontar para NULL)
int pilhaD_vazia(PilhaD* p){
  if(p == NULL){
    return 1;
  }
  return 0;
}

// remove um NO da pilha (o no que a pilha aponta)
int pilhaD_pop(PilhaD** p){
  
  PilhaD* aux;
  int valor;
  // verifica se a pilha nao esta vazia
  if (!pilhaD_vazia(*p)){
    // nao esta vazia
    aux = *p; // auxiliar para liberar a memoria
    valor =(*p)->info; // valor da posicao que esta sendo removida (sera retornado pela funcao)
    *p = (*p)->prox;  // atualiza o apontamento da fila para o proximo NO
    free(aux);
  }else{
    exit(1);
  }
  // retorna o valor removido
  return valor;
}

// itera pela fila e imprime todos os nos
void pilhaD_imprime(PilhaD* pilha){
  PilhaD* p; // ponteiro auxiliar para nao comprometer o apontamento da pilha

    // itera por cada posicao da pilha (atualizando a posicao apartir do ponteiro ->prox que guarda o endereco do proximo NO)
  printf("TOPO\n");
  for (p = pilha; p != NULL; p = p->prox)
  {

    printf("%d \n", p->info);
  }
  printf("BASE\n");

  printf("\n");
}

// libera o espaco de memoria alocado dinamicamente
FilaD* libera_fila(FilaD* l){
  // lista auxiliar (usada para liberar os espacos)
  FilaD* p = l;
  // lista auxiliar (usada para n perder o endereco da proxima posicao para liberar)
  FilaD* t = NULL;

  // itera enquanto tiver posicoes alocadas
  while (p != NULL)
  {
    t = p->prox; // t guar o proximo endereco para liberar
    free(p);  // libera o espaco de memoria de p (que eh o espaco de l tbm)
    p = t; // p recebe a proxima posicao para liberar
  }
  p = NULL;
  return NULL;
} 

// libera o espaco de memoria alocado dinamicamente
PilhaD* libera_pilha(PilhaD* l){
  // lista auxiliar (usada para liberar os espacos)
  PilhaD* p = l;
  // lista auxiliar (usada para n perder o endereco da proxima posicao para liberar)
  PilhaD* t = NULL;

  // itera enquanto tiver posicoes alocadas
  while (p != NULL)
  {
    t = p->prox; // t guar o proximo endereco para liberar
    free(p);  // libera o espaco de memoria de p (que eh o espaco de l tbm)
    p = t; // p recebe a proxima posicao para liberar
  }
  p = NULL;
  return NULL;
} 