#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHARACTERES 50

char *repete(char *s, int n);

int main() {

  char palavra[MAX_CHARACTERES], *frase;
  int n;

  frase = NULL; // inicializa o ponteiro com NULL

  printf("Digite a palavra: ");
  scanf("%[^\n]", palavra);
  printf("Quatidade de vezes para repetir a palavra: ");
  scanf("%d", &n);

  // frase recebe a frase completa com todas as repeticoes
  frase = repete(palavra, n);

  // a aspas no printf é para visualizar melhor que foi removido
  // o ultimo espaco
  printf("\"%s\"\n", frase);

  // desaloca a frase alocada dinamicamente
  frase = NULL;
  free(frase);

  return 0;
}

// Retorna a frase com palavra repetida n vezes
char *repete(char *s, int n){
  char *frase;
  // Aloca espaco suficiente para a frase
  // (n * strlen(s)) = quantidade de repeticoes * tamanho da palavra
  // + n = Alocar os espaco entres as palavras
  frase = (char*) malloc(((n * strlen(s)) + n)* sizeof(char));
 
  int i, y, aux = 0;

  // For que repete a quantidade de vezes que eu quero copiar char *s
  for (i = 0; i < n; i++)
  {
    // itera sobre a palavra passada por parametro
    for (y = 0; s[y] != '\0'; y++)
    {
      // atribui letra po letra a palavra na frase
      frase[aux] = s[y];
      aux++;
    }
    // adiciona um espaco
    frase[aux] = ' ';
    aux++;
  }
  // remove o ultimo espaco e adiciona o final da string
  frase[aux - 1] = '\0';

  return frase;
}