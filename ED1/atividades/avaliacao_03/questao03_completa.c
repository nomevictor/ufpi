#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 

  O programa eh dividido em duas etapas

  1 - validar a expressao digitada
  2 - transformar a expressao de in-fixa para pos-fixa


  1 ----- Validar a expressao digitada ------

  Para validar, foi criado algumas funcoes que validam partes diferentes:

  parentesesInicioFim - verifica se existe parentes no inicio e fim da expressao
  identifica_formacao - verifica se todos os parenteses que abrem, são fechados
  
  calculo_valido - Valida a expressao com base na quantidade de operadores e expressoes
  Cada operacao de um operador binario leva sempre 3 digitos: o operador e dois numeros;
  Por tanto, o tamanho da pilha, inserindo sempre os operadores e os numeros será sempre
  impar. Calculo valido insere todos os valores e verificar se a pilha eh impar

  isCaraterValido - verifica se a expressao possui apenas caracteres validos
  remove com o strtok todos os caracteres valido exceto os numeros. itera pelos
  valores restantes e se existir algum que não seja um numero, entao foi digitado 
  um caracter invalido

  2 transformar a expressao de in-fixa para pos-fixa

  apos garantir que a expressao eh valida, eh enviada para a funcao de calculo
  Ela itera por cada caracter e para cada caso do switch, eh feito uma operacao
  de empilhamento para os operadores e abre parenteses e operadores
  (continuacao do algoritmo)


*/

#define MAX_CHAR 101

// estruturas

// struct para armazenar apenas um caracter
typedef struct no{
    char caracter;
    struct no *proximo;
}No;

// struct para armazenar uma string (utilizadas nos processos com strtok)
typedef struct no_ch{
    char* caracter;
    struct no_ch *proximo;
}No_ch;



No* pilhaD_inicializa (); // inicializa a pilha com NULL
No_ch* pilhaD_inicializa_string (); // inicializa a pilha de no string com NULL
No* pilhaD_alocaNo(char valor); // aloca espaco de memoria para o No
No* empilhar_char(No *pilha, char valor); // insere na pilha um NO char
No_ch* empilhar_string(No_ch *pilha, char* valor); // insere na pilha um NO string
No* desempilhar_No_char(No **pilha); // desempilha um NO char
char desempilhar_char(No **pilha); // desempilha um NO string
int isNumberDigit(const char* number); // verifita se a string passada possui apenas numeros
int isCaraterValido(char* formula, char* caracterInvalido, char* caracterRemover); 
int forma_par(char f, char d); // forma os pares dos parenteses
int identifica_formacao(char x[]); // verifica se todos os parenteses possuem pares
int parentesesInicioFim(char* formula); // verifica se existe parenteses no inicio e no fim
int calculo_valido(char* formula); // verifica se a quantidade de operadores eh valida
char *infixaParaPosfixa (char *inf); // transforma a expressao para pos fixa

int main(){

  char formula[MAX_CHAR];
  char copia_formula[MAX_CHAR];
  char caractereInvalido;
  int op, expressao = 0;



  do
  {
    printf("1 - Digitar e verificar expressao\n2 - Visualizar expressao no modo pos-fixa\n0 - Finalizar\n");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
      expressao = 1;
      /* Digitar e verificar expressao */
      printf("Digite uma expressao: ");
      setbuf(stdin, NULL);
      scanf("%[^\n]s", formula);


      strcpy(copia_formula, formula);

      // -------VERIFICA SE A FORMULA EH VALIDA--------
  
      // verifica se existe parenteses no inicio e no fim
      if(!parentesesInicioFim(copia_formula)){
        printf("A expressao não possui parenteses no inicio ou no fim\n");
        expressao = 0;
      }

      // verificar se os parenteses abrem e fecham corretamente
      if (identifica_formacao(copia_formula))
      {
        printf("Parênteses faltando\n");
        expressao = 0;
      }

      // verifica se os operadores sao validos
      if (!calculo_valido(copia_formula))
      {
        printf("Quantidade de operadores ou numeros invalida\n");
        expressao = 0;
      }
      
      // verificar se a formula eh composta apenas por numeros, parenteses e caracteres de operacao
      if (!isCaraterValido(copia_formula, &caractereInvalido, "(){}[]+-/* "))
      {
        // formula possue caracteres invalidos
        printf("O caractere %c nao eh permitido na expressao\n", caractereInvalido);
        expressao = 0;
      }
      break;
    case 2:

      // ---------EFETUAR CONVERSAO-----------
      // verifica se a expresao foi considerada valida
      if (expressao)
      {
        char* formulaPosFixa;
        formulaPosFixa = infixaParaPosfixa(formula);
        printf("formula pos-fixa = %s\n", formulaPosFixa);
      } else {
        printf("Voce nao digitou a expressao ou digitou incorretamente\n");
      }

      break;
    default:
      break;
    }
  } while (op != 0);

  return 0;
}


// inicializa a pilha com NULL
No* pilhaD_inicializa (){
  return NULL;
} 

// inicializa a pilha com NULL
No_ch* pilhaD_inicializa_string (){
  return NULL;
}

// aloca o espaco de memoria para um NO
No* pilhaD_alocaNo(char valor){
  No* no = (No*) malloc(sizeof(No));
  no->caracter = valor;
  no->proximo = NULL;
  return no;
}

// adiciona um NO na pilha de caracteres
No* empilhar_char(No *pilha, char valor){
    // aloca o espaco de memoria
    No *novo = malloc(sizeof(No));

    // verifica se foi alocado a memoria
    if(novo){
        // atribui o valor enviado pelo usuario
        novo->caracter = valor;
        // liga os nos para manter o encadeamento
        novo->proximo = pilha;
        return novo;
    }
    else
        printf("Erro ao alocar memoria!\n");
    return NULL;
}

// adiciona um NO na pilha de string
No_ch* empilhar_string(No_ch *pilha, char* valor){
    No_ch *novo = malloc(sizeof(No));

    // verifica se foi alocado a memoria
    if(novo){
        // atribui o valor enviado pelo usuario
        novo->caracter = valor;
        // liga os nos para manter o encadeamento
        novo->proximo = pilha;
        return novo;
    }
    else
        printf("Erro ao alocar memoria!\n");
    return NULL;
}

// remove da pilha de caracteres
No* desempilhar_No_char(No **pilha){
    No *remover = NULL;

    // verifica se a pilha possui valor
    if(*pilha){
        // pegar o valor a remover (ele sera retornado)
        remover = *pilha;
        // faz a pilha apontar para o proximo valor (valor abaixo dele)
        *pilha = remover->proximo;
    }
    return remover;
}

// remove da pilha de caracteres
char desempilhar_char(No **pilha){
    No *remover = NULL;

    // verifica se a pilha possui valor
    if(*pilha){
        // pegar o valor a remover (ele sera retornado)
        remover = *pilha;
        // faz a pilha apontar para o proximo valor (valor abaixo dele)
        *pilha = remover->proximo;
    }
    return remover->caracter;
}

// itera pela string enviada e verifica se ela possue apenas numeros
int isNumberDigit(const char* number){
  int i = 0;
  // itera ate o final da string
  while (number[i] != '\0')
  {
    // verifica se o caracter esta no intervalo de qualquer caracter, exceto os numeros
    // com base no decimal da tabela ASCII
    
    if (*number < 48 || *number > 57)
    {
      // nao esta no intervalo
      return 0;
    }
    i++;
  }
  return 1;
}


int isCaraterValido(char* formula, char* caracterInvalido, char* caracterRemover){
  char *pt;
  // (){}[]+-*/ 
  pt = strtok(formula, caracterRemover);
  while (pt)
  {
    if (!isNumberDigit(pt))
    {
      // minha formula não é valida 
      // possui caracteres invalidos
      *caracterInvalido = *pt;
      return 0;
    }
    pt = strtok(NULL, caracterRemover);
  }
  return 1;
}

// ---------VERIFICAR PARENTESES----------

int forma_par(char f, char d){
    switch(f){
    case ')':
        if(d == '(')
            return 1; // bem formada
        else
            return 0; // mal formada
        break;
    case ']':
        if(d == '[')
            return 1; // bem formada
        else
            return 0; // mal formada
        break;
    case '}':
        if(d == '{')
            return 1; // bem formada
        else
            return 0; // mal formada
        break;
    }
}


int identifica_formacao(char x[]){
    int i = 0;
    No* remover, *pilha = NULL;
  // itera por todos os caracteres
  while(x[i] != '\0'){
    // verifica s eo caracter eh uma abertura de parenteses, cahves ou colchetes
    if(x[i] == '[' || x[i] == '(' || x[i] == '{'){
      // caso sim, empilha em uma pilha de conteudo char
      pilha = empilhar_char(pilha, x[i]);
      //imprimir(pilha);
    }
    //caso seja parentese, colchete ou chave aberta de fechamento
        // desempilha o ultimo valor e verifica se eh possivel fechar os pares de parenteses, colchetes ou chaves
        // caso nao seja possivel, parenstese da expressao invalidos
    else if(x[i] == ']' || x[i] == ')' || x[i] == '}'){
      remover = desempilhar_No_char(&pilha);
      if(remover){
        if(forma_par(x[i], remover->caracter) == 0){
          return 1; // expressao esta mal formada
        }
          free(remover);
      } else{
        return 1; // expressao esta mal formada
      }
    }
    i++;
  }
   // se restar algo na pilha
    // significa que algum parenteses nao tem seu fechamento
  if(pilha){
    return 1;
  }
  else{
    return 0;
  }
}

int parentesesInicioFim(char* formula){
  // verifica se na primeira posicao existe um abre parenteses e se na ultima existe um fecha arenteses
  if (formula[0] == '(' && formula[strlen(formula) - 1] == ')')
  {
    return 1;
  } else{
    return 0;
  }
}

// --------- VERIFICA OS NUMEROS E OPERADORES -------
int calculo_valido(char* formula){
  char *pt;
  int tamanho_pilha = 0;
  No_ch* pilha = pilhaD_inicializa_string();

  // strtok retira da minha expressao (){}[] e espaco em branco, restando os numeros e operadores

  // assim, empilho eles 
  pt = strtok(formula, "(){}[] ");
  while (pt)
  {
    pilha = empilhar_string(pilha, pt);
    pt = strtok(NULL, "(){}[] ");
  }

  // empilhei todos os meu numero e operadores na pilha
  // apos empilhado todos os operadores e numeros
  // itero pela pilha e conto seu tamanho
  while (pilha != NULL)
  {
    tamanho_pilha++;
    pilha = pilha->proximo;
  }
  
  // verifico se o tamanho eh par
  if (tamanho_pilha % 2 == 0)
  {
    // eh par e com base na explicacao inicial
    // a expresao eh invalida
    return 0;
  }
  // nao eh par, expressao valida
  return 1;
}

// efetua a transformacao da expressao de infixa para pos fixa
char *infixaParaPosfixa (char *inf) {
   int n = strlen(inf); // n recebe o tamanho da expressao
   char *posfixa; // a string posfixa recebe a expressao no modo pos fixa
   posfixa = malloc ((n+1) * sizeof (char)); // aloca o espaco suficiente para a expressao pos fixa
   No* pilha = pilhaD_alocaNo(inf[0]); // aloac uma pilha para fazer os empilhamentos e desenpilhamentos dos caracteres

  int j = 0; // j corresponde ao iterador da variavel posfixa que guardara cartere por caracters
  for (int i = 1; inf[i] != '\0'; ++i) { // itera ate o final da expressao
    switch (inf[i]) {
      char x;
      case '(':
      // caso encontre um parenteses aber, empilhar 
        pilha = empilhar_char(pilha, inf[i]);
        break;
      case ')': 
      // para um parenteses fehcado, significa que temos o final de uma expressao
      // portanto, desempilhar tudo que foi empilhado e enviar para posfixa (numeros nao sao empilhados, vao direto para pos fixa)
        x = desempilhar_char(&pilha);
        while (x != '(') { // itera enquanto nao achar o parenteses de abertura da expressao
          posfixa[j++] = x; // envia os operadores para a expressao posfixa
          x = desempilhar_char(&pilha); // desempilhar um valor da pilha
        }
        break; 
      case '+': 
      case '-': 
      // caso encontre um operador, ele desempilhará tudo na pilha até encontrar um parenteses aberto 
        x = desempilhar_char(&pilha); 
        while (x != '(') {
          posfixa[j++] = x;
          x = desempilhar_char(&pilha);
        }
        pilha = empilhar_char(pilha, x); // empilha o ( novamente
        pilha = empilhar_char(pilha, inf[i]); // empilha o operador
        break;
      case '*':
      case '/': 
      x = desempilhar_char(&pilha); 
      // desempilhar enquanto os valores forem diferente dos operadores de maior
      // precedencia e do parentese aberto
      // dessa forma, o + e o - serao inseridos depois dos * e /, mantendo
      // a ordem de precedencia
        while (x != '(' && x != '+' && x != '-') {
          posfixa[j++] = x;
          x = desempilhar_char(&pilha);
        }
        pilha = empilhar_char(pilha, x); // empilar o parenteses abertoo
        pilha = empilhar_char(pilha, inf[i]); // empilhar o operador da iteracao
        break;
      default:  
        posfixa[j++] = inf[i]; //  numeros e espacos sao adicionados diretamento na expressao
    }
  }
   
  posfixa[j] = '\0'; // adicionar o final da string para a expressao
  return posfixa; // retornar a expressao
}




