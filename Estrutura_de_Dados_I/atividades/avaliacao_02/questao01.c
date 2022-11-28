#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
  O algoritmo consiste em gerar um sistema que cadastre, mostre e remova cursos e disciplinas
*/

#define MAX 100 // quantidade maxima de cursos e disciplinas
#define MAX_CHAR_NAME 51 // quantidade maxima de caracteres para os nomes

// struct para armazenar os dados das disciplinas
typedef struct 
{
  int cod_disciplina;
  int cod_curso;
  char nome[MAX_CHAR_NAME];
  int periodo;
  int carga_horaria;
} Disciplina;

// struct para armazenar os dados dos cursos
typedef struct 
{
  int cod_curso;
  char nome[MAX_CHAR_NAME];
  int qtd_periodo;
  int turno;
  int cargaHorariaTotal;
} Curso;

/* FUNCOES - Serao detalhadas em seus escopos */
void menu();
void inicializa_disciplina(int n, Disciplina** tab);
void inicializa_curso(int n, Curso** tab);
void cadastrar_curso(Curso** cursos, int qtde_curso);
void cadastrar_disciplina(Curso** cursos, Disciplina** disciplinas, int qtde_cursos, int qtde_disciplinas);
int mostrarCurso(Curso** cursos, int qtde_cursos, int cod);
void imprime_cursos(Curso** curso, int qtde_cursos); // imprime o codigo e o nome de um curso
void imprime_curso(Curso** curso, int index); // imprime todas as informacoes de um curso
void imprime_disc(Disciplina** disciplinas, int index); // imprime todas as informacoes de uma disciplina
int curso_escolhido(Curso** cursos, int qtde_cursos);
void cursosTurno(Curso** cursos, int qtde_cursos);
void todasDiscCurso(Disciplina** disciplinas, int qtde_disciplinas, int cod);
void todasDiscCursoPeriodo(Disciplina** disciplinas, int qtde_disciplinas, int cod, int cod_periodo);
int temDisc(Disciplina** disciplinas, int qtde_disciplinas, int cod_curso);
int busca_binaria_disciplina(Disciplina** disciplinas, int cod_disciplina, int qtde_disciplinas);
int busca_binaria_curso(Curso** curso, int cod, int qtde_cursos);
void desalocar_curso(Curso** tab, int n);
void desalocar_disciplina(Disciplina** tab, int n);
void insertionSort_curso(Curso** cursos, int qtde_cursos);
void insertionSort_disciplina(Disciplina** disciplinas, int qtde_disciplinas);

int main(){

  Curso *cursos[MAX]; // vetor de struct para armazenar os cursos
  Disciplina *disciplinas[MAX]; // vetor de struct para armazenar as disciplinas

  inicializa_curso(MAX, cursos); // inicializa com NULL o vetor de struct Cursos
  inicializa_disciplina(MAX, disciplinas); // inicializa com NULL o vetor de struct Disciplina

  int qtde_cursos = 0, qtde_disciplinas = 0; // contarao a quantidade de cursos e disciplinas adicionadas
  
  // opcao -> opcao do switch que é lida da entrada padra
  // index -> armazena os indices que sao retornados na funcao de busca
  int opcao = -1, index; 

  // auxiliares para ler os valores que serao buscados nos vetores
  int cod_curso, cod_disciplina, periodo_digitado; 
  int i;

  // struct auxiliar para o processo de remocao de disciplina ou curso
  Disciplina aux;
  Curso aux_curso;

  // repeticao que ficara executando ate que o usuario desejar finalizar o programa
  do
  {
    menu(); // imprime o menu de opcoes
    scanf("%d", &opcao); // leitura da opcao escolhida pelo usuario
    
    switch (opcao)
    {
      case 1:
        /* Adicionar Curso */
        // aloca espaco para um curso e ler os dados do curso, com as devidas restricoes (citadas no escopo da funcao)
        cadastrar_curso(cursos, qtde_cursos);  

        qtde_cursos++; // incrementa a quantidade de cursos adicionados     
        insertionSort_curso(cursos, qtde_cursos); // Ordena pelo metodo insertionSort o vetor de struct cursos
        break;
      case 2:
        /* Adicionar Disciplina */

        // verifica se exite algum curso antes de adicionar uma disciplina
        if (cursos[0] != NULL)
        {
          // primeira posicao não é NULL -> existe pelo menos um curso adicionado
          // aloca memoria para armazenar uma disciplina e ler os cados da disciplina (restricoes descritas no escopo da funcao)
          cadastrar_disciplina(cursos, disciplinas, qtde_cursos, qtde_disciplinas);
          qtde_disciplinas++; // incrementa a quantidade de disciplinas
          insertionSort_disciplina(disciplinas, qtde_disciplinas); // Ordena pelo metodo insertionSort o vetor de struct cursos
        } else
        {
          // primeira posicao é NULL -> não foram adicionados cursos ainda
          printf("\nNão é possivel adicionar disciplinas!\nNão existe cursos cadastrados.\n\n");
        }
        break;
      case 3:
        /* Mostrar um Curso */
        // usa a busca binaria para buscar um curso pelo codigo do curso
        printf("Digite o codigo do curso: ");
        scanf("%d", &cod_curso);
        // verifica se o codigo é valido (maior que 0)
        if (cod_curso >= 0)
        {
          // enviado para a busca binaria o codigo do curso
          // busca_binaria_curso retorna -1 caso n encontre ou o indice se encontrar
          index = busca_binaria_curso(cursos, cod_curso, qtde_cursos);
          if (index != -1)
          {
            // encontrou o curso -> imprime o curso
            imprime_curso(cursos, index);
          } else {
            // nao encontrou o curso
            printf("\nCurso não encontrado\n\n");
          }
        } else
        {
          // codigo digitado nao pe valido
          printf("\nCodigo invalido!\n\n");
        }
        break;
      case 4:
        /* Mostrar uma disciplina */
        // usa a busca binaria para buscar uma disciplina pelo codigo de uma disciplina
        printf("Digite o codigo da disciplina: ");
        scanf("%d", &cod_disciplina);
        // verifica se o codigo é valido (maior que 0)
        if (cod_disciplina < 0)
        {
          printf("Codigo invalido");
        }else
        {
          // enviado para a busca binaria o codigo da disciplina
          // busca_binaria_curso retorna -1 caso n encontre ou o indice se encontrar
          index = busca_binaria_disciplina(disciplinas, cod_disciplina, qtde_disciplinas);
          if (index != -1)
          {
            // encontrou -> imprime a disciplina
            imprime_disc(disciplinas, index);
          }else{
            // disiciplina nao encontrada
            printf("\nDisciplina não encontrado\n\n");
          }
        }
        break;
      case 5:
        /* Mostrar todos os cursos de um turno */
        cursosTurno(cursos, qtde_cursos); 
        break;
      case 6:
        /* Mostrar todos as disciplinas de um curso */
        // apos informado o codigo do curso, é buscado todas as disciplinas que possuem o cogido do curso igual ao informado
        printf("Digite o codigo do curso (nao e permitido valores negativos): ");
        scanf("%d", &cod_curso);
        if (cod_curso >= 0)
        {
          // busca o curso
          index = busca_binaria_curso(cursos, cod_curso, qtde_cursos);
          if(index == -1){
            // nao encontrou o curso
            printf("\nERRO: curso não existe\n\n");
          }else
          {
            // encontrou o curso -> imprimir todas as disciplinas com aquele curso
            todasDiscCurso(disciplinas, qtde_disciplinas, cursos[index]->cod_curso);
          }
        }else
        {
          printf("Valor não permitido");
        }
        break;
      case 7:
        /* Mostrar disciplinas de um periodo */
        // apos informar o curso e o periodo, caso ambos sejam validos,
        // o algoritmo itera por todas a s disciplinas buscando aquelas
        // que pertencem aquele curso e aquele periodo
        printf("Digite o codigo do curso (nao e permitido valores negativos): ");
        scanf("%d", &cod_curso);
        if (cod_curso >= 0)
        {
          // busca o curso
          index = busca_binaria_curso(cursos, cod_curso, qtde_cursos);
          if(index == -1){
            // curso nao encontrado
            printf("\nERRO: curso não existe\n\n");
          }else
          {
            // curso encontrado - buscar o periodo
            printf("Digite o periodo: ");
            scanf("%d", &periodo_digitado);
            if (periodo_digitado > 0 && periodo_digitado <= cursos[index]->qtd_periodo)
            {
              /* periodo_valido -> buscar e imprimir as disciplinas */
              todasDiscCursoPeriodo(disciplinas, qtde_disciplinas, cursos[index]->cod_curso, periodo_digitado);
            } else
            {
              // o curso nao possui aquele periodo
              printf("\nPeriodo invalido!\n\n");
            }
          }
        }else
        {
          printf("Valor não permitido");
        }
        break;
      case 8:
        /* Remover uma disciplina */
        /* Passos para remover uma disciplina:  
        1 - Encontrar a disciplina 
        2 - enviar a disciplina para a ultima posicao 
        (caso n envie, haverá problemas na busca binaria)
        3 - liberar memoria e setar para NULL
        */
        
        // 1 - encontrar disciplina
        printf("Digite o codigo da disciplina: ");
        scanf("%d", &cod_disciplina);
        if (cod_disciplina < 0)
        {
          printf("Codigo invalido");
        }else
        {
          // buscar disicplina na struct
          index = busca_binaria_disciplina(disciplinas, cod_disciplina, qtde_disciplinas);
          if (index != -1)
          {
            // disciplina encontrada
            // 2 - enviar para a ultima posicao
            // itera por todas as posicoes a partir da que desejo remover
            for (i = index; i < qtde_disciplinas; i++)
            {
              // se a proxima posicao for diferente de NULL (ou seja, a frente ainda existe disciplinas)
              if (disciplinas[i + 1] != NULL)
              {
                /* Existe disciplina na proxima posicao */
                // fazer a troca
                aux = *disciplinas[i + 1];
                *disciplinas[i + 1] = *disciplinas[i];
                *disciplinas[i] = aux;
              } else
              {
                // nao existe mais disiciplinas a frente
                // a que desejo remover está na ultima posicao
                break;
              }
            }
            
            // libera a memoria
            free(disciplinas[i]);
            // seta para NULL
            disciplinas[i] = NULL;
            // decrementa a quantidade de disciplinas
            qtde_disciplinas--;
            printf("\nDisciplina removida\n\n");
          }else{
            printf("\nDisciplina não encontrado\n\n");
          }
        }
        break;
      case 9:
        /* Remover um curso */
        /* 
          etapas para a remocao de um curso
          1 - encontrar curso
          2 - verificar se no vetor de disciplinas existe alguma disciplina daquele curso
          3 - enviar curso para a ultima posicao
          4 - liberar curso
         
        */

       // 1 - encontrar curso
        printf("Digite o codigo do curso (nao e permitido valores negativos): ");
        scanf("%d", &cod_curso);
        if (cod_curso > 0)
        {
          // busca curso no vetor
          index = busca_binaria_curso(cursos, cod_curso, qtde_cursos);
          if(index == -1){
            printf("\nERRO: curso não existe\n\n");
          }else
          {
            // codigo existe no vetor
            // 2 - verificar se no vetor de disciplinas existe alguma disciplina daquele curso
            // a funcao tem disciplina itera pelas disciplinas e verica se 
            // alguma tem o cod_curso igual ao do curso que desejo rmeover
            if(!temDisc(disciplinas, qtde_disciplinas, cod_curso)){
              // posso remover o curso
              // 3 - enviar curso para a ultima posicao
              for (i = index; i < qtde_cursos; i++)
              {
                if (cursos[i + 1] != NULL)
                {
                  /* Existe disciplina na proxima posicao */
                  aux_curso = *cursos[i + 1];
                  *cursos[i + 1] = *cursos[i];
                  *cursos[i] = aux_curso;
                } else
                {
                  break;
                }
            }
            // 4 - liberar curso
            free(cursos[i]);
            cursos[i] = NULL;
            qtde_cursos--;
            printf("\nCurso removido\n\n");
            }else {
              printf("\nNão é possivel remover o curso!\nO curso ainda possui disciplinas\n\n");
            }
          }
        }else
        {
          printf("Valor não permitido");
        }
        break;
      case 0: 
        /* Finalizar programa */
        printf("\nPrograma Finalizado!\n\n");
        break;

      default:
        break;
    }
  } while (opcao != 0);  

  // desalocar vetor de cursos e disciplinas
  desalocar_curso(cursos, qtde_cursos);
  desalocar_disciplina(disciplinas, qtde_disciplinas);

  return 0;
}

// Adiciona um curso no vetor de struct curso
void cadastrar_curso(Curso** cursos, int qtde_curso){
  int i, cod_curso;

  // itera até encontra a primeira posicao livre
  for (i = 0; cursos[i] != NULL; i++){}
  
  // aloca memoria para adicionar 1 curso na struct
  cursos[i] = (Curso*) malloc(sizeof(Curso));

  // ler o codigo do curso
  printf("Digite o codigo do curso (nao e permitido valores negativos): ");
  scanf("%d", &cod_curso);
  
  // faz uma busca no vetor, verificando se existe um codigo igual aquele
  // repetira até o usuario digitar um codigo valido (maior ou igual a 0 e que nao seja repetido)
  while (cod_curso < 0 || busca_binaria_curso(cursos, cod_curso, qtde_curso) != -1){
    printf("O codigo do curso invalido ou ja existe!\nDigite novamente: ");
    scanf("%d", &cod_curso);
  }
  cursos[i]->cod_curso = cod_curso;
  
  // leitura dos demais dados
  printf("Nome do curso: ");
  setbuf(stdin, NULL);
  fgets(cursos[i]->nome, MAX_CHAR_NAME, stdin);
  printf("Quantidade de periodos: ");
  scanf("%d", &cursos[i]->qtd_periodo);
  
  printf("Turno:\n1 - manha\n2 - tarde\n3 - noite\n4 - integral\n");
  scanf("%d", &cursos[i]->turno);
  // repetirá até o usuario digitar um turno valido
  while (cursos[i]->turno > 4 || cursos[i]->turno < 1)
  {
    printf("Turno Inválido. Repita a operacao.\n");
    scanf("%d", &cursos[i]->turno);
  }
  printf("Carga Horaria Total: ");
  scanf("%d", &cursos[i]->cargaHorariaTotal);
}

// adiciona as disciplinas no vetor de sctruct disciplinas
void cadastrar_disciplina(Curso** cursos, Disciplina** disciplinas, int qtde_cursos, int qtde_disciplinas){
  int periodo, i, cod_disciplina;

  // itera até encontra a primeira posicao livre
  for (i = 0; disciplinas[i] != NULL ; i++){}
  
  // aloca memoria para adicionar uma disciplina a struct
  disciplinas[i] = (Disciplina*) malloc(sizeof(Disciplina));

  // Leitura de dados para o vetor dinamico disciplinas
  printf("Codigo da disciplina: ");
  scanf("%d", &cod_disciplina);

  // faz uma busca no vetor, verificando se existe um codigo igual aquele
  // repetira até o usuario digitar um codigo valido (maior ou igual a 0 e que nao seja repetido)
  while (busca_binaria_disciplina(disciplinas, cod_disciplina, qtde_disciplinas) != -1){
    printf("O codigo da disciplina ja existe!\nDigite novamente: \n");
    setbuf(stdin, NULL);
    scanf("%d", &cod_disciplina);
  }
  disciplinas[i]->cod_disciplina = cod_disciplina;

  printf("Nome da disciplina: ");
  setbuf(stdin, NULL);
  fgets(disciplinas[i]->nome, MAX_CHAR_NAME, stdin);

  /* A QUE CURSO PERTENCE A DISCIPLINA */ 
  // imprime todos so curso existentes
  imprime_cursos(cursos, qtde_cursos);
  // curso recebe o curso escolhido pelo usuario
  int curso = curso_escolhido(cursos, qtde_cursos);
  disciplinas[i]->cod_curso = cursos[curso]->cod_curso;
  
  // Executa até o usuario escolher um periodo valido para o curso
  do
  {
    printf("Periodo: ");
    scanf("%d", &periodo);
    if (periodo < 1 || periodo > cursos[curso]->qtd_periodo)
    {
      printf("ERRO: periodo não existe\n");
    }
  } while (periodo < 1 || periodo > cursos[curso]->qtd_periodo);
  
  disciplinas[i]->periodo = periodo;

  printf("Carga Horaria: ");
  scanf("%d", &disciplinas[i]->carga_horaria);

  // repetira até que o usuario digite uma carga horaria valida (multiplo de 15)
  while (disciplinas[i]->carga_horaria % 15 != 0){
    printf("\nCarga Horaria invalida!\nO valor deve ser multiplo de 15\n");
    scanf("%d", &disciplinas[i]->carga_horaria);
  } 
}

// imprime todos os cursos de um turno
void cursosTurno(Curso** cursos, int qtde_cursos){
  int i, turno, temCurso = 0;

  // imprime todos os turnos disponiveis
  printf("Turno:\n1 - manha\n2 - tarde\n3 - noite\n4 - integral\n");
  scanf("%d", &turno);
  // repete ate o usuario digitar um turno valido
  while (turno > 4 || turno < 1)
  {
    printf("Turno Inválido. Repita a operacao.\n");
    scanf("%d", &turno);
  }
  
  // turno valido
  // itera por todos os cursos e imprime aqueles que sao iguais ao turno escolhido

  for (i = 0; i < qtde_cursos; i++)
  {
    if (cursos[i]->turno == turno)
    {
      imprime_curso(cursos, i);
      temCurso = 1; // flag para verificar se foi impresso algum curos ou nao
    }
  }

  // caso nao tenha nenhum curso, imprime mensagem
  if (!temCurso)
  {
    printf("\nO turno não possui cursos!\n\n");
  }
}

// imprime o codigo e nome de todos os cursos adicionados
// essa funcao é util no momento de cadastro de disciplina
// imprime ao usuario todos os curso que foram adicionados
void imprime_cursos(Curso** cursos, int qtde_cursos){
  int i;

  printf("\n");
  for (i = 0; i < qtde_cursos; i++)
  {
    printf("%d - %s", cursos[i]->cod_curso, cursos[i]->nome); 
  }
  printf("\n"); 
}

// imprime todas as informacoes do curso
void imprime_curso(Curso** curso, int index){
  printf("\nCodigo: %d\n", curso[index]->cod_curso);
  printf("Nome: %s", curso[index]->nome);
  printf("Quantidade de periodos: %d\n", curso[index]->qtd_periodo);
  printf("Carga Horaria Total: %d\n", curso[index]->cargaHorariaTotal);
  printf("Turno: ");

  // como o turno é INT, faco uum switch para imprimr de acordo com o valor
  switch (curso[index]->turno)
  {
    case 1:
      printf("Manha");
      break;
    case 2:
      printf("Tarde");
      break;
    case 3:
      printf("Noite");
      break;    
    case 4:
      printf("Integral");
      break;    
  }
  printf("\n\n");
}

// imprime todas as informacoes de uma disciplina
void imprime_disc(Disciplina** disciplinas, int index){
  printf("\nCodigo da disciplina: %d\n", disciplinas[index]->cod_disciplina);
  printf("Codigo do curso: %d\n", disciplinas[index]->cod_curso);
  printf("Nome: %s", disciplinas[index]->nome);
  printf("Periodo: %d\n", disciplinas[index]->periodo);
  printf("Carga Horaria: %d\n\n", disciplinas[index]->carga_horaria);
}

// itera sobre os cursos e procura o curso com o codigo enviado
// essa funcao é semelhante a busca binaria, mas é utilizada em uma
// situacao especifica, pois o comportamento da busca binaria nao funciona para
// este caso
int mostrarCurso(Curso** cursos, int qtde_cursos, int cod){
  int i;
  for (i = 0; i < qtde_cursos; i++)
  {
    // verifica se o codigo enviado é igual ao do curso
    if (cursos[i]->cod_curso == cod)
    {
      // curso existe na lista - retorna a posicao dele
      return i;
    }
  }
  // curso nao existe na lista - retorna -1
  return -1;
}

// itera por todas as disciplinas e imprime aquela que possuem o cod_curso igual
// ao informado pelo usuario
void todasDiscCurso(Disciplina** disciplinas, int qtde_disciplinas, int cod){
  int i;
  
  for (i = 0; i < qtde_disciplinas; i++)
  {
    if (disciplinas[i]->cod_curso == cod)
    {
      /* disciplina pertecente ao curso */
      imprime_disc(disciplinas, i);
    }
  }
}

// itera sobre o vetor de disciplinas e verifica se um curso possui disciplinas
// util ao remover um curso, ja que a restricao é que ele nao pode ter disicplinas
// dois retornos
// 1 = possue disciplinas
// 0 = nao possue
int temDisc(Disciplina** disciplinas, int qtde_disciplinas, int cod_curso){
  int i;
  
  for (i = 0; i < qtde_disciplinas; i++)
  {
    if (disciplinas[i]->cod_curso == cod_curso)
    {
      /* disciplina pertecente ao curso */
      return 1;
    }
  }
  return 0;
}

// itera por todas as disciplinas e imprime aquelas que tiverem o codigo e o periodo igual ao informado
void todasDiscCursoPeriodo(Disciplina** disciplinas, int qtde_disciplinas, int cod, int cod_periodo){
  int i;

  for (i = 0; i < qtde_disciplinas; i++)
  {
    if (disciplinas[i]->cod_curso == cod && disciplinas[i]->periodo == cod_periodo)
    {
      /* disciplina pertecente ao curso e ao periodo especificado */
      imprime_disc(disciplinas, i);
    }
  }
}

// inicializa o vetor curso com NULL
void inicializa_curso(int n, Curso** tab){
  int i;
  for(i=0; i<n; i++){
    tab[i] = NULL; // seta para NULL
  }
}

// inicializa o vetor disciplina com NULL
void inicializa_disciplina(int n, Disciplina** tab){
  int i;
  for(i=0; i<n; i++){
    tab[i] = NULL; // seta para NULL
  }
}

// desaloca o vetor curso
void desalocar_curso(Curso** tab, int n){
  int i;
  for (i = 0; i < n; i++)
  {
    if (tab[i] != NULL)
    {
      free(tab[i]); // desaloca
      tab[i] = NULL; // seta para NULL
    }
  }
}

// desaloca o vetor disciplinas
void desalocar_disciplina(Disciplina** tab, int n){
  int i;
  for (i = 0; i < n; i++)
  {
    if (tab[i] != NULL)
    {
      free(tab[i]); // desaloca
      tab[i] = NULL; // seta para NULL
    }
  }
}

// ler o codigo do curso digitado pelo usuario e
// verifica se o curso existe no vetor cursos
int curso_escolhido(Curso** cursos, int qtde_cursos){
  int opcao, cod_curso;

  do
  {
    printf("Digite o codigo do curso: ");
    scanf("%d", &cod_curso);
    // mostrarCurso retorna a posicao do curso, caso encontre
    // retorna -1 caso o curso nao exista no vetor
    opcao = mostrarCurso(cursos, qtde_cursos, cod_curso);
    if(opcao == -1){
      printf("ERRO: curso não existe\n");
    }
  } while (opcao == -1);
  // while executa até o usuario digitar um curso valido

  return opcao;
}

// imprime o menu com as opcoes
void menu(){
  printf("1 - Cadastrar Curso\n");
  printf("2 - Cadastrar Disciplina\n");
  printf("3 - Mostrar um curso\n");
  printf("4 - Mostrar uma disciplina\n");
  printf("5 - Mostrar todos os cursos de um turno\n");
  printf("6 - Mostrar todos as disciplinas de um curso\n");
  printf("7 - Mostrar disciplinas de um periodo\n");
  printf("8 - Remover uma disciplina\n");
  printf("9 - Remover um curso\n");
  printf("0 - Finalizar programa\n");
}

// busca binaria para a struct curso
/* 
  A busca binaria trabalha sob um vetor ordenado
  1 - determinar o meio do vetor
  2 - verifica se o meio é o valor desejado
      caso sim, retorna a posicao
  3 - caso nao, verifica se o valor do meio é maior ou menor que o valor desejado
      caso maior, analisar agora apenas os itens da esquerda do meio
      caso menor, analisar agora apenas os itens da direita do meio
*/
int busca_binaria_curso(Curso** curso, int cod, int qtde_cursos)
{
  int inicio = 0;
  int fim = qtde_cursos;

  while (inicio <= fim) {  /* Condição de parada */
    int i = (inicio + fim) / 2;  /* Calcula o meio do sub-vetor */
    
    if (inicio == qtde_cursos || fim == 0)
    {
      return -1;
    }
    
    if (curso[i]->cod_curso == cod) {  /* valor encontrado */
      return i;
    }
    if (curso[i]->cod_curso < cod)  /* valor está no sub-vetor à direita */
    { 
      inicio = i + 1;  
    } else  /* vector[i] > valor. valor está no sub-vetor à esquerda */
    { 
      fim = i;       
    }
  }
  return -1; /*Não encontrou o valor procurado*/
}

// busca binaria para a struct curso
// (mesma logica explicada na linha 672, mas agora aplicado ao struct disciplina)
int busca_binaria_disciplina(Disciplina** disciplinas, int cod_disciplina, int qtde_disciplinas){
  int inicio = 0;
  int fim = qtde_disciplinas;

  while (inicio < fim) {  /* Condição de parada */
    int i = (inicio + fim) / 2;  /* Calcula o meio do sub-vetor */

    if (inicio == qtde_disciplinas || fim == 0)
    {
      return -1;
    }
    
    if (disciplinas[i]->cod_disciplina == cod_disciplina) {  /* valor encontrado */
      return i;
    }
    if (disciplinas[i]->cod_disciplina < cod_disciplina)  /* valor está no sub-vetor à direita */
    { 
      inicio = i + 1; 
    } else  /* vector[i] > valor. valor está no sub-vetor à esquerda */
    { 
      fim = i;       
    }
  }
  return -1; /*Não encontrou o valor procurado*/
}

/* ------------ INSERCTION SORT -------------- */
// Funcoes para ordenar os meus vetores

/* 
  logica da insertion
  1 - comeca da segunda posicao do vetor
  2 - verifica com as posicoes anteriores se a posicao atual é maior ou menor que a anterior
  3 - caso menor, ele irá retornar o vetor decrementando até encontrar uma posicao onde
  o valor atual seja menor que  o valor da direira dele e maior que o da esquerda dele
  4 - fará o processo até ordenar todos os valores 
 
*/
 
// insertionSort para a struct Curso
void insertionSort_curso(Curso** cursos, int qtde_cursos)
{
  int i, key, j;
  Curso chave;
  for (i = 1; i < qtde_cursos; i++) {
      chave = *cursos[i];
      j = i - 1;

      while (j >= 0 && cursos[j]->cod_curso > chave.cod_curso) {
          *cursos[j + 1] = *cursos[j];
          j = j - 1;
      }
      *cursos[j + 1] = chave;
  }
}

// insertionSort para a struct Disciplina
void insertionSort_disciplina(Disciplina** disciplinas, int qtde_disciplinas)
{
  int i, j;
  Disciplina chave;
  Disciplina aux;
  for (i = 1; i < qtde_disciplinas; i++) {
    
    chave = *disciplinas[i];
    j = i - 1;
    
    while (j >= 0 && disciplinas[j]->cod_disciplina > chave.cod_disciplina) {
        *disciplinas[j + 1] = *disciplinas[j];
        j = j - 1;
    }
    *disciplinas[j + 1] = chave;
  }
}