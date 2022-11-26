#include <stdio.h>
#define MAX 100

int dividir(int *vet, int inicio, int fim) {
  int aux;
  
  // determina o elemento pivo
  int pivo = *(vet + fim);
  
  // inicio da analise
  int i = (inicio - 1);

  for (int j = inicio; j < fim; j++) {
    if (*(vet + j) <= pivo) {
      // elemento da posicao j é menor que o pivo
      // trocar o elemento j com as posicoes iniciais

      i++; 
      
      // troca o elemento da posicao i com o da posicao j
      int aux = *(vet + i);
      *(vet + i) = *(vet + j);
      *(vet + j) = aux;
    }
  }

  // trocando o pivo para a proxima posicao depois de i (ultimo elemento menor que o pivo)
  aux = *(vet + (i + 1));
  *(vet + (i + 1)) = *(vet + fim);
  *(vet + fim) = aux;
  
  // return a ponto de divisao dos vetores
  return (i + 1);
}

void quickSort(int vet[], int inicio, int fim) {
  if (inicio < fim) {
    
    // Encontra o elemento pivo
    // organiza os menores valores que o pivo a esquerda
    // maiores que o pivo ficam a direita
    int pi = dividir(vet, inicio, fim);
    
    // recursiva para a esquerda do pivo
    quickSort(vet, inicio, pi - 1);
    
    // recursiva para a direita do pivo
    quickSort(vet, pi + 1, fim);
  }
}

void imprimeVetor(int vet[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", vet[i]);
  }
  printf("\n");
}

// Verifica se value já existe dentro de vet3
int isRepetido(int value, int *vet3, int indice){
  int i = indice - 1;
  
  // Verifica se value será o primeiro valor de vet3
  if (indice == 0)
  {
    // É o primeiro valor, logo, não é um valor repetido
    return 0;
  } else
  {
    // Não é o primeiro valor
    // iterar sobre todos os valores de vet
    while (i >= 0)
    {
      // Verifica se algum valor de vet3 é igual a value
      if (value == *(vet3 + i))
      {
        // Valor igual
        return 1;
      }
      i--;
    }
  }
  // Não existe valor igual
  return 0;
}

// Faz a união do vet1 e do vet2 no vet3
void unirVetores(int *vet1, int i , int tam1, int *vet2, int j, int tam2,int *vet3, int *k){
  if (i < tam1 && j < tam2)
  {
    /* Ainda existe valores nos meus vetores */
    if (*(vet1 + i) < *(vet2 + j))
    {
      if (!isRepetido(*(vet1 + i), vet3, *k))
      {
        // valor do vetor 1 menor que valor do vetor 2
        // Valor não é repetido
        *(vet3 + *k) = *(vet1 + i);
        *k += 1; 
      }
      i++;
      unirVetores(vet1, i, tam1, vet2, j, tam2, vet3, k);
    } else
    {
      if (!isRepetido(*(vet2 + j), vet3, *k))
      {
        // valor do vetor 1 menor que valor do vetor 2
        // Valor não é repetido
        *(vet3 + *k) = *(vet2 + j);
        *k += 1; 
      }
      j++;
      unirVetores(vet1, i, tam1, vet2, j, tam2, vet3, k);
    }
  }

  // Envio dos valores restantes dos vetores para o vetor 3
  int x;
  // verifica se já foi usado todos os valores do vetor 1
  if (i < tam1)
  {
    // itera sobre os valores restantes
    for (x = i; x < tam1; x++)
    {
      // verifica se o valor restante é repetido
      if (!isRepetido(*(vet1 + i), vet3, *k))
      {
        // Valor não é repetido
        // Adiciona no vetor 3
        *(vet3 + *k) = *(vet1 + i);
        *k += 1; 
      }
      i++;
    }
  }
  
  // verifica se já foi usado todos os valores do vetor 2
  if (j < tam2)
  {
    for (x = j; x < tam2; x++)
    {
      // verifica se o valor restante é repetido
      if (!isRepetido(vet2[j], vet3, *k))
      {
        // Valor não é repetido
        // Adiciona no vetor 3
        *(vet3 + *k) = *(vet2 + j);
        *k += 1; 
      }
      j++;
    }
  }
}

int main(){

  int vet1[MAX], vet2[MAX];
  int n1, n2, i;

  // Leitura do vetor 2
  printf("Tamanho do primeiro vetor: "); 
  scanf("%d", &n1);
  printf("Digite os valores do vetor 01: ");
  for (i = 0; i < n1; i++)
  {
    scanf("%d", &vet1[i]);
  }

  // ordenar o primeiro vetor
  quickSort(vet1, 0, n1 - 1);
  // Imprime o vetor 1 ordenado
  imprimeVetor(vet1, n1);
  printf("\n");

  // Leitura do vetor 2
  printf("Tamanho do segundo vetor: "); 
  scanf("%d", &n2);
  printf("Digite os valores do vetor 02: ");
  for (i = 0; i < n2; i++)
  {
    scanf("%d", &vet2[i]);
  }

  // ordenar o segundo vetor
  quickSort(vet2, 0, n2 - 1);
  // Imprime o vetor 1 ordenado
  imprimeVetor(vet2, n2);
  printf("\n");

  int vet3[n1 + n2];
  int cont = 0;

  unirVetores(vet1, 0, n1, vet2, 0, n2, vet3, &cont);

  // Imprime vetor 3 ordenado
  imprimeVetor(vet3, cont);
  printf("\n");
  return 0;
}
