#include <stdio.h>
#include <stdlib.h>

/* 
  Na questão 4, foram criados as structs Curso e Disciplina
  para amazenar informações sobre os cursos e disciplina existentes

  É lido primeiramente todos os cursos que serão adicionados e em seguida
  as disciplinas

  No processo de leitura das disciplinas, é exibido os cursos existentes e o
  usuario so pode adicionar essa disciplina se ela pertencer a algum daqueles
  cursos

  O mesmo vale para periodo: só é possivel adicionar uma disciplina a um periodo
  se este periodo existe no curso 
  
  (impossivel adicionar no 9 periodo se o curos só possui 8 periodos)
*/

#define MAX 100

// struct para armazenar os dados das disciplinas
typedef struct 
{
  int cod_disciplina;
  int cod_curso;
  char nome[51];
  int periodo;
  int carga_horaria;
} Disciplina;

// struct para armazenar os dados dos cursos
typedef struct 
{
  int cod_curso;
  char nome[51];
  int qtd_periodo;
  int qtd_disciplinas;

  // um ponteiro para a struct disciplina para armazenar 
  // as disciplinas pertencentes a aquele curso
  Disciplina** disciplinas; 
  int indice_disciplina;
} Curso;

void inicializa_disciplina(int n, Disciplina** tab);
void inicializa_curso(int n, Curso** tab);
void adiciona_curso(Curso** cursos, int* qtde_cursos);
void adiciona_disciplina(Curso** cursos, Disciplina** disciplinas, int* qtde_cursos, int* qtde_disciplinas);
void imprime_cursos(Curso** curso, int* qtde_cursos);
int procura_curso(Curso** curso, int *qtde_cursos, int cod);
char* curso_mais_periodos(Curso** cursos, int* qtde_cursos);
int qtd_disc_periodo(Curso** cursos, int op, int periodo);
void desalocar_disciplina(Disciplina** tab, int n);
void desalocar_curso(Curso** tab, int n);
int qtde_disc_curso(Curso** cursos, int* qtde_cursos, int* indice_curso);
int curso_escolhido();

int main(){

  Curso *cursos[MAX];
  Disciplina *disciplinas[MAX];

  // inicializa os vetores com NULL

  int qtde_cursos = 0, qtde_disciplinas = 0, quantidade_disc_curso, q_cursos, q_disciplinas;
  int op, periodo, disc_periodo;
  char *nome_curso;

  printf("Informe a quantidade de cursos que serão inseridos: ");
  scanf("%d", &q_cursos);

  inicializa_curso(q_cursos, cursos);
  inicializa_disciplina(q_cursos, disciplinas);

  int i;
  // Adiciona todos os curso no vetor de struct
  for (i = 0; i < q_cursos; i++)
  {
    printf("\nCurso %d\n", i+1);
    adiciona_curso(cursos, &qtde_cursos);
    qtde_cursos++;
  }

  if (q_cursos > 0)
  {
    printf("\n-----ADICIONAR DISCIPLINAS-----\n\n");

  
    printf("Informe a quantidade de disciplina que serão inseridas: ");
    scanf("%d", &q_disciplinas);

    // adiciona todas as disciplinas no vetor de disciplinas 
    // (todas as disciplinas de todos os cursos)
    for (i = 0; i < q_disciplinas; i++)
    {
      printf("\nDisciplina %d\n", i+1);
      adiciona_disciplina(cursos, disciplinas, &qtde_cursos, &qtde_disciplinas);
      qtde_disciplinas++;
    }

    printf("\n-----NOME DO CURSO COM MAIOR QUANTIDADE DE PERIODOS-----\n\n");

    // Busca o nome do curso com maior quantidade de periodos
    nome_curso = curso_mais_periodos(cursos, &qtde_cursos);
    printf("\n");
    printf("Curso: %s", nome_curso);
    printf("\n");

    printf("\n-----QUANTIDADE DE DISCIPLINAS DE UM CURSO-----\n\n");

    // Retorna a quantidade de disciplinas de um curso
    quantidade_disc_curso = qtde_disc_curso(cursos, &qtde_cursos, &op);
    printf("\nCurso: %s", cursos[op]->nome);
    printf("Quantidade de disciplinas adicionadas: %d\n", quantidade_disc_curso);
    printf("Quantidade de disciplinas totais: %d\n\n", cursos[op]->qtd_disciplinas);

    printf("\n-----QUANTIDADE DE DISCIPLINAS DE UM PERIODO DE UM CURSO-----\n\n");
    
    // imprime todos os cursos existentes no vetor de struct
    imprime_cursos(cursos, &qtde_cursos);

    // Ler o codigo do curso digitado pelo usuario e verifica se o curso existe
    // na lista 
    // retorna -1 caso não existe
    // retorna o indice do curso na struct caso exista 
    op = curso_escolhido(cursos, &qtde_cursos);
    
    // Repete até o usuario digitar um periodo valido para o curso escolhido
    do
    {
      printf("Qual periodo deseja saber: ");
      scanf("%d", &periodo);
      if (periodo < 0 || periodo > cursos[op]->qtd_periodo)
      {
        printf("ERRO: periodo não existe\n");
      }
    } while (periodo < 0 || periodo > cursos[op]->qtd_periodo);
    
    // busca a quantidade de disciplinas de um periodo do curso escolhido
    disc_periodo = qtd_disc_periodo(cursos, op, periodo);

    printf("\n");
    printf("Curso: %s", cursos[op]->nome);
    printf("Periodo: %d\n", periodo);
    printf("Quantidade de disciplinas: %d\n\n", disc_periodo);

    // Desaloca os vetores
    desalocar_curso(cursos, qtde_cursos);
    desalocar_disciplina(disciplinas, qtde_disciplinas);
  }  

  return 0;
}

// itera sobre todos os cursos e retorna o nome daquele que tiver mais periodos
char* curso_mais_periodos(Curso** cursos, int* qtde_cursos){
  int i, mais_periodos;

  // inicialmente, é considerado o curso da posicao 0 como aquele com mais
  // periodos, já que nenhum outro foi analisado ainda
  mais_periodos = 0; 

  for (i = 0; i < *qtde_cursos; i++)
  {
    // verifica se o curso da iteracao tem mais periodos que o ultimo curso 
    // determinado com mais periodos
    if (cursos[i]->qtd_periodo > cursos[mais_periodos]->qtd_periodo)
    {
      // sim, atualiza o indice do curso que possue mais periodos
      mais_periodos = i;
    }
  }
  // retorna o nome do curdo com mais periodos
  return cursos[mais_periodos]->nome;
}

// retorna por parametro a quantidade de disciplinas de um periodo de um curso
int qtd_disc_periodo(Curso** cursos, int op, int periodo){
  int n = 0, i;

  // itera sobre todas as disciplinas de um curso 
  for (i = 0; i < cursos[op]->indice_disciplina; i++)
  {
    // verifica se o periodo daquela disciplina é igual ao periodo escolhido
    if (cursos[op]->disciplinas[i]->periodo == periodo)
    {
      n++;
    }
  }
  return n;
}

// Adiciona um curso no vetor de struct curso
void adiciona_curso(Curso** cursos, int* qtde_cursos){
  // aloca memoria para adicionar 1 curso na struct
  cursos[*qtde_cursos] = (Curso*) malloc(sizeof(Curso));
  cursos[*qtde_cursos]->indice_disciplina = 0; // zerando o indice de curso para incrementos futuros

  printf("Codigo do curso: ");
  scanf("%d", &cursos[*qtde_cursos]->cod_curso);
  printf("Nome do curso: ");
  setbuf(stdin, NULL);
  fgets(cursos[*qtde_cursos]->nome, 50, stdin);
  printf("Quantidade de disciplinas: ");
  scanf("%d", &cursos[*qtde_cursos]->qtd_disciplinas);
  printf("Quantidade de periodos: ");
  scanf("%d", &cursos[*qtde_cursos]->qtd_periodo);

  // aloca no ponteiro disciplinas dentro da struct espaco para apontar para 
  // todas as disciplinas do curso 
  cursos[*qtde_cursos]->disciplinas = (Disciplina**) malloc(cursos[*qtde_cursos]->qtd_disciplinas * sizeof(Disciplina*));

}

// adiciona as disciplinas no vetor de sctruct disciplinas
void adiciona_disciplina(Curso** cursos, Disciplina** disciplinas, int* qtde_cursos, int* qtde_disciplinas){
  int periodo;
  // aloca memoria para adicionar uma disciplina a struct
  disciplinas[*qtde_disciplinas] = (Disciplina*) malloc(sizeof(Disciplina));

  // Leitura de dados para o vetor dinamico disciplinas
  printf("Codigo da disciplina: ");
  scanf("%d", &disciplinas[*qtde_disciplinas]->cod_disciplina);
  printf("Nome da disciplina: ");
  setbuf(stdin, NULL);
  fgets(disciplinas[*qtde_disciplinas]->nome, 50, stdin);

  /* A QUE CURSO PERTENCE A DISCIPLINA */ 
  // imprime todos so curso existentes
  imprime_cursos(cursos, qtde_cursos);
  // curso recebe o curso escolhido pelo usuario
  int curso = curso_escolhido(cursos, qtde_cursos);
  
  // Executa até o usuario escolher um periodo valido para o curso
  do
  {
    printf("Periodo: ");
    scanf("%d", &periodo);
    if (periodo < 0 || periodo > cursos[curso]->qtd_periodo)
    {
      printf("ERRO: periodo não existe\n");
    }
  } while (periodo < 0 || periodo > cursos[curso]->qtd_periodo);
  
  disciplinas[*qtde_disciplinas]->periodo = periodo;

  printf("Carga Horaria: ");
  scanf("%d", &disciplinas[*qtde_disciplinas]->carga_horaria);
  
  // Pegar a quantidade de disciplinas já adicionadas no curso
  int indice = cursos[curso]->indice_disciplina;
  // Atribuir a disciplina dentro do curso
  cursos[curso]->disciplinas[indice] = disciplinas[*qtde_disciplinas];
  cursos[curso]->indice_disciplina++;
}

// imprime o codigo e nome de todos os cursos adicionados
void imprime_cursos(Curso** cursos, int* qtde_cursos){
  int i;

  printf("\n");
  for (i = 0; i < *qtde_cursos; i++)
  {
    printf("%d - %s", cursos[i]->cod_curso, cursos[i]->nome); 
  }
  printf("\n");
  
}

// itera sobre os cursos e procura o curso com o codigo enviado
int procura_curso(Curso** cursos, int *qtde_cursos, int cod){
  int i;
  for (i = 0; i < *qtde_cursos; i++)
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

// inicializa o vetor curso com NULL
void inicializa_curso(int n, Curso** tab){
  int i;
  for(i=0; i<n; i++){
    tab[i] = NULL;
  }
}

// inicializa o vetor disciplina com NULL
void inicializa_disciplina(int n, Disciplina** tab){
  int i;
  for(i=0; i<n; i++){
    tab[i] = NULL;
  }
}

// desaloca o vetor curso
void desalocar_curso(Curso** tab, int n){
  int i;
  for (i = 0; i < n; i++)
  {
    tab[i] = NULL;
    free(tab[i]);
  }
}

// desaloca o vetor disciplinas
void desalocar_disciplina(Disciplina** tab, int n){
  int i;
  for (i = 0; i < n; i++)
  {
    tab[i] = NULL;
    free(tab[i]);
  }
}

// devolve pela funcao a quantidade de disciplina de um curso
int qtde_disc_curso(Curso** cursos, int* qtde_cursos, int* indice_curso){
  int op = -1, cod_curso;
  // imprime todos os cursos
  imprime_cursos(cursos, qtde_cursos);
  // op recebe o curso escolhido pelo usuario
  op = curso_escolhido(cursos, qtde_cursos);

  *indice_curso = op;
  // indice disciplina guarda a quantidade de disciplinas que foram adicionadas
  // no curso
  return cursos[op]->indice_disciplina;
}

// ler o codigo do curso digitado pelo usuario e
// verifica se o curso existe no vetor cursos
int curso_escolhido(Curso** cursos, int* qtde_cursos){
  int cod_curso, opcao;
  do
  {
    printf("Digite o codigo do curso: ");
    scanf("%d", &cod_curso);
    // procura_curso retorna a posicao do curso, caso encontre
    // retorna -1 caso o curso nao exista no vetor
    opcao = procura_curso(cursos, qtde_cursos, cod_curso);
    if(opcao == -1){
      printf("ERRO: curso não existe\n");
    }
  } while (opcao == -1);
  // while executa até o usuario digitar um curso valido

  return opcao;
}
