#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
  O algoritmo consiste em ler do usuario o tamanho da frase,
  a frase e a letra que deseja contar.

  em seguida, a funcao letras_iguais é responsavel por contar
  quantas letras são iguais a passada
*/

int *letras_iguais();

int main(){
  char *frase;
  char letra;
  int tam, tam_vet_int = 0;
  
  // leitura do tamanho da frase
  printf("Digite o tamanho da frase: ");
  scanf("%d", &tam);

  int* vet;
  // leitura da frase
  frase = (char*) malloc(tam * 1);
  printf("Digite a frase: ");
  scanf("%s", frase);
  
  // leitura da letra que será contada
  setbuf(stdin, NULL);
  printf("Qual letra deseja contar: ");
  scanf("%c", &letra);

  vet = letras_iguais(frase, &letra, &tam_vet_int);

  int i;
  for (i = 0; i < tam_vet_int; i++)
  {
    printf("letra %c na posicao %d\n", letra, vet[i]);
  }
  printf("Tamanho do vetor: %d\n", tam_vet_int);
  
}

int *letras_iguais(char* frase, char* letra, int* tam_vet_int){
  int* vet;
  // aloca o vetor que retornará a posicao onde a letra se repete
  vet = (int*) malloc(strlen(frase) * sizeof(int));

  int i;
  // itera sobre a frase verificando quais letras
  // sao iguais a desejada
  for (i = 0; frase[i] != '\0'; i++)
  {
    if (*(frase + i) == *letra)
    {
      // letra igual
      // envia o indice para o vetor e incrementa o contador
      vet[*tam_vet_int] = i;
      *tam_vet_int = *tam_vet_int + 1;
    }
    
  }
  return vet;
}