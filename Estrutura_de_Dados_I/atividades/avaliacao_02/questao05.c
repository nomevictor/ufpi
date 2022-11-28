#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ler_aposta(int *aposta, int n);
void sorteia_valores(int *sorteio, int n);
int sorteaNumero(int min, int max);
int* compara_aposta(int *aposta, int *sorteio, int *qtdacertos, int na, int
ns);

int main() {
  int qtde_num, qtdacertos = 0;
  int* aposta;
  int* sorteado;
  int* acertos;
  
  srand( (unsigned) time(NULL) );
  
  // repetirá até o usuario digitar um valor de aposta valido
  // (a quantida de numeros que deseja apostar deve ser entre 1 e 20)
  do
  {
    printf("Quantidade de numeros que deseja apostar (entre 1 e 20): ");
    scanf("%d", &qtde_num);
  } while (qtde_num < 1 || qtde_num > 20);

  // Aloca o vetor para armazenar a aposta e para os numeros que serao sorteados
  aposta = (int*) malloc(qtde_num * sizeof(int));
  sorteado = (int*) malloc(20 * sizeof(int));

  // ler pela entrada padrao todos os numeros apostados pelo usuario
  ler_aposta(aposta, qtde_num);

  // Perguntar se o vetor sorteado é fixo em 20 numeros ou varia
  sorteia_valores(sorteado, 20);

  acertos = compara_aposta(aposta, sorteado, &qtdacertos, qtde_num, 20);

  int i;
  printf("Quantidade de acertos: %d\n", qtdacertos);
  printf("Acertou os numeros:\n");
  for (i = 0; i < qtdacertos; i++)
  {
    printf("%d\n", acertos[i]);
  }
  
  return 0;
}

// itera spbre a quantidade de numeros que serao apostados (n) e
// ler todos os numeros apostados, garantindo que o numero será
// entre 0 e 100
void ler_aposta(int *aposta, int n){
  int i, num;

  // repetirá ate ler todos os numeros que o usuario deseja apostar
  for (i = 0; i < n; i++)
  {
    do
    {
      printf("%d - Escolha um numero entre 0 e 100: ", i + 1);
      scanf("%d", &num); // ler o numero apostado
      // verifica se o numero é valido ou n
      if (num < 0 || num > 100)
      {
        printf("Numero invalido!\nRepita a operacao.\n");
      }
      // repetira até o usuario digitar um valor valido
    } while (num < 0 || num > 100);
    
    // numero valido, atribui no vetor aposta
    aposta[i] = num;
  }
}

// sorteia n numeros aleatoriamente entre 0 e 100
void sorteia_valores(int *sorteio, int n){
  int i;
  for (i = 0; i < n; i++)
  {
    sorteio[i] = sorteaNumero(0, 100); 
    printf("%d ", sorteio[i]);
  }
  printf("\n");
}

// compara todos os numeros apostados com todos os numeros sorteados
// e incremente qtdeacertos sempre que um valor for acertado e
// adiciona o valor acertado no vetor acertos[] que será retornado pela
// funcao
int* compara_aposta(int *aposta, int *sorteio, int *qtdacertos, int na, int
ns){
  int* acertos;
  int i, y;
  // Alocacao dinamica com maximo de acertos possiveis
  acertos = (int*) malloc(na * sizeof(int));

  // itera por todos os numeros apostados
  for (i = 0; i < na; i++)
  {
    // itera por todos os numeros sorteados
    for (y = 0; y < ns; y++)
    {
      // verifica se o numero sorteado é igual ao apostado
      if (aposta[i] == sorteio[y])
      { 
        // incrementa qtdacertos
        // adiciona o numero acertado no vetor 
        acertos[*qtdacertos] = aposta[i];
        *qtdacertos = *qtdacertos + 1; 
      }
    }
  }

  // realocando o vetor para diminuir o tamanho dele e economizar memoria
  acertos = (int*) realloc(acertos, *qtdacertos * sizeof(int));
  
  return acertos;
}

// sorteia um numero entre o min e o max informador por parametro
int sorteaNumero(int min, int max){
  return rand() % max + min;
}