#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// definicao do maximo de caracteres para o CPF
#define MAX_CPF_CHAR 12

// struct para armazenar os dados das pessoas
typedef struct 
{
  char CPF[12];
  char nome[50];
  int idade;
}Pessoa;

// struct para criacao de uma lista dinamica e armazenar ar pessoas
typedef struct lista ListaD;

struct lista{
  Pessoa pessoa;
  ListaD *prox;
  ListaD *ant;
};

// ----- FUNCOES ------

ListaD* inicializa(); // inicializa a lista
ListaD* alocaNovo(Pessoa pessoa); // aloca 
ListaD* insere(ListaD* l, Pessoa pessoa); // insere uma pessoa na lista
ListaD* libera(ListaD* l);
void ordenaCPF(ListaD* l); // ordena a lista pelo metodo InsertionSort
void ordenaPorIdade(ListaD* l); // ordena pela idade com o metodo insertionSort
void imprimeReverso(ListaD* raiz); // imprime a lista (do ultimo inserido para o primeiro)
ListaD* pessoasComIdadeMenor(ListaD* l, int idade); //retorna uma lista com todas as pessoas existe na lista passada por parametro que possua idade menor a idade informada
Pessoa encontraVizinhoMaisVelho(ListaD* l, char* cpf, Pessoa* usuario); // retorna o vizinho mais velho de uma pessoa informada pelo usuario

int nomeValido(const char* nome); // verifica se o nome eh valido (nao eh vazio, nao eh apenas espacos e nao contem numeros)
int cpfValido(const char* nome); // verifica se o CPF contem apenas numeros que contenha 11 numeros

int main(){

  Pessoa novaPessoa; // recebe os dados da pessoa informada pelo usuario
  Pessoa vizinhoMaisVelho, usuario; // pessoas auxiliares para receber o vizinho mais velho de um usuario e o proprio usuario, respectivamente 
  char cpf[MAX_CPF_CHAR]; // recebe o cpf digitado pelo usuario
  ListaD* lista; // lista para guardar todas as pessoas
  ListaD* listaAuxiliar; // lista auxiliar para receber todas as pessoas com idade menor que idade informada 
  int op, idade;
  lista = inicializa(); // inicializa a lista

  // garantir que nome inicia vazio
  strcpy(novaPessoa.nome, "\0");
  
  do
  {
    printf("1 - Adicionar pessoa\n2 - Imprimir pessoas ordenado pelo CPF\n3 - Pessoas menores que idade informada\n4 - idade do vizinho mais velho\n0 - Finalizar\n");
    scanf("%d", &op);
    switch (op)
    {
    case 1: // LEITURA DE DADOS
      /* Adicionar pessoa */
      setbuf(stdin, NULL);
      printf("Nome: ");
      scanf("%[^\n]s", novaPessoa.nome);
      setbuf(stdin, NULL);
      printf("CPF: ");
      scanf("%[^\n]s", novaPessoa.CPF);
      setbuf(stdin, NULL);
      printf("Idade: ");
      scanf("%d", &novaPessoa.idade);

      // VERIFICA SE O NOME, CPF E IDADE SAO VALIDOS

      // condicoes:
      // nome - O campo nome não pode ser vazio, conter numeros ou conter somente espacos
      // cpf - deve ser somente numeros e ter 11 digitos
      // idade - idade > 0 e < 125

      if(nomeValido(novaPessoa.nome)){
        if (cpfValido(novaPessoa.CPF))
        {
          if (novaPessoa.idade > 0 && novaPessoa.idade < 125)
          {
            // todas as condicoes validas
            // adicionar pessoa
            // inserir a pessoa
            lista = insere(lista, novaPessoa);
            printf("\nPessoa adicionada com sucesso!\n\n");
            
            // ordena alista logo apos cada insercao para manter sempre ordenada
            // ordenar por CPF
            ordenaCPF(lista);
          }else {
            // idade nao bateu com as condicoes
            printf("Idade invalida\n");
          }
          
        }else {
          // cpf nao bateu com as condicoes
          printf("CPF invalido\n");
        }
        
      }else {
        // nome nao bateu com as condicoes
        printf("O campo nome não pode ser vazio, conter numeros ou conter somente espacos!\n");
      }   

      break;
    case 2:
      /* imprimir pessoas ordenado pelo CPF */
      imprimeReverso(lista);
      break;
    case 3:
      /* 2 - Pessoas menores que idade informada */
      // ler idade
      printf("Digite a idade: ");
      scanf("%d", &idade);

      // verifica se a idade eh valida
      if (idade >= 0 && idade < 125)
      {
        // A lista auxiliar recebe todas as pessoas com idade menor que a informada
        // a lista é ordenada pela idade
        listaAuxiliar = pessoasComIdadeMenor(lista, idade);
        
        // verifica se a lista recebeu alguma pessoa
        if (listaAuxiliar)
        {        
          // recebeu
          // ordenar por idade e imprimir a lista
          ordenaPorIdade(listaAuxiliar); // ordenar todas as pessoa da nova lista por idade
          printf("\n");
          imprimeReverso(listaAuxiliar); // imprimir
        }else {
          // lista vazia
          printf("\nNenhuma pessoa com idade menor que a informada\n\n");
        }
      }else {
        // idade digitada inválida
        printf("Idade invalida!\n");
      }
      break;
    case 4:

      /* 3 - idade do vizinho mais velho */
      
      printf("Digite o CPF: ");
      setbuf(stdin, NULL);
      scanf("%[^\n]s", cpf);

      if (cpfValido(cpf))
      {
        /* 
          - itera sobre a lista até encontrar o CPF igual
          - ao encontrar, volta no anterior e verifica a idade dele com o vizinho posterior
          - retorna o vizinho com a maior idade por funcao e retorna por parametro a pessoa do cpf informado
        */
        vizinhoMaisVelho = encontraVizinhoMaisVelho(lista, cpf, &usuario);

        // imprime as informacoes do vizinho mais velho
        printf("\nVizinho mais velho\n");
        printf("CPF: %s\n", vizinhoMaisVelho.CPF);
        printf("Nome: %s\n", vizinhoMaisVelho.nome);
        printf("Idade: %d\n", vizinhoMaisVelho.idade);
        printf("\n");

        // compara a idade do vizinho com a da pessoa do cpf que foi informada pelo usuario
        if(vizinhoMaisVelho.idade > usuario.idade){
          printf("O vizinho %s eh mais velho que %s\n", vizinhoMaisVelho.nome, usuario.nome);
        }else {
          printf("O vizinho %s eh mais novo que %s\n", vizinhoMaisVelho.nome, usuario.nome);
        }
      } else {
        // cpf digitado invalido
        printf("CPF invalido\n");
      }
      break;
    case 0:
      // finalizar
      break;
    default:
      printf("\nOpcao invalida!\nRepita a operacao\n");
      break;
    }
  } while (op != 0);

  lista = libera(lista);
  
  return 0;
}

// ------ Funcoes ------

// inicializa a lista com NULL
ListaD* inicializa(){
  return NULL;
}

// itera pela lista principal e verifica para todas as pessoas dentro da lista,
// quais delas possuem a idade menor que a idade informada
// para aquelas com a idade menor, sao inseridas na lista auxiliar menorQueIdade
// que sera retornada pela funcao
ListaD* pessoasComIdadeMenor(ListaD* l, int idade){
  ListaD* menorQueIdade; // recebe todas as pessoas com idade menor que a informada
  ListaD* p; // lista auxiliar ara iterar na lista principal

  menorQueIdade = inicializa(); // inicializa a lista auxiliar

  // encontrar todas as pessoas com a idade menor que a informada e enviar para
  // a lista menorQueIdade
  for (p = l; p != NULL; p = p->prox)
  {
    if (p->pessoa.idade < idade)
    {
      // inserir o valor na lista menorQueIdade
      menorQueIdade = insere(menorQueIdade, p->pessoa);
    }
  }

  // retorna a lista contendo todas as pessoas com idade menor que informada que existe 
  // dentro da lista principal
  return menorQueIdade;
}

// itera pela lista principal ate encontrar verificando se o cpf da pessoa eh igual
// ao cpf informado pelo usuario
// ao encontrar, retorna com o ponterio ant e encontrar o primeiro vizinho (caso exista)
// em seguida, usa o ponteir ->prox para encontra o proximo vizinho (caso exista)
// compara a idade de ambos e retorn o vizinho mais velho 
Pessoa encontraVizinhoMaisVelho(ListaD* l, char* cpf, Pessoa* usuario){
  ListaD* p;
  Pessoa maisVelho; //struct que guardara o vizinho mais velho

  // encontrar a pessoa;
  // itera pela lista principal
  for (p = l; p != NULL; p = p->prox)
  {
    // compara o cpf informado com o de cada pessoa na lista
    if(strcmp(p->pessoa.CPF, cpf) == 0)
    {
      // encontrou o usuario correto
      // atribui ao pontei usuario (retorno por parametro)
      *usuario = p->pessoa;

      // verificar quantos vizinhos o usuario possui
      // se for o primeiro valor
      if (p == l )
      {
        // so existe um vizinho
        maisVelho = p->prox->pessoa;
      } else if (p->prox == NULL)
      {
        // se for o ultimo da lista
        // so existe um vizinho
        maisVelho = p->ant->pessoa;
      } else if(p->ant->pessoa.idade > p->prox->pessoa.idade){
        // anterior eh mais velho
        maisVelho = p->ant->pessoa;
      } else {
        // proximo eh o mais velho
        maisVelho = p->prox->pessoa;
      }
      return maisVelho;
    }
  }
}

// ordena usando o metodo insertionsort comparando por idade
void ordenaPorIdade(ListaD* l){
  ListaD* p;
  ListaD* pos;
  Pessoa pessoaAux;
  
  // itera por todas as posicoes
  for(p = l->prox; p != NULL; p = p->prox){
    pos = p;
      // itera de um ponto ate o inicio da lista verificando para as posicoes se estao ordenadas
      while (pos != l){
        // verifica se ja esta na ordem correta as idades
        if (pos->pessoa.idade < pos->ant->pessoa.idade){
          // nao esta na ordem correta
          // fazer a troca das pessoas na posicao da lista 
          // (nao na estrutura da lista, apenas nas pessoas dentro de cada posicao)
          pessoaAux = pos->pessoa;
          pos->pessoa = pos->ant->pessoa;
          pos->ant->pessoa = pessoaAux;
        } else {
          // ja esta ordenado daquele ponto para tras
          // atualiza pos para a repetiao finalizar
          pos = l;
        }
      
        // se existir posicoes antes da posicao atual
        // volta uma posicao
        if (pos != l)
        {
          pos = pos->ant;
        }
    }
  }
}

// ordena pelo meto insertionsort com base no CPF 
void ordenaCPF(ListaD* l){
  ListaD* p;
  ListaD* pos;
  Pessoa pessoaAux;
  // itera de um ponto ate o inicio da lista verificando para as posicoes se estao ordenadas
  for(p = l->prox; p != NULL; p = p->prox){
    pos = p;
      while (pos != l){
        // verifica se ja esta na ordem correta os cpf
        if (strcmp(pos->pessoa.CPF, pos->ant->pessoa.CPF) < 0){
          // nao esta na ordem correta
          // fazer a troca das pessoas na posicao da lista 
          // (nao na estrutura da lista, apenas nas pessoas dentro de cada posicao)
          pessoaAux = pos->pessoa;
          pos->pessoa = pos->ant->pessoa;
          pos->ant->pessoa = pessoaAux;
        } else {
          // ja esta ordenado daquele ponto para tras
          // atualiza pos para a repetiao finalizar
          pos = l;
        }
      
        // se existir posicoes antes da posicao atual
        // volta uma posicao
        if (pos != l)
        {
          pos = pos->ant;
        }
    }
  }
}

// inseri uma pessoa na lista
ListaD* insere(ListaD* l, Pessoa pessoa){
  // alocar uma pessoa na lista
  ListaD* novo = alocaNovo(pessoa);
  
  // verifica se a lista esta vazia
  // se estiver vazia, basta inserir
  if (l != NULL)
  {
    // anterior da lista aponta para o novo no da lista 
    l->ant = novo; 
  }

  // novo aponta para o ultimo No alocado 
  novo->prox = l; 
  // retorna para a lista o novo no (fazendo a lista apontar para o novo NO)
  return novo; 
}

// aloca novo No
ListaD* alocaNovo(Pessoa pessoa){
  // aloca dinamicamento um novo No
  ListaD* novo = (ListaD*) malloc(sizeof(ListaD));

  // inicializando a struct vazia e adicionando a pessoa passada por parametro
  novo->pessoa = pessoa;
  
  // inicializa os apontadores para o proximo e anterios
  novo->prox = NULL; 
  novo->ant = NULL;
  return novo; 
}

// imprime do ultimo para o primeiro elemento da lista
void imprimeReverso(ListaD* raiz){
  // lista auxiliar para iterar na lista principal (util para nao mudar o apontamento correto
  // da lista principal
  ListaD* p = NULL; 

  // verifica se a lista nao esta vazia
  if (raiz != NULL)
  {
    // itera pela lista e imprime as informacoes de cada pessoa
    for (p = raiz; p != NULL; p = p->prox)
    {
      printf("CPF: %s\n", p->pessoa.CPF);
      printf("Nome: %s\n", p->pessoa.nome);
      printf("Idade: %d\n", p->pessoa.idade);
      printf("\n");
    }
    printf("\n");
  } else
  {
    printf("Lista Vazia\n");
  }
}

// libera o espaco de memoria alocado dinamicamente
ListaD* libera(ListaD* l){
  // lista auxiliar (usada para liberar os espacos)
  ListaD* p = l;
  // lista auxiliar (usada para n perder o endereco da proxima posicao para liberar)
  ListaD* t = NULL;

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

// verificar se o nome eh valido
int nomeValido(const char* nome){
  int i = 0;
  int stringSoComEspacos = 1;
  
  // nao pode ser vazio
  // verifica se o tamanho de nome eh igual a zero
  if (strlen(nome) == 0)
  {
    // caso sim, nome invalido
    return 0;
  }

  // verificar se a string só possui espacos
  // itera por todas as posicoes e procura uma diferente de espaco (testada pela funcao isspace())
  while (nome[i] != '\0')
  {
    if (!isspace(nome[i]))
    {
      // valor nao eh espaco, atualiza flag
      stringSoComEspacos = 0;
      break;
    }
    i++;  
  }

  // verifica o valor da flag
  if (stringSoComEspacos)
  {
    // caso true, nome so possui espacos
    // nome invalido 
    return 0;
  }

  i = 0;
  
  // itera pela string verificando se existe algum numero
  // nao eh permitido numeros no nome
  while (nome[i] != '\0')
  {
    // nao permitir nome com numeros
    // isdigit() verifica se o caracter eh um numero
    if (isdigit(nome[i]))
    {
      // casos seja, nome invalido
      return 0;
    }
    i++;
  }

  return 1;
  
}

// verifica se o cpf eh valido
int cpfValido(const char* cpf){
  int i = 0;

  // verifica se o tamanho da string cpf eh igual a 11
  if (strlen(cpf) != 11)
  {
    // diferente de 11, cpf invalido
    return 0;
  }

  // verifica se todos os digitos do cpf sao numeros
  while (cpf[i] != '\0')
  {
    // nao permitir cpf com numeros
    if (!isdigit(cpf[i]))
    {
      // existe digitos que nao sao numeros
      // cpf invalido
      return 0;
    }
    i++;
  }

  // tudo certo, cpf valido
  return 1;
  
}
