#include <stdio.h>
#include <stdlib.h>

/* 
  A logica consiste em ler as notas e verificar se são de fato numeros. Em seguida,
  é somado na variavel soma e depois divido pela quantidade de notas, sendo atribuido
  a variavel.

  Apos isso, é verificado o valor da media:
  Caso maior ou igual a 7, aprovado.
  Caso menor que 7, reprovado.

  Para ambos os caso, é impresso a situação e a media

*/

// Constantes
#define qtde_notas 3 // Quantidade de notas que serão lidas
#define tam_nota 10 // A quantidade de caracteres que tem cada nota

int main() {
  char buffer[tam_nota];
  float notas[qtde_notas], soma = 0;
  
  // Criacao do ponteiro float e alocacao de memoria para ele
  float *media = (float *) malloc(sizeof(float)); 
  
  int i;
  for (i = 0; i < qtde_notas; i++)
  {
    printf("Nota 0%d: ", i + 1);
    fgets(buffer, sizeof(buffer), stdin); // Leitura da entrada e armazenada como string na variavel buffer

    /*
    Verifico se dentro da string buffer existe um valor
    que pode ser convertido me float (um número).

    Caso sim, ele é enviado para nota[i] e a função sscanf
    retorna a quantidade de valores que conseguiu preencher
    (no caso, apenas 1).

    Caso, não consiga, significa que não foi digitado numeros,
    entao a entrada é invalida e retorna para o usuario digitar novemente
    */

    if ((sscanf(buffer, "%f", &notas[i]) < 1)) {
      // Valor invalido. Imprime na tela do usuario a mensagem 
      // e decrementa o iterador para o usuario poder digitar novamente 
      fputs("Valor inválido!\n", stdout);
      i--;
    }
    else {
      // valor valido, calcula a media da nota
      soma += notas[i];
    }
  }

  // calculando a media das notas
  *media = soma / qtde_notas;

  // Verifica se a nota e maior ou igual a 7 para determinar aprovado ou reprovado
  if (*media >= 7)
  {
    // Nota maior ou igual a 7
    printf("O aluno esta aprovado.\nmedia: %f\n", *media);
  } else {
    // Nota menor que 7
    printf("O aluno esta reprovado.\nmedia: %f\n", *media);
  }
  return 0;
}