#include <stdio.h>

// O algoritmo itera sobre as duas strings e verifica 
// para cada letra, se é vogal e envia para s3, caso seja vogal 

#define MAX 100
#define qtde_palavras 2


/* FUNCTIONS */
void vogais(const char s1[MAX], const char s2[MAX], char *s3);
int isVogal(const char letra);

int main(){

  char s1[MAX], s2[MAX], s3[MAX];
  int i;

  // Leitura de dados
  printf("Digite a string 1: ");
  scanf("%[^\n]s", s1);
  setbuf(stdin, NULL);
  printf("Digite a string 2: ");
  scanf("%[^\n]s", s2);

  vogais(s1, s2, s3);

  printf("%s\n", s3);

  return 0;
}

// Itera sobre s1 e s2 e verifica se existe vogais.
// Caso sim, envia para a string s3 
void vogais(const char s1[MAX], const char s2[MAX], char *s3){
  int cont = 0, contPtr = 0;

  // itera sobre as palavras até chegar ao fim de uma delas
  // verifica se tem vogais
  // envia vogais para s3
  while (s1[cont] != '\0' && s2[cont] != '\0')
  {
    if (isVogal(s1[cont]))
    {
      *(s3 + contPtr) = s1[cont];
      contPtr++;
    }

    if (isVogal(s2[cont]))
    {
      *(s3 + contPtr) = s2[cont];
      contPtr++;
    }
    
    cont++;
  }

  // verifica nas letras restantes de s1 se existe vogais e envia para s3
  while (s1[cont] != '\0')
  {
    if (isVogal(s1[cont]))
    {
      *(s3 + contPtr) = s1[cont];
      contPtr++;
    }
    cont++;
  }

  // verifica nas letras restantes de s2 se existe vogais e envia para s3
  while (s2[cont] != '\0')
  {
    if (isVogal(s2[cont]))
    {
      *(s3 + contPtr) = s2[cont];
      contPtr++;
    }
    cont++;
  }
  
}

// Verifica se letra é uma vogal 
int isVogal(const char letra){
  char vogais[] = "aeiouAEIOU"; 
  int i, j;
  
  for (i = 0; i < 10; i++)
  {
    if(letra == vogais[i]){
      return 1;
    }
  }
  return 0;
}