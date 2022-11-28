#include <stdio.h>
#include <stdlib.h>

/* FUNCTIONS */
float** soma(float** matriz1, float** matriz2, int linha, int coluna);
float** subtracao(float** matriz1, float** matriz2, int linha, int coluna);
float** multiplicacao(float** matriz1, float** matriz2, int linha, int coluna, int coluna_linha);
float** alocar_matriz_real(int linhas, int colunas);
float** desalocar(float** matriz, int coluna);
void ler_dados(float** matriz1, float** matriz2, int l1, int c1, int l2, int c2);
void imprimir_matriz(float** matriz, int linha, int coluna);
void menu();

int main() {

  float** matriz1; 
  float** matriz2;
  float** matriz_resultado;
  int opcao, l1, l2, c1, c2, alocou = 0;

  // inicializar matrizes
  matriz1 = NULL;
  matriz2 = NULL;
  matriz_resultado = NULL;

  printf("Linha e coluna da matriz 1, respectivamente: ");
  scanf("%d %d", &l1, &c1);
  printf("Linha e coluna da matriz 2, respectivamente: ");
  scanf("%d %d", &l2, &c2);

  // Alocar as duas matrizes
  matriz1 = alocar_matriz_real(l1, c1);
  matriz2 = alocar_matriz_real(l2, c2);

  // Ler os valores da matriz1 e matriz2
  ler_dados(matriz1, matriz2, l1, c1, l2, c2);

  // do while executa até que o usuario deseje finalizar (digite 0)
  do
  {
    menu();
    printf("O que deseja fazer: ");
    scanf("%d", &opcao);
    switch (opcao)
    {
      case 1:
        /* Soma */
        // para calcular a soma, as matrizes devem ter o mesmo tamanho
        // verifica se tem o mesmo tamanho
        if (l1 == l2 && c1 == c2)
        {
          // soma() retorna um ponteiro para a matriz soma da matriz1 e matriz2
          matriz_resultado = soma(matriz1, matriz2, l1, c1);
          printf("\n");
          imprimir_matriz(matriz_resultado, l1, c1);
          printf("\n");
          alocou = 1;
        } else
        {
          printf("\nNao e possivel calcular!\nMatrizes com tamanhos diferentes\n\n");
        }
        break;
      case 2:
        /* Subtração */
        // para calcular a subtracao, as matrizes devem ter o mesmo tamanho
        // verifica se tem o mesmo tamnho
        if (l1 == l2 && c1 == c2)
        {
          // subtracao() retorna um ponteiro para a matriz subtracao da matriz1 e matriz2
          matriz_resultado = subtracao(matriz1, matriz2, l1, c1);
          
          printf("\n");
          imprimir_matriz(matriz_resultado, l1, c1);
          printf("\n");
          
          alocou = 1;
        } else{
          printf("\nNao e possivel calcular!\nMatrizes com tamanhos diferentes\n\n");
        }
        break;
      case 3:
        /* Multiplicação */
        // para calcular a multiplicacao, as matriz1 deve a coluna do mesmo tamanho
        // da linha da matriz2
        if (c1 == l2)
        {
          /* possivel multiplicar */
          matriz_resultado = multiplicacao(matriz1, matriz2, l1, c2, c1);
          alocou = 1;

          printf("\n");
          imprimir_matriz(matriz_resultado, l1, c2);
          printf("\n");

        } else{
          // nao é possivel calcular
          printf("\nNao e possivel multiplicar.\nO numero de colunas da matriz 1 e diferente do numero de linhas da matriz 2\n\n");
        }
        break;
      case 0:
        printf("\n");
        printf("Programa finalizado!");
        printf("\n");
        break;

      default:
        printf("\nOpção inválida\nRepita a operacao!\n\n");
        break;
    }
    // Ao passa pelo case, a matriz resutado pode ou nao ser alocado
    // a flag alocou garante que o algoritmo so tente desalocar
    // a matriz_resultado se ela tiver sido alocado anteriormente
    // a cada repeticao, ela é desalocada para ser reutilizada
    if (alocou)
    {
      // foi alocada anteriormente
      // desalocar
      matriz_resultado = desalocar(matriz_resultado, c2);
      alocou = 0;
    }
    
  } while (opcao != 0);

  // Desaloca a matriz1 e matriz2
  matriz1 = desalocar(matriz1, c1);
  matriz2 = desalocar(matriz2, c2);

  return 0;
}

void menu(){
  printf("1 - Soma de matrizes\n");
  printf("2 - Subtração de matrizes\n");
  printf("3 - Multiplicação de matrizes\n");
  printf("0 - Finalizar\n");
}

float** alocar_matriz_real(int linhas, int colunas){
  float** matriz;

  // Alocacao das linhas (primeira dimensao da matriz)
  matriz = (float**) malloc(linhas * sizeof(float*));
  if (matriz == NULL)
  {
    printf("Memoria insuficiente!\n");
    return NULL;
  }

  // Alocacao das colunas (segunda dimensao da matriz)
  int i, y;
  for (i = 0; i < linhas; i++)
  {
    matriz[i] = (float*) malloc(colunas * sizeof(float)); 
    if (matriz[i] == NULL)
    {
      // alocacao deu erro
      // desalocar todas as posicoes alocadas até aqui
      printf("Memoria insuficiente!\n");
      for (y = i - 1; y >= 0; y--)
      {
        free(matriz[i]);
      }
      free(matriz);
      return NULL;
    }
  }
  return matriz;
}

void ler_dados(float** matriz1, float** matriz2, int l1, int c1, int l2, int c2){
  int i, j;

  // Ler dados da matriz 1
  for (i = 0; i < l1; i++)
  {
    for (j = 0; j < c1; j++)
    {
      printf("Valor matriz 1 [%d][%d]: ", i, j);
      scanf("%f", &matriz1[i][j]);
    }
  }

  printf("\n");

  // Ler dados da matriz
  for (i = 0; i < l2; i++)
  {
    for (j = 0; j < c2; j++)
    {
      printf("Valor matriz 2 [%d][%d]: ", i, j);
      scanf("%f", &matriz2[i][j]);
    }
  }
}

float** soma(float** matriz1, float** matriz2, int linha, int coluna){
  float** matriz_resultante;
  int i,j;
  // aloca a matriz resultante
  matriz_resultante = alocar_matriz_real(linha, coluna);

  // itera sobre cada posicao das matrizes e atribui a soma do valor da matriz1
  // da matriz2 a matriz_resultante
  for (i = 0; i < linha; i++)
  {
    for (j = 0; j < coluna; j++)
    {
      matriz_resultante[i][j] = matriz1[i][j] + matriz2[i][j];
    }
  }
  return matriz_resultante;
}

float** subtracao(float** matriz1, float** matriz2, int linha, int coluna){
  float** matriz_resultante;
  int i,j;
  // aloca a matriz resultante
  matriz_resultante = alocar_matriz_real(linha, coluna);

  // itera sobre cada posicao das matrizes e atribui a subtracao do valor da matriz1
  // e da matriz2 a matriz_resultante
  for (i = 0; i < linha; i++)
  {
    for (j = 0; j < coluna; j++)
    {
      matriz_resultante[i][j] = matriz1[i][j] - matriz2[i][j];
    }
  }
  return matriz_resultante;
}

float** multiplicacao(float** matriz1, float** matriz2, int linha, int coluna, int coluna_linha){
  float** matriz_resultante;
  int i, j, k;
  // aloca a matriz resultante
  matriz_resultante = alocar_matriz_real(linha, coluna);

  // Zerar matriz
  for (i = 0; i < linha; i++)
  {
    for (j = 0; j < coluna; j++)
    {
      matriz_resultante[i][j] = 0;
    }
  }

  // Calculo dos valores da matriz
  for (i = 0; i < linha; i++)
  {
    for (j = 0; j < coluna; j++)
    {
      for (k = 0; k < coluna_linha; k++)
      {
        matriz_resultante[i][j] += matriz1[i][k] * matriz2[k][j];
      }
    }
  }
  
  return matriz_resultante;
}

float** desalocar(float** matriz, int coluna){
  int i, y;

  if (coluna < 1)
  {
    printf("** Erro: Parametro invalido **\n");
    return matriz;
  }
  
  for (i = coluna - 1; i >= 0; i--)
  {
    free(matriz[i]);
  }
  free(matriz);
  return NULL;
}

void imprimir_matriz(float** matriz, int linha, int coluna){
  int i, j;
  printf("Matriz resultante\n");
  for (i = 0; i < linha; i++)
  {
    for (j = 0; j < coluna; j++)
    {
      printf("%.1f ",matriz[i][j]);
    }
    printf("\n");
  }
}