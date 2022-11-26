/*TAD: jogador(nome, jogos, gols, assistencia)*/
/*Tipo exportado*/

typedef struct jogador Jogador;

/*-=-=-=-=-=FUNCOES EXPORTADAS-=-=-=-=-=-=-=-=-=-=-*/

/*atribui, funcao que recebe as informacoes dos jogadores e adiciona ao vetor de struct*/
Jogador* atribui(char nome[], int jogos, int gols, int assistencias);

/*Imprime, funcao que imprime as informacoes de um jogador*/
void imprime_jogador(int n, Jogador** jogador);

/*Soma_estaatisticas, funcao que recebe dois jogadores e mostra a soma de suas estatisticas*/
void soma_estatistica(Jogador** jogador, char nome1[], char nome2[], int n);

/*ehbom, funcao que recebe um jogador, verifica a quantidade de gols por partida e diz se eh bom */
void ehbom(Jogador** jogador, char nomejg[], int n);

/*libera_memoria, funcao que desaloca a memoria armazenada dinamicamente*/
void libera_memoria(int n, Jogador** jogador);
