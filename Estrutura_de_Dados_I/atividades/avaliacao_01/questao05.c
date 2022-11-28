#include <stdio.h>
#include <string.h>
#define MAX 100

// O codigo consiste em iterar pela frase e para cada letra,
// verificar se esta já existe no vetor Struct 'Caracteres'

// Caso não exista, é adicionado
// Caso exista, a quantidade dessa letra é incrementada

// struct para guardar qual o caracter e quantos deste existe
typedef struct
{
  char caracter;
  int qtde_caracter;
}Caracteres;

int contaCaracteres(char *frase, Caracteres *caracteres);
int caracterExiste(char caracter, Caracteres *caracteres, int qtde_caracteres);

int main() {

  char frase[MAX];
  int i, j;

  Caracteres caracteresPalavra[MAX]; // struct para armazenar todos os caracteres da string
  
  // Leitura de dados
  printf("Digite a frase: ");
  scanf("%[^\n]s", frase);

  // Chamada da funcao - o retorno dela é a quantidade de caracteres diferentes na struct
  j = contaCaracteres(frase, caracteresPalavra);

  // Imprimir todos os caracteres da Struct
  for (i = 0; i < j; i++)
  {
    printf("'%c' = %d\n", caracteresPalavra[i].caracter, caracteresPalavra[i].qtde_caracter);
  }

  return 0;
}

// A funcao adiciona ou incrementa na struct Caracteres a quantidade 
// de caracteres que existe em frase
int contaCaracteres(char *frase, Caracteres *caracteres){
  int cont_caracter = 0, i = 0, aux;

  // Itera sobre cada letra da frase
  for (i = 0; i < strlen(frase); i++)
  {
    // verificar se o novo caracter existe na lista de caracteres
    aux = caracterExiste(*(frase + i), caracteres, cont_caracter);
    // Tipos de retorno:
    // Existe a letra - Retorna a posicao dela no vetor Struct
    // Não existe - Retorna -1
    if (aux == -1)
    {
      // Caracter novo
      (caracteres + cont_caracter)->caracter = *(frase + i);
      (caracteres + cont_caracter)->qtde_caracter = 1;
      cont_caracter++;
    } else
    {
      // Caracter existente
      caracteres[aux].qtde_caracter++;
    }
  }

  return cont_caracter;
}

// verifica se caracter já existe na struct Caracteres
int caracterExiste(char caracter, Caracteres *caracteres, int qtde_caracteres){
  int i;
  for (i = 0; i < qtde_caracteres; i++)
  {
    if (caracter == caracteres[i].caracter)
    {
      // O caracter existe na lista e será retornado o indice dele
      return i;
    }
  }
  // O caracter não existe na lista
  return -1;
}