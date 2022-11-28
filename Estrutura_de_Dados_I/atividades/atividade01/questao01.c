#include <stdio.h>
#include <stdlib.h>

/* 
  A logica de solucao consiste em calcular a media dos valores e em seguida,
  para cada valor, calcula a diferenca de valor entre a media e o valor do vetor.

  Para cada caso a partir do caso inicial (a primeira posicao), é verificado se 
  a diferenca do valor é menor que a diferenca do valor anterior.

  caso nao, passa para a proxima repetição.

  caso sim, entao é atribuido a i a posicao desse valor e atribuido a diferenca a
  nova menor diferenca. Dessa forma, serao testados todos os valores do vetor.

  finalizado os testes, a media é retornado via retorno da funcao e a posicao do
  valor mais proximo, retornado por referencia pelo ponterio *i
*/

double media(double vet[], int n, int *i){
  double media = 0;
  double diferenca;

  /* Calculo da media */
  for (int i = 0; i < n; i++)
  {
    media += vet[i];
  }
  media = media/n;

  diferenca = abs(vet[0] - media); // Aplicando diferenca do primeiro valor */
  
  *i = 0; // incializando tambem o indice da menor diferenca com a primeira posicao

  double diferencaFor; // variavel para guardar a diferenca dos valores a serem testados

  /* Verificando se a diferenca é menor nos outros valores do vetor */
  for (int y = 1; y < n; y++) {
    diferencaFor = abs(vet[y] - media); // Calculado a diferenca entre o valor do vetor e a media
    if (diferenca > diferencaFor)
    {
      // caso a nova diferenca seja menor que a anterior, é atribuido a posicao a i
      // e a nova diferenca a variavel diferenca
      *i = y;
      diferenca = diferencaFor;
    }
  }
  return media;
}


int main(){
  int i, n, y;

  // leitura do tamanho do vetor
  printf("Digite o tamanho do vetor: ");
  scanf("%d", &n);

  double vet[n], media_final;

  // Leitura dos valores do vetor
  printf("Digite os elementos do vetor: \n");
  for (y = 0; y < n; y++)
  {
    scanf("%lf", &vet[y]);
  }

  media_final = media(vet, n, &i); // Chamada da funcao media

  printf("Media = %f\n", media_final);
  printf("indice = %d\n", i);

  return 0;
}