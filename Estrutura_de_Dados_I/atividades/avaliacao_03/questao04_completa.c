#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


/* 
    Para solucionar esse problema, usamos duas structs que serão nos das pilhas

    Seus dados sao diferentes, pois para o processo de validacao da expressao
    digitada, usamos uma pilha char e para a solucao, usamos uma pilha float
    para ir guardando os resultados

*/


// struct No float usada na pilha para calcula a expressao pos fixa
typedef struct no{
    float valor;
    struct no *proximo;
}No;

// struct No char usada na pilha para validar a expressao pos fixa antes de tentar
// calcular
typedef struct no_ch{
    char caracter;
    struct no_ch *proximo;
}No_ch;


// funcoes utilizadas
No* empilhar(No *pilha, float num); // empilhar No de conteudo float na pilha
No* desempilhar(No **pilha); // desempilhar No de conteudo float na pilha
No_ch* empilhar_char(No_ch *pilha, char valor); // empilhar No de conteudo char na pilha
No_ch* desempilhar_char(No_ch **pilha); // desempilhar No de conteudo char na pilha
float operacao(float a, float b, char x); // funcao que executa o calculo dos operadores di expressao pos fixa
int forma_par(char f, char d); // Verificam se os parenteses formam pares (funcao auxiliar) 
int identifica_formacao(char x[]); // Verificam se os parenteses formam pares (funcao principal)

int verifica_posFixa(char x[]); // verifica se os operadores e numeros dentro da expressao estao corretor (sao validos)
float resolver_expressao(char x[]); // funcao que resolve a expressao posfixa

int main(){
    char exp[50]; // variavel que recebe a expressao da entrada padrao
    int expressao = 1; // flag que guarda a informacao da expressao ser valida ou nao 

    // leitura da expressao
    printf("Digite a expressao: ");
    setbuf(stdin, NULL);
    scanf("%[^\n]s", exp);
    
    // VERIFICACAO DA EXPRESSAO

    // verifica se os parenteses se completam (abre e fecha)
    if(identifica_formacao(exp)){
        // mal formada
        expressao = 0;
        printf("expressao mal formada");
    }


    // verifica se a expressao eh pos fixa (se todos os valores e operadores estao corretos)
    if (!verifica_posFixa(exp))
    {
        // expressao posfixa incorreta
        expressao = 0;
    }
    

    // se a expressao for valida -> executar o calculo
    if(expressao) {
        // expressao valida
        printf("\nExpressao valida\n\n");
        printf("Resultado de %s: ", exp);
        printf("%.2f\n", resolver_expressao(exp));
    } else {
        // expressao nao eh valida
        printf("A expressao digitada nao eh valida\n");
    }

    
    return 0;
}

// iterar e adicionar numero. A cada operador remover dois numeros, se possivel
// caso não seja possivel, não eh valida

// OBS: ao desempilhar, sempre verificar se tem como desempilhar mais
// usar o contador de valor inicial dois para desempilhar

// ----- logica da funcao ------
// para uma expressao pos fixa, note que cada operacao envolve dois numeros e um
// operado, respectivamente, nesta ordem ( 2  2  +).

// Portanto, se usarmo uma pilha para armazenar os numeros, sempre que encontrarmos
// um operador, a pilha deve possuir pelo menos 2 valores numericos

// caso nao possua os valores, a formula nao eh valida

// caso, possua, eh feito o calculo e empilhado o valor resultante (1 unico valor na pilha)

// portanto, para saber se eh valida, preciso garantir os seguintes pontos:


// 1 - ao encontra um operador, deve ser possivel remover da pilha dois valores
// 2 - ao final do calculo, dentro da pilha so deve existi o resultado final (pilha com tamanho 1)
// caso exista mais valores, significa que nao foi digitado todos os operadores da expressao e
// portanto, nao foi executado os calculos

// para efetuar a validacao, nao eh necessario guardar na pilha, de fato, os valores, 
// basta desempilhar e empilhar um valor

int verifica_posFixa(char x[]){
    No_ch* pilha = NULL;
    char num[20];
    int i = 0, y, cont = 0;

    // itero pela expressao carter por caracter
    while (x[i] != '\0')
    {
        // verifico se aquele caracter eh um operador
        switch (x[i])
        {
        case '+':
        case '-':
        case '/':
        case '*':
            // eh um operador - tentar desempilhar dois numeros da pilha
            cont = 2; // flag que conta se os dois numeros foram desempilhados
            while (cont > 0)
            {
                // verifica se ainda existe numero para desempilhar
                if (pilha != NULL){
                    // existe -> desempilha
                    desempilhar_char(&pilha);
                }else
                {
                    // nao existe
                    // nao foi possivel desempilhar os dois numeros
                    // expressao invalida
                    return 0;
                }
                cont--;
            }
            // empilhar um valor simbolico que represente o resultado do calculo
            // feito pelo desempilhamento
            pilha = empilhar_char(pilha, '1');
            break;
        default:
            // nao eh um caracter
            // pode ser ( ), espaco em branco ou numeros
            // verifica se eh numero
            if (isdigit(x[i]))
            {
                // caso seja numero, preciso iterar por todos os proximos digitos
                // ate que eu encontre uma posicao que nao eh um numero
                // (dessa forma, consigo pegar todos os caracteres daquele numero com muitas casas)
                y = i;
                // itero ate o valor da posicao nao ser um numero
                while (isdigit(x[y]) && x[y] != '\0')
                {
                    y++;
                }
                y--;
                // passo para o meu iterador principal (i) a posicao em que o numero de
                // muitas casas termina
                i = y;
                // empilhar um valor simboloco ao numero expressao
                pilha = empilhar_char(pilha, '1');
            }
            break;
        }
        i++;
    }

    // contar o tamanho da pilha
    cont = 0;
    while (pilha != NULL)
    {
        cont++;
        pilha = pilha->proximo;
    }

    // verificar se o tamanho da pilha equivale a 1 
    // se for diferente, significa que faltou valores na expressao
    if (cont != 1)
    {
        // faltou valores
        // expressao invalida
        return 0;
    }
    
    return 1;
}

// aloca um no de conteudo float atribui aos ponteiro novo->valor, o valor desse no
// e para novo->prox, a ultimo No adicionado (o valor que a pilha aponta)
// retorna para a pilha o novo valor (agora a pilha aponta para novo) 
No* empilhar(No *pilha, float num){
    No *novo = malloc(sizeof(No));

    // verifica se foi alocado
    if(novo){
        // alocou corretamente
        novo->valor = num;
        novo->proximo = pilha;
        return novo;
    }
    else // erro ao alocar
        printf("Erro ao alocar memoria!\n");
    return NULL;
}

// desempilhar no de conteudo float
// cria um no auxilia para poder libera a memoria depois de "desconectar" ele da pilha
// faz a pilha apontar para proximo no 
// libera a memoria do no que deseja remover
No* desempilhar(No **pilha){
    No *remover = NULL;

    if(*pilha){
        remover = *pilha;
        *pilha = remover->proximo;
        free(remover);
    }
    else
        printf("Pilha vazia\n");
    return remover;
}

// aloca um no de conteudo char e atribui aos ponteiro novo->valor, o valor desse no
// e para novo->prox, a ultimo No adicionado (o valor que a pilha aponta)
// retorna para a pilha o novo valor (agora a pilha aponta para novo)
No_ch* empilhar_char(No_ch *pilha, char valor){
    No_ch *novo = malloc(sizeof(No_ch));

    if(novo){
        novo->caracter = valor;
        novo->proximo = pilha;
        return novo;
    }
    else
        printf("Erro ao alocar memoria!\n");
    return NULL;
}

// desempilhar no de conteudo char
// cria um no auxilia para poder libera a memoria depois de "desconectar" ele da pilha
// faz a pilha apontar para proximo no 
// libera a memoria do no que deseja remover
No_ch* desempilhar_char(No_ch **pilha){
    No_ch *remover = NULL;

    if(*pilha){
        remover = *pilha;
        *pilha = remover->proximo;
        free(remover);
    }
    else
        printf("Pilha vazia\n");
    return remover;
}

// recebe doi numeros e um operados char
// compara o parametro com outro operador char
// ao encontrar o operador correto, efetua o calculo com aquele operador
float operacao(float a, float b, char x){
    switch(x){
    case '+':
        return a + b;
        break;
    case '-':
        return a - b;
        break;
    case '/':
        return a / b;
        break;
    case '*':
        return a * b;
        break;
    default:
        return 0.0;
    }
}


float resolver_expressao(char x[]){
    char num_char[60];
    int cont_num_char = 0;
    float num;
    No *n1, *n2, *pilha = NULL;
    int i = 0, y = 0;

    // itera pela expressao
    while (x[i] != '\0')
    {
        // verifica se o valor eh um operador, (), espaco em branco ou numero
        switch (x[i])
        {
        case '+':
        case '-':
        case '/':
        case '*':
            // eh um operador
            // desmepilhar os dois numeros da pilha
            // efetuar o calculo na funcao operacao
            // o retorno da funao operacao eh empilhado novamente
            n1 = desempilhar(&pilha);
            n2 = desempilhar(&pilha);
            num = operacao(n2->valor, n1->valor, x[i]);
            pilha = empilhar(pilha, num);
            free(n1); // libera os Nos usado para guardar o desempilhamento
            free(n2);
            break;
        default:
        // nao eh um operador
            // vetifica se eh um numero
            if (isdigit(x[i]))
            {
                // eh um numero
                // percorre pela expressao enquanto os digitos forem numericos
                // (encontrar o final de um numero com muitos digitos)
                y = i;
                while (isdigit(x[y]) && x[y] != '\0')
                {
                    num_char[cont_num_char++] = x[y];
                    y++;
                }
                y--;
                // enviar para o iterador principal (i) a posicao em que numero com muitos digitos
                // termina 
                i = y;
                num_char[cont_num_char] = '\0'; // atribuir o final da string para o numero

                // tranformar a strign em float
                num = strtol(num_char, NULL, 10);
                
                cont_num_char = 0;

                // empilhar o valor float
                pilha = empilhar(pilha, num);
            }
            break;
        }
        i++;
    }
    // desmepilha o unico valor restante na pilha (o resultado do calculo)
    n1 = desempilhar(&pilha);
    num = n1->valor; // atribui o valor do No (resultado do calculo) a variavel float
    free(n1); // libera a memoria do no
    
    return num; // retorna o resultado do calculo
}

// verifica se os parenteses formam pares
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

// essa funcao verifica se todo parenteses, colchete ou chave aberto tem seu fechamento
int identifica_formacao(char x[]){
    int i = 0;
    No_ch *remover, *pilha = NULL;

    // itera pela expressao
    while(x[i] != '\0'){
        // verifica se o caracter da repeticao eh um parentese, colchete ou chave aberta
        if(x[i] == '[' || x[i] == '(' || x[i] == '{'){
            // caso sim, empilha em uma pilha de conteudo char
            pilha = empilhar_char(pilha, x[i]);
            //imprimir(pilha);
        }
        //caso seja parentese, colchete ou chave aberta de fechamento
        // desempilha o ultimo valor e verifica se eh possivel fechar os pares de parenteses, colchetes ou chaves
        // caso nao seja possivel, parenstese da expressao invalidos
        else if(x[i] == ']' || x[i] == ')' || x[i] == '}'){
            remover = desempilhar_char(&pilha);
            if(remover){
                if(forma_par(x[i], remover->caracter) == 0){
                    return 1; // expressao esta mal formada
                }
                free(remover);
            }
            else{
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