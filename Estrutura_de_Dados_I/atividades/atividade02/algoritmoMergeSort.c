#include <stdio.h>
#include <stdlib.h>

void intercala(int inicio, int meio, int fim, int v[]){
    int vet_esquerda , vet_direita , auxiliar , *ponteiro;

    // Ponteiro auxiliar para guardar os valores ordenados
    ponteiro = (int *) malloc((fim - inicio) * sizeof(int));
    
    vet_esquerda = inicio; // Inicio do vetor da esquerda
    vet_direita = meio; // Inicio do vetor da direita
    
    auxiliar = 0; // iterador auxiliar para o ponteiro
	
    // Iterar sobre os dois vetores para ordenar (esquerda -> vet_esquerda, direita = vet_direita)
    // e verificar qual valor é menor entre os todos os valores desses vetores e 
    // armazenar na ordem crescente esses valores no vetor auxiliar. 
    while(vet_esquerda < meio && vet_direita < fim){
        if(v[vet_esquerda] <= v[vet_direita]){
            ponteiro[auxiliar] = v[vet_esquerda];
            auxiliar++;
            vet_esquerda++;
        }
        else{
            ponteiro[auxiliar] = v[vet_direita];
            auxiliar++;
            vet_direita++;
        }
    }
    
    // vetor auxiliar recebe todos os valores restantes do vetor da esquerda 
    // (caso exista valores restantes)
    while(vet_esquerda < meio){
        ponteiro[auxiliar] = v[vet_esquerda];
        auxiliar++;
        vet_esquerda++;
    }
    
    // vetor auxiliar recebe todos os valores restantes do vetor da direita 
    // (caso exista valores restantes)
    while(vet_direita < fim){
        ponteiro[auxiliar] = v[vet_direita];
        auxiliar++;
        vet_direita++;
    }
	
    // Vetor principal receber os valores ordenados do vetor auxiliar
    for(vet_esquerda = inicio;vet_esquerda < fim;vet_esquerda++){
        v[vet_esquerda] = ponteiro[vet_esquerda - inicio];
    }
    free(ponteiro); // Liberar espaco de memoria do ponteiro
}

void mergeSort(int inicio, int fim,int vet[]){
    /*inicio= representa a posição inicial do vetor que será ordenado;
    fim = representa até qual posição vamos ordenar o vetor
    vet[] = vetor a ser ordenado*/
    if(inicio < fim - 1){
        int centro = (inicio + fim) / 2;
        //centro = representa a posição central do vetor;
        mergeSort(inicio, centro,vet);
        //Ordenada do início ao centro;
        mergeSort(centro,fim,vet);
        //Ordenada do centro até o fim;
        intercala(inicio,centro,fim,vet);
    }
}

void mergeSortIterativo(int vet[], int tam)
{
   int t_bloco = 1; // quantidade de valores que serão ordenados por vez

   // while responsavel pelas repeticoes onde a quantidade de valores a 
   // cada intercalacao muda (de 2 valores para 4; 4 para 8)
   while (t_bloco < tam) { 
      int inicio = 0; // ponto inicial do vetor para ordenar

      // O while responsavel por intercalar todos os valores do vetor 
      // iniciando a cada dois valores,
      while (inicio + t_bloco < tam) {  
         int fim = inicio + 2*t_bloco; // Ponto final onde será ordenado
         
         if (fim > tam) fim = tam; // garantir que não vai ultrapassar o tamanho do vetor

         intercala(inicio, inicio+t_bloco, fim, vet);
         inicio = inicio + 2*t_bloco;
      }
      t_bloco = 2*t_bloco;// quantidade de valores que serão ordenados duplica 
   }
}

int main(){
    int qnt_num;
    printf("Informe o tamanho do vetor: ");
    scanf("%d",&qnt_num);
    int vetor[qnt_num];
    for(int i = 0; i < qnt_num; i++){
        scanf("%d",&vetor[i]);
    }
 
    mergeSort(0,qnt_num,vetor);

    printf("Resultado mergesort recursivo :");
    for(int i = 0; i < qnt_num; i++){
        printf("%d ",vetor[i]);
    }
    printf("\n");
    
    printf("Informe o tamanho do vetor: ");
    scanf("%d",&qnt_num);
    for(int i = 0; i < qnt_num; i++){
        scanf("%d",&vetor[i]);
    }
    printf("Resultado mergesort iterativo :");
    mergeSortIterativo(vetor,qnt_num);
    for(int i = 0; i < qnt_num; i++){
        printf("%d ",vetor[i]);
    }
    printf("\n");
    return 0;
}
