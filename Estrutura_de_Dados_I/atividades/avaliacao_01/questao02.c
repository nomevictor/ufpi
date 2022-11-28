#include <stdio.h>

void somaIntervalo(int a, int b, int *somatorio);

int main(){
  // declaracao das variaveis
  int a, b, aux, somatorio = 0;

  // leitura dos dados
  printf("Digite os valores de A e B: ");
  scanf("%d %d", &a, &b);

  // garantir que o valor de A seja menor que o valor de B
  if (a > b)
  {
    aux = b;
    b = a;
    a = aux;
  }

  // chamada da funcao que soma os numeros do intervalo
  somaIntervalo(a, b, &somatorio); 

  printf("Somatório dos valores entre %d e %d (não incluindo %d e %d) = %d\n",a, b, a, b, somatorio);

  return 0;
}

// Guarda em somatório a soma de todos os valores entre a e b (não incluindo eles)
void somaIntervalo(int a, int b, int *somatorio){
  if (a < b - 1)
  {
    a += 1;
    somaIntervalo(a, b, somatorio);
    // recursao sem cauda - a soma acontece no retorno de cada recursao
    *somatorio += a;
  }
}