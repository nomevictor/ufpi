#include <stdio.h>
#define MAX 100
#define qtde_palavras 2

// O algoritmo ler duas strings, e verifica letra por letra 
// se a mesma é vogal ou não. Caso seja, é enviando para a string3

/* FUNCTIONS */

// itera sobre todas as palavras verificando se existe vogais e\ou letras maiusculas
int vogaisEMaiusculo(char palavras[qtde_palavras][MAX], int *maiusculas);

// Verifica se a letra é uma vogal. Retorna 1 para vogal e 0 quando não é vogal
int isVogal(char letra);


int main() {
  // vetor de strings onde ficam todas as palavras
  char palavras[qtde_palavras][MAX]; 

  // vetor que guarda para cada palavra a quantidade de maiusculas nelas
  int qtde_maiusculas[qtde_palavras]; 
  
  int i, vogais;

  // zerar vetor
  for (i = 0; i < qtde_palavras; i++)
  {
    qtde_maiusculas[i] = 0;
  }

  // Leitura das palavras
  for ( i = 0; i < qtde_palavras; i++)
  {
    printf("Digite a %dª String: ", i + 1);
    setbuf(stdin, NULL);
    scanf("%[^\n]s", palavras[i]);
  }

  vogais = vogaisEMaiusculo(palavras, qtde_maiusculas);

  printf("\n");
  for (i = 0; i < qtde_palavras; i++)
  {
    printf("Maiusculas - %d\n", qtde_maiusculas[i]);
  }
    printf("Vogais totais - %d\n", vogais);

  return 0;
}


int vogaisEMaiusculo(char palavras[qtde_palavras][MAX], int *maiusculas){
  int i, j = 0, vogais = 0;

  // itera sobre todas as palavras
  for (i = 0; i < qtde_palavras; i++)
  {
    // itera até o fim da palavra
    while(palavras[i][j] != '\0'){

      // verifica se a letra é maiuscula
      if (palavras[i][j] >= 65 && palavras[i][j] <= 90)
      {
        /* contem letra maiuscula - incrementa a quantidade de maiusculas */
        *(maiusculas + i) += 1;
      }

      // Verifica se a letra é vogal
      if (isVogal(palavras[i][j]))
      {
        vogais += 1;
      }
      j++;
    }
    j = 0;
  }
  return vogais;
}

int isVogal(char letra){
  char vogais[] = "aeiouAEIOU"; 
  int i, j;
  
  for (i = 0; i < 10; i++)
  {
    // Verifica se a letra passada por parametro é uma das vogais dentro
    // do vetor vogais
    if(letra == vogais[i]){
      return 1;
    }
  }
  return 0;
}