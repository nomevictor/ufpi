#include <stdio.h>
#include <stdlib.h>

// Lista duplamente encadeada circular
// o algoritmo de lista duplamente ligada circular é semelhante ao de lista duplamente ligada, portanto algumas explicacoes serao semelhantes ou iguais a de lista duplamente encadeada
// algumas grandes diferencas e na condicao de parada, ja que agora ao inves de NULL,
// uso o endereco de que a lista aponta, ja que todos os anteriores e proximos aponta
// para algum endereco de memoria

// outra boa mudanca e na funcao de imprimir, ja que eu nao preciso iterar e depois
// voltar imprimindo, ja que posso sair do final e ir para o inicio com a lista
// duplamente ligada circular


/*
Para a lista duplamente encadeada circular tambem usamos uma struct renomeada para ListaD que guardará 3 informaçãoes: 

1 - A informação inteira da lista - int info;
2 - Um ponteiro para a proxima lista - ListaD *prox;
3 - Um ponteiro para a lista anterior - ListaD *prox;*/

typedef struct lista ListaD;

struct lista{
  int info;
  ListaD *prox;
  ListaD *ant;
};

ListaD* inicializa(); // Inicializa a lista com NULL
ListaD* insere(ListaD* l, int valor); /*insere ele no final da lista*/
ListaD* alocaNovo(int valor); // Aloca um no para ser inserido na lista posteriormente
ListaD* busca(ListaD* l, int v); // Itera sequencialmente pela lista e busca um valor
ListaD* retira(ListaD* l, int v); // Itera sequencial pela lista, encontra o valor, conecta o nó anterior com o proximo e libera a memoria do valor a ser removido

ListaD* libera(ListaD* l); // Itera sequencialmente pela lista e libera todos os especo de memoria alocados

void imprimeReverso(ListaD* raiz); // para imprimir o reverso, itero sequencialmente usando o prox e imprimo os valore
void imprime(ListaD* raiz); // para o imprime normal, uso o ponteiro
// que por ser circular, me levara da ultima para aa primeira posicao
// de maneira mais rapida e assim, itero sequencialmente usando o ponteiro ant e imprimo os valores

int main(){

  ListaD* lista;  // Lista principal onde será guardado todos os valores
  ListaD* aux; // lista auxiliar usada para receber o retorno da funcao busca
  int opcao; // variavel para ler a opcao do menu digitada
  int valor; // variavel auxiliar para receber os valores digitados pelo usuario

  // inicializacao da lista - a funcao inicializa apenas retorna NULL
  lista = inicializa();
  

  // do while que repetira até que o usuario escolha finalizar o programa
  do
  {
    // imprime o menu com todas as opcoes
    printf("1 - Insere\n2 - Imprime (Do primeiro para o ultimo)\n3 - Imprime Reverso (Do ultimo para o primeiro)\n4 - Busca\n5 - Remove\n0 - Finalizar\n");
    printf("Escolha uma opcao: ");
    setbuf(stdin, NULL);
    scanf("%d", &opcao);// ler a opcao digitadad pelo usuario
    system("clear"); // Limparia a tela do terminal, mas dependerá do sistemas operacional usado para teste

    // acredito que para windows, funcionaria com system("cls");

    // switch com todas as opcoes do menu
    switch (opcao)
    {
    case 1:
      // Insere um dado na lista
      // leitura do valor a inserir
      printf("Digite o valor que deseja inserir: ");
      scanf("%d", &valor);

      // envia o dado e a lista para a funcao inseri que retornará o novo valor inserido
      // que será o inicio (para onde a lista aponta)
      lista = insere(lista, valor);
      break;
    case 2:
      // Imprime todos os valores da lista
      // para esse caso, usara o ponteiro ant para ir para o inicio e
      // o ant tambem para iterar sequencialmente e imprimir os valores
      imprime(lista);
      break;  
    case 3:
      // imprime reverso
      // apenas itera imprimindo a informacao de cada posicao
      // como a lista ja aponta para a ultima posicao (ultimo inserido)
      // basta iterar usando o ponteiro prox ate a primeira e assim, imprimir
      // do ultimo para o primeiro
      imprimeReverso(lista);
      break;
    case 4:
      // Busca
      // ler o valor que deseja buscar e envia para a funcao busca
      // caso encontre, a funcao retorna o proprio no
      // caso nao, retorna NULL
      printf("Qual valor deseja busca: ");
      scanf("%d", &valor);
      aux = busca(lista, valor);
      if (aux)
      {
        // encontrou - retornou o no - imprime o endereco do no
        printf("Valor encontrado\nEndereco: %p\n", aux);
      } else {
        // nao encontrou - retornou NULL - informa ao usuario que nao encontrou
        printf("valor não encontrado\n");
      }
      break;
    case 5:
      // retira
      // ler o valor que deseja retirar e envia para funcao retira juntamente com a lista
      printf("Qual valor deseja remover: ");
      scanf("%d", &valor);
      lista = retira(lista, valor);
      // a funcao retorna a propria lista, so que sem o valor que foi removido, 
      // caso tenha sido encontrado 
      break;
    case 0:
      // Finaliza
      break;
    default:
     // usuario digitou uma opçao que nao existe no menu
      printf("Opcao invalida!\nRepita a operacao.");
      break;
    }
  } while (opcao != 0);

  libera(lista); // libera a lista
  lista = NULL; // define com null para nao conter os valores (mesmo que a memoria ja esteja livre)

  return 0;
}

// A funcao inicializa apenas retorna NULL
ListaD* inicializa(){
  return NULL;
}

// inseri um no na lista
ListaD* insere(ListaD* l, int valor){
  // A funcao insere chama a funcao alocaNovo que aloca um no e retorna o no para
  // a listaD aux chamada novo  
  ListaD* novo = alocaNovo(valor);

  // Quando nao existe nenhum no adicionado ainda, a minha lista aponta para NULL


  // mas quando existe um valor na lista, e necessario fazer algumas acoes

  // 1 - como a lista é circular e a lista sempre aponta para o ultimo valor, l->ant significa o primeiro valor adicionado na lista. Portanto, como estou adicionando um novo valor, eu preciso que o ant do meu novo valor aponte para o primeiro, logo
  // novo->ant = l->ant;

  // 2 - feito o passo 1, eu sei que novo->ant é o primeiro valor inserido. Agora preciso garantir que o prox do primeiro valor inserido aponte para o ultimo valor inserido (novo). Logo
  // novo->ant->prox = novo;

  // 3 - feito o passo 1 e 2, eu garanto a circulacao da minha lista. Agora devo o ant do ultimo valor da minha lista apontar para o novo valor. 
  // l->ant = novo;

  // 4 - E por fim, fazer o prox do meu novo valor, apontar para o ultimo valor da lista que tinha sido inserido.
  // novo->prox = l;

  // 5 - feito isso, basta fazer a lista apontar para o novo valor, que sera feito no momento do retorno da funcao

  // verifica se ja existe valor na lista

  if (l != NULL)
  {
    /* A minha lista já possui algum item */
    novo->ant = l->ant;
    novo->ant->prox = novo;
    l->ant = novo;
    novo->prox = l;
  }

  return novo;
}

ListaD* alocaNovo(int valor){
  ListaD* novo = (ListaD*) malloc(sizeof(ListaD));
  novo->info = valor;
  // adiciona a informacao enviada no no
  // inicialmente, o no nao tem proximo e nem anterio, portanto, ambos apontam 
  // para NULL
  novo->prox = novo;
  novo->ant = novo;
  return novo; // retorna o no
}

// itera sequencialmente e imprime as informacoes de cada no
// com ja foi dito, a lista aponta para o ultimo, portanto, para
// imprimir do ultimo para o primeiro, basta iterar sequencialmente
// usando o ponteiro prox para o proximo no e em cada posicao, imprimir o
// o valor em cada no
void imprimeReverso(ListaD* raiz){
  ListaD* p = NULL; // no auxiliar para n modificamos o apontamento da lista principal

  // verifica se a lista esta vazia
  // a lista so esta vazia quando ela nao aponta para uma struct Lista, ou seja, tem seu valor NULL
  if (raiz != NULL)
  {
    // itera sobre cada no da lista
    // o p recebe o valor inicial da lista, que e o ultimo valor inserido e
    // a execucao finaliza quando p->prox == raiz (quando p se tornar o penultimo valor inserido)
    // isso significa que ele iterou por todas as posicoes e retornou a posicao inicial (a raiz)
    for (p = raiz; p->prox != raiz; p = p->prox)
    {
      // imprime a informacao do no
      printf("%d ", p->info);
    }
    printf("%d\n", p->info);
  } else
  {
    // raiz = null 
    // a lista estar vazia
    printf("Lista Vazia\n");
  }
}

// para imprimi do primeiro valor para o ultimo, eu preciso primeiro chegar no primeiro valor
// como minha lista aponta para a ultima posicao e ela e circular, basta eu iterar sequencialmente, mas usando o ponterio ant de cada no

// a condicao de parada sera o p ter passado por todos os valores (p = raiz, ja que a raiz e o ponto de partida de p) 
void imprime(ListaD* raiz){
  ListaD* p = NULL;  // no auxiliar para nao modificarmos o apontamento da lista principal

  // verifica se a lista esta vazia
  if (raiz != NULL)
  {
    // nao esta vazia - itera usando o ponteiro ant
    for (p = raiz->ant; p != raiz; p = p->ant)
    {
      // imprime os valores
      printf("%d ", p->info);
    }
    printf("%d\n", p->info);
  } else
  {
    printf("Lista Vazia\n");
  }
}

// itera sobre todos os valores e busca o que for igual ao valor enviado por paramentro
ListaD* busca (ListaD* l, int v){
  ListaD* p;
  ListaD* aux;

  // itera até chegar o ponto inicial(l), ou seja, passar por todos os valores e nao encontrar o valor buscado
  for (p=l->prox; aux != l; p = p->prox)
  {
    // verifica se o valor do no e igual ao valor enviado por paramentro
    if (p->info == v)
    {
      // retorna o no
      return p;
    }
    aux = p;
  }
  // passou por todos os valores e nao encontrou, retornar NULL
  return NULL;
}



ListaD* retira(ListaD* l, int v){
  ListaD* p;

  // chama a funcao busca para encontrar o valor na lista
  // caso encontre, a funcao busca ja retorna o valor a ser removido
  p = busca(l, v);

  // se p = NULL, significa que o a funao busca iterou por todos
  // os valores e nao encontrou o valor que deveria ser removido
  if (p == NULL)
  {
    printf("Valor nao encontrado!\n");
    return l;
  }

  if (p == l)
  {

  // se p = l, significa que o valor a ser removido estava na primeira posicao (ultimo valor inserido). antes de remover, para nao quebrar a relacao entre os nos, devemos fazer as seguintes acoes
  
  // 1 - fazer com que o ponteiro ant do proximo no aponte para o inicio (que atualmente é p->ant) logo
  // p->prox->ant = p->ant;

  // 2 - Fazer com que a lista para de apontar para o valor que sera removido e aponte para  o proximo 
  // l = p->prox;

  // 3 - fazer com que o primeiro valor aponte agora para o ultimo valor da lista (o proximo ao que sera removido)
  // l->ant->prox = l;
    p->prox->ant = p->ant;
    l = p->prox;
    l->ant->prox = l;
  }else { // Se for o elemento do meio e final

    // Se for o elemento do meio ou final
    // temos dois tratamentos a se fazer:
    // 1 - fazer o ponteiro ant do proximo no apontar para o no anterior ao que sera removido
    // 2 - fazer o ponteiro prox do no anterior apontar para o proximo no do que sera removido
    p->ant->prox = p->prox;
    p->prox->ant = p->ant;
  }

  free(p);
  return l;
}

// Libera todas as posicoes da lista
// itera pela lista e libera cada espaco
// antes de liberar, e importante guar em um no auxiliar o endereco do proximo no
// para que nao perca a posicao e o no fique armazenado se poder ser liberado
ListaD* libera(ListaD* l){
  ListaD* p = l;
  ListaD* t = NULL;
  while (t != l)
  {
    t = p->prox;
    free(p);
    p = t; 
  }
  p = NULL;
  return NULL;
}