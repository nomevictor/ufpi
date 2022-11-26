#include <stdio.h>
#define MAX 101

void trocaLetra(char *frase);

int main(){

  char frase[MAX]; // string para armazenar a frase

  // Leitura de dados
  printf("digite uma frase: ");
  scanf("%[^\n]s", frase); 


  trocaLetra(frase);
  printf("%s\n", frase);

  return 0;
}

// A funcao trocaLetra itera sobre cada letra da frase e caso
// seja uma das vogais, é trocada pela outra especificada na questao

// troca as vogais da String passada por parametro
// a -> u | e -> o | i -> u | o -> a | u -> e
void trocaLetra(char *frase){
  int i;
  for (i = 0; *(frase + i) != '\0'; i++)
  {
    // switch para cada caso das vogais
    switch(*(frase + i))
    {
      case 'a':
        *(frase + i) = 'u';
      break;

      case 'e':
        *(frase + i) = 'o';
      break;
      
      case 'i':
        *(frase + i) = 'u';
      break;

      case 'o':
        *(frase + i) = 'a';
      break;

      case 'u':
        *(frase + i) = 'e';
      break;
    }
  }
}