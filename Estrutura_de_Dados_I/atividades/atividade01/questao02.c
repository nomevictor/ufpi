#include <stdio.h>

/* A logica da funcao consiste em repetir diversas multiplicoes
com uma base ate chegar ao numero informado. 

Caso chegue, a base e o expoente é retornado via referencia.

Caso nao chegue, o expoente retorna pra 1 e a base e incrementada e
o processo recomeca ate a ultima possibilidade, que é a base igual ao 
proprio numero informado */

void fatoraPotencia(int numero, int *base, int *expoente){
  int flag = 1; // flag responsavel por parar a repeticao
  *expoente = 1; // valor inicial do expoente
  *base = 2; // valor inicial da base
  int cont = *base; // variavel que será inicialmente a base e que testa a quantidade de multiplicacoes ate chegar no numero informado

  while (flag)
  {
    if (cont == numero)
    {
      // Significa que eu encontrei a menor base e o expoente correto ou
      // a menor base é o proprio numero e o expoente 1 
      flag = 0;
    } else
    {
      // verifico se meu valor de teste cont ainda é menor que o valor inicial recebido
      if (cont < numero){
        // É menor. Multiplico ele pelo valor da base e incremento meu expoente
        cont *= *base;
        *expoente+=1;
      } else{
        // É maior. retorno o expoente para 1 e incremento minha base
        *expoente = 1;
        *base+=1;
        cont = *base;
      }
    }
  }
  
}

int main(){
  int valor, base, expoente;
  
  // leitura do dados
  printf("Digite um valor: ");
  scanf("%d", &valor);

  // chamada da funcao que efetua o calculo
  fatoraPotencia(valor, &base, &expoente);
  printf("base = %d\nexpoente = %d\n", base, expoente );
  return 0;
}