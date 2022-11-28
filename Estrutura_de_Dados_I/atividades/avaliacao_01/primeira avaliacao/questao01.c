#include <stdio.h>

void soma(int k, int *somatorio);

int main() {
  int k, somatorio = 0;

  // leitura dos dados
  printf("Digite o valor: ");
  scanf("%d", &k);

  soma(k, &somatorio);

  printf("\nSoma de todos os números inteiros entre %d e 0: \n%d\n", k ,somatorio);
  return 0;
}

// A funcao se chama recursivamente enquanto o valor de k
// for maior que zero e a cada chamada, o valor de K é 
// decrementado e o somatorio é salvo em um ponteiro
void soma(int k, int *somatorio){
  if(k > 0){
    *somatorio += k;
    soma(k - 1, somatorio);
  }
}