#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CHAR_CODE 10
#define MAX_CHAR_WORD 50

// struct para armazenar os dados dos livros
typedef struct
{
  char codigo[MAX_CHAR_CODE];
  char titulo[MAX_CHAR_WORD];
  char autor[MAX_CHAR_WORD];
  char editora[MAX_CHAR_WORD];
  int anoEdicao;
  int numExemplares;
}Livro;

/* FUNCOES */
void inicializa (int n, Livro** v);
int insereLivro(int i, Livro** v);
int alocar(int i, Livro** livro);
void imprime(Livro* livro);
void mostraLivroEditora(int qtde_Livros, Livro** livros, char* editora);
void mostraLivroAutor(int qtde_Livros, Livro** livros, char* autor);
int removeLivro(int qtde_Livros, Livro** livros, char* livro);
void desaloca(int qtde_livros, Livro** livros);

int main(){

  int qtde_livros, op, indiceLivros = 0, situacao;
  char editora[MAX_CHAR_WORD], autor[MAX_CHAR_WORD], livro[MAX_CHAR_WORD];

  // usuario informa a quantidade maxima de livros que serão ordenados
  printf("Digite o limite máximo do conjunto de livro: ");
  scanf("%d", &qtde_livros);

  // criar um vetor de struct para armazenar todos os livros
  Livro *livros[qtde_livros];

  // inicializa o vetor com NULL
  inicializa(qtde_livros, livros);

  // O menu repetira até o usuario desejar finalizar
  do
  {
    // imprime o menu e pede ao usuario que escolha uma opcao valida
    printf("1 - Inserir livro\n2 - Mostrar livros da editora\n3 - Mostrar livros de autor\n4 - Remover livro\n0 - Finalizar\n");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
      /* Inserir livro */
      // chama a funcao insereLivro que adicionará um livro no vetor de struct
      // a funcao retorna tipos de erros, caso ocorra
      situacao = insereLivro(qtde_livros, livros);
      if (situacao == -1)
      {
        printf("\nERRO: Memoria insuficiente\n\n");
      } else if (situacao == -2)
      {
        printf("\nERRO: Limite de livros atingido\n\n");
      }   
      break;
    case 2:
      /* Mostrar livros da editora */
      // ler o nome da editora
      printf("Nome da editora: ");
      setbuf(stdin, NULL);
      scanf("%[^\n]s", editora);
      // funcao responsavel por mostrar todos os livros de uma editora
      mostraLivroEditora(qtde_livros, livros, editora);
      break;
    case 3:
      /* Mostrar livros de autor */
      // ler o nome de um autor
      printf("Nome do autor: ");
      setbuf(stdin, NULL);
      scanf("%[^\n]s", autor);
      // funcao responsavel por mostrar todos os livros de um autor
      mostraLivroAutor(qtde_livros, livros, autor);
      break;
    case 4:
      /* Remover livro */
      // ler o livro que deseja ser removido
      printf("Nome do livro: ");
      setbuf(stdin, NULL);
      scanf("%[^\n]s", livro);

      // funcao remove livro busca o livro e libera a memoria onde ele estava
      // alocado
      // a funcao remove o resultado da remocao
      if (!removeLivro(qtde_livros, livros, livro))
      {
        // livro removido
        printf("\nLivro removido com sucesso\n\n");
      } else
      {
        // livro nao encontrado
        printf("\nLivro não encontrado\n\n");
      }
      break;
    case 0:
      // finalizar programa
      op = 0;
        break;
    default:
        printf("\nOpcao invalida!\nRepita a operacao.\n\n");
      break;
    }
  } while (op != 0);

  // desalocar o vetor de livros
  desaloca(qtde_livros, livros);
  
  return 0;
}

int insereLivro(int qtde_livros, Livro** livro){
  int i;
  // Alocar espaco para armazenar um livro
  // alocar retorna
  i = alocar(qtde_livros, livro);

  // A funcao alocar tem dois possiveis retornos
  // -1 - nao foi alocado
  // -2 - atingiu o limites de livros alocados
  if (i == -1) return -1;
  else if (i == -2) return -2;
  
  // ler os dados do livro
  printf("Codigo do livro: ");
  setbuf(stdin, NULL);
  scanf("%[^\n]s", livro[i]->codigo);
  
  printf("Titulo do livro: ");
  setbuf(stdin, NULL);
  scanf("%[^\n]s", livro[i]->titulo);

  printf("Autor: ");
  setbuf(stdin, NULL);
  scanf("%[^\n]s", livro[i]->autor);

  printf("Editora: ");
  setbuf(stdin, NULL);
  scanf("%[^\n]s", livro[i]->editora);
  printf("Ano de edicao: ");
  // tratar para aceitar apenas numeros
  scanf("%d", &livro[i]->anoEdicao);
  printf("Numero de exemplares: ");
  scanf("%d", &livro[i]->numExemplares);

  return 0;
}

// itera sobre todos os livros e verifica se o autor de algum deles
// é igual ao autor informado
void mostraLivroAutor(int qtde_Livros, Livro** livros, char* autor){
  int i, existe = 0;
  // itera por todos os livros
  for (i = 0; i < qtde_Livros; i++)
  {
    // verifica se aquela posicao tem um livro alocado
    if (livros[i] != NULL)
    {
      // compara o nome do autor do livro com o autor informado
      if (strcmp(livros[i]->autor, autor) == 0)
      {
        // auto igual ao informado, imprime o livro
        imprime(livros[i]);
        existe = 1;
      }
    }
  }

  // flag para verifica se foi adiocionados livros daquele autor
  if (!existe)
  {
    printf("\nNão foi adicionado livros desse autor\n\n");
  }
}

// itera sobre todos os livros e verifica se a editora de algum deles
// é igual a editora informada
void mostraLivroEditora(int qtde_Livros, Livro** livros, char* editora){
  int i, existe = 0;
  // itera sobre todos os livros
  for (i = 0; i < qtde_Livros; i++)
  {
    // verifica se a posicao está alocada com um livro
    if (livros[i] != NULL)
    {
      // compara a editora do livro com a editora informada
      if (strcmp(livros[i]->editora, editora) == 0)
      {
        // editora informa e do livro iguais
        // imprime o livro
        imprime(livros[i]);
        existe = 1;
      }
    }
  }
  // flag que verifica se houve algum livro daquela editora adicionado
  if (!existe)
  {
    printf("\nNão foi adicionado livros dessa editora\n\n");
  }
}

int removeLivro(int qtde_Livros, Livro** livros, char* livro){
  int i;

  for (i = 0; i < qtde_Livros; i++)
  {
    if (strcmp(livros[i]->titulo, livro) == 0)
    {
      free(livros[i]);
      livros[i] = NULL;
      return 0;
    }
  }
  return 1;
}

// inicializa todas as posicoes do vetor como NULL
void inicializa (int n, Livro** livro){
  int i;
  for (i = 0; i < n; i++){
  	livro[i] = NULL;
  }                 
}

// aloca uma posicao do vetor para receber as informacoes do livro
int alocar(int qtde_max_livros, Livro** livro){
  int i;

  // itera sobre o vetor de livro
  for (i = 0; i < qtde_max_livros; i++)
  {
    // encontra a primeira posicao vazia (NULL)
    if (livro[i] == NULL)
    {
      // livre para alocar
      // aloca memoria
      livro[i] = (Livro*) malloc(sizeof(Livro));
      
      // verifica se foi realmente alocada
      if (livro[i] == NULL)
      {
        // nao foi alocado
        return -1; 
      } else {
        // foi alocada, retorna a posicao que foi alocada
        return i;
      }
    }  
  }
  // Todos os espacos do vetor ja estao ocupados
  return -2;
}

// imprime todas as informacoes do livro envaido por parametro
void imprime(Livro* livro){
  printf("\nCodigo: %s\n", livro->codigo);
  printf("Titulo: %s\n", livro->titulo);
  printf("Autor: %s\n", livro->autor);
  printf("Editora: %s\n", livro->editora);
  printf("Ano de edicao: %d\n", livro->anoEdicao);
  printf("Numero exemplares: %d\n\n", livro->numExemplares);
}

// desaloca e seta como NULL a memoria alocada anteriormente
void desaloca(int qtde_livros, Livro** livros){
  int i;
  for (i = 0; i < qtde_livros; i++)
  {
    free(livros[i]);
    livros[i] = NULL;
  }
}