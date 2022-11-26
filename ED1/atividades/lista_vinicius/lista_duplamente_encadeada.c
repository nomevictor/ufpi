#include <stdio.h>
#include <stdlib.h>

// Lista duplamente encadeada 

/*

Para a lista duplamente encadeada usamos uma struct renomeada para ListaD
que guardará 3 informaçãoes: 

1 - A informação inteira da lista - int info;
2 - Um ponteiro para a proxima lista - ListaD *prox;
3 - Um ponteiro para a lista anterior - ListaD *prox;

*/
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

// A logica de inverso usada foi a de entrada de dados
void imprimeReverso(ListaD* raiz); // Itera sequencial e imprime as posicoes (já que a lista aponta inicialmente para final) 
void imprime(ListaD* raiz); // Itera até a ultima posicao e retornar usando o ponteiro ant e a cada iteracao, imprime os valores (dessa forma, será impresso do primeiro valor inserido para o ultimo)


int main(){

  ListaD* lista; // Lista principal onde será guardado todos os valores
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
    scanf("%d", &opcao); // ler a opcao digitadad pelo usuario
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
      // para esse caso, itera até o final (primeiro valor inserido)
      // e retornar usando o ponteir ant imprimindo cada valor, dessa forma, 
      // imprimindo do primeiro inserido para o ultimo
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
      lista = retira(lista, valor); // a funcao retorna a propria lista, so que sem o valor que foi removido, 
      // caso tenha sido encontrado 
      break;
    case 0:
      // Finaliza 
      // a condicao de repeticao sera falsa e o programa finalizara
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
  // e por isso eu nao preciso me preocupar em fazer o anterior apontar para o novo no
  // mas quando existe um valor na lista, eu preciso que o poteiro ant dele aponte para
  // o novo valor inserido, portanto

  // verifica se ja existe valor na lista
  if (l != NULL)
  {
    // existe - fazer o ultimo valor da lista apontar seu ponteiro anterior para o no no
    l->ant = novo; 
  }

  // Agora preciso garantir que o novo valor adicionado tambe aponte o ponteiro prox para o
  // ultimo valor inserido na lista
  novo->prox = l; // fazer o novo no apontar para o ultimo inserido
  return novo; // retorna o novo no que sera o para onde a lista apontara
}

// aloca um novo no
ListaD* alocaNovo(int valor){
  // aloca usando o malloc um espaco de memoria para receber um no (struct ListaD)
  ListaD* novo = (ListaD*) malloc(sizeof(ListaD));

  novo->info = valor; // adiciona a informacao enviada no no
  // inicialmente, o no nao tem proximo e nem anterio, portanto, ambos apontam 
  // para NULL
  novo->prox = NULL; 
  novo->ant = NULL;
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
    // a execucao finaliza quando p for NULL (quando ele se tornar o p->prox da primeira posicao
    //, ja que a primeira posicao aponta o proximo para null)
    for (p = raiz; p != NULL; p = p->prox)
    {
      // imprime a informacao do no
      printf("%d ", p->info);
    }
    printf("\n");
  } else
  {
    // raiz = null 
    // a lista estar vazia
    printf("Lista Vazia\n");
  }
}

// para imprimi do primeiro valor para o ultimo, eu preciso primeiro chegar no primeiro valor
// como minha lista aponta para a ultima posicao, primeiro e necessario iterar ate a ultima
// posicao usando o ponteiro prox e depois retornar usando o ponteiro ant e ir imprimindo os valores
// Dessa forma, a impressao ficara do primeiro valor inserido para o ultimo 
void imprime(ListaD* raiz){
  ListaD* p = NULL; // no auxiliar para nao modificarmos o apontamento da lista principal
  
  // no auxiliar para garantir que quando o valor de p = NULL, ou seja,
  // p tenha se tornado o prox do primeiro valor, eu possa armazenar o primeiro valor na aux
  // e assim, poder imprimir do primeiro valor inserido para o ultimo
  ListaD* aux = NULL; 

  // verifica se a lista esta vazia
  if (raiz != NULL)
  {
    // Lista nao esta vazia
    // itera ate o final (chegar o p vira o prox do primeiro valor)
    // e a cada iteracao, armazenar o valor de p em aux
    // assim, quando p se tornar o valor prox da primeira posicao,
    // aux aind sera o valor da primeira posicao
    for (p = raiz; p != NULL; p = p->prox){
      aux = p;
    }

    // iterar usando aux e retornar usando o ponteiro ant
    // e imprimir os valores
    for (; aux != raiz; aux = aux->ant)
    {
      printf("%d ", aux->info);
    }
    printf("%d\n", aux->info);

  } else
  {
    // raiz = null 
    // a lista estar vazia
    printf("Lista Vazia\n");
  }

}

// itera sobre todos os valores e busca o que for igual ao valor enviado por paramentro
ListaD* busca (ListaD* l, int v){
  ListaD* p;
  for (p=l; p != NULL; p = p->prox)
  {
    // verifica se o valor do no e igual ao valor enviado por paramentro
    if (p->info == v)
    {
      // retorna o no
      return p;
    }
  }
  // passou por todos os valores e nao encontrou, retornar p que nesse ponto
  // vale NULL
  return p;
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
  // Se p == l, significa que o valor a ser removido estava na primeira posicao (ultimo valor inserido)
  // assim, n existe valor anterior, apenas o proximo
  // entao devemos garantir que a lista aponte para o proximo valor
  if (p == l)
  {
    l = p->prox;
  }else { 
    // Se for o elemento do meio ou final
    // Caso o elemento esteja no meio, temos dois tratamentos a se fazer:
    // 1 - fazer o ponteiro ant do proximo no apontar para o no anterior ao que sera removido
    // 2 - fazer o ponteiro prox do no anterior apontar para o proximo no do que sera removido
    p->ant->prox = p->prox;

    // so é necessario fazer o ponteiro ant do proximo no apontar para o no anterior ao que sera removido
    // se esse nao for o ultimo no (o primeiro no inserido), pois ele nao tem proximo no
    if (p->prox != NULL)
    {
      p->prox->ant = p->ant;
    }
  }

  free(p); // libera o espaco de memoria do valor removido
  return l; // retorna a lista
}

// Libera todas as posicoes da lista
// itera pela lista e libera cada espaco
// antes de liberar, e importante guar em um no auxiliar o endereco do proximo no
// para que nao perca a posicao e o no fique armazenado se poder ser liberado
ListaD* libera(ListaD* l){
  ListaD* p = l;
  ListaD* t = NULL;
  while (p != NULL)
  {
    t = p->prox;
    free(p);
    p = t; 
  }
  p = NULL;
  return NULL;
} 