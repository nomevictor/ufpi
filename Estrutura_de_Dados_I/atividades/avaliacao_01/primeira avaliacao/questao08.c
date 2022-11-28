#include <stdio.h>

void primo(int m, int *p1, int *p2);
int isPrimo(int primo);

int main() {
  int p1, p2, m;

  // Leitura de dados
  printf("Digite o valor de m: ");
  scanf("%d", &m);

  if (m > 2)
  {
    // Caso m > 2, existe valores de p1 e p2
    primo(m, &p1, &p2);
    printf("P1 = %d\n", p1);
    printf("M = %d\n", m);
    printf("P2 = %d\n", p2);
  } else if (m == 2)
  {
    // Caso m == 2, não existe valor de p1
    primo(m, &p1, &p2);
    printf("P1 = Não existe\n");
    printf("M = %d\n", m);
    printf("P2 = %d\n", p2);
  } else
  {
    // Caso m == 2, não existe valor de p1 e p2 = 2
    printf("P1 = Não existe\n");
    printf("M = %d\n", m);
    printf("P2 = 2\n");
  }
  return 0;
}

// Encontra o maior primo menor que m e armazena em p1
// Encontra o menor primo maior que m e armazena em p2
void primo(int m, int *p1, int *p2){
  *p1 = m - 1, *p2 = m + 1;
  
  int inicio, primo;

  // maior numero primo menor que m
  
  // itera sobre os valores menores que m, decrementando p1
  // testa para cada valor de p1 se p1 é primo
  // Finaliza a repeticao quando p1 for primo
  while (*p1 > 1)
  {
    primo = isPrimo(*p1);
    if (primo)
    {
      // É primo
      break;
    }
    *p1 = *p1 - 1;
  }

  // itera sobre os valores maiores que m, incrementando p2
  // testa para cada valor de p2 se p2 é primo
  // Finaliza a repeticao quando p2 for primo
  while (1)
  {
    primo = isPrimo(*p2);
    if (primo)
    {
      // É primo
      break;
    }
    *p2 = *p2 + 1;
  }
}

// Verifica se o numero é primo
// Retorna 1 quando o parametro for um numero primo e 
// retorna 0 quando não for primo.
int isPrimo(int primo){
  int i;

  for (i = 2; i < primo; i++)
  {
    if (primo % i == 0)
    {
      return 0;
    }
  }
  return 1;
}