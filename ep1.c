//--------------------------------------------------------------
// NOMES DOS RESPONS¡VEIS: blablabla E blablabla
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> /*pode incluir?*/
#include <stdbool.h>

// lib de bool

int grupo() {
  return 0;
}

// ######### ESCREVA O NROUSP AQUI
int nroUSP1() {
    return 0;
}

int nroUSP2() {
    return 0;
}

// elemento das listas de adjacÍncia e de resposta - NAO ALTERE ESTA DEFINICAO
typedef struct estr 
{
    int adj; // elemento
	int peso; // custo (n„o precisa ser usado na resposta)
    struct estr *prox;
} NO;


// vertices do grafo (salas) - use este tipo ao criar o grafo  - NAO ALTERE ESTA DEFINICAO
typedef struct 
{
    int flag; // para uso na busca em largura e profundidade, se necessario
    bool aberto; // vale true se a sala em questao esta aberta
    int via; // use este campo se precisar computar algum caminho etc.
	int dist; // use este campo se precisar computar alguma dist‚ncia etc.
    NO* inicio;
} VERTICE;

/*
	funcao cria N vertices
	inicializa seus campos com 0
	define se o vertice esta aberto ou fechado a partir do array estaAberto
*/
VERTICE *criaVetices(int N, int *estaAberto) {
	VERTICE *g = (VERTICE*) malloc(sizeof(VERTICE) * (N + 1));
	for (int i = 1; i <= N; i++) {
		g[i].flag = 0;
		g[i].via = -1;
		g[i].dist = INT_MAX;
		g[i].inicio = NULL;
		g[i].aberto = estaAberto[i];
		// printf("%d %d %d %d %p %d\n", 
		// i,		
		// g[i].flag,
		// g[i].via,
		// g[i].dist,
		// g[i].inicio,
		// g[i].aberto);
	}
	return g;
}

/*
	funcao que insere as arestas no grafo
	ex primeira chamada -> i = 0
		origem = ijpeso[0 * 3]
		destino = ijpeso[0 * 3 + 1]
		peso = ijpeso[0 * 3 + 2]

*/
void insereArestas(VERTICE *g, int atual, int *ijpeso) {
	int origem = ijpeso[atual*3];
	int destino = ijpeso[atual*3+1];
	int peso = ijpeso[atual*3+2];
	
	NO *novoNo = (NO*)malloc(sizeof(NO));
	if (!novoNo) {
		printf("erro de alocacao");
	}
	novoNo->adj = destino;
	novoNo->peso = peso;
	novoNo->prox = g[origem].inicio;
	g[origem].inicio = novoNo;
}

// funcao principal
//NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave);
int encontraMenorDistancia(VERTICE *g, int N);
NO* dijkstra(VERTICE *g, int origem, int destino,  int N, int *pesoTotal);
void adicionaNosResposta(NO *resp, int adj);


void imprimeGrafo(VERTICE *g, int N) {
	for (int i = 1; i <= N; i++) {
		printf("%d", i);
		NO* p = g[i].inicio;
		while(p) {
			printf("->%d (%d) ", p->adj, p->peso);
			p = p->prox;
		}
		printf("\n");
	}
}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave)
{
	NO* resp;
	resp = NULL;
	int value = 0;
	int *pesoSemChave = &value;
	bool temChave = false;

	// seu codigo AQUI

	VERTICE* g = criaVetices(N, aberto);
	for (int i = 0; i < A; i++) {
		insereArestas(g, i, ijpeso);
	}
	imprimeGrafo(g, N);
	resp = dijkstra(g, inicio, fim, N, pesoSemChave);
	printf("pesoTotal %d\n", *pesoSemChave);

	NO *atual = resp;
	while(atual) { 
		printf("%d->", atual->adj);
		atual = atual->prox;
	}

	/* TEM QUE DAR FREE NO GRAFO */

	return resp;
}

void adicionaNoInicio(NO** resp, int adj) {
	NO *novoNo = (NO *)malloc(sizeof(NO));
    novoNo->adj = adj;
    novoNo->prox = *resp;
    *resp = novoNo;
}

/*
	encontra o vertice com dist minima
*/

int encontraMenorDistancia(VERTICE *g, int N) {
	int min = INT_MAX;
	int min_idx = -1;

	for (int i = 1; i <= N; i++) {
		if (!g[i].flag && g[i].dist <= min) {
			min = g[i].dist;
			min_idx = i;
		}
	}
	return min_idx;
}

NO* dijkstra(VERTICE *g, int origem, int destino,  int N, int *pesoTotal) {
	g[origem].dist = 0;
	g[origem].via = origem;

	for (int i = 1; i <= N; i++) {
		// if (!g[i].aberto) 
		// 	continue;
		int u = encontraMenorDistancia(g, N);
		g[u].flag = 1;
		NO* p = g[u].inicio;
		while (p) {
			int adj = p->adj;
			int peso = p->peso;
			if (!g[adj].flag && g[u].dist != INT_MAX && g[u].dist + peso < g[adj].dist) {
				g[adj].dist = g[u].dist + peso;
				g[adj].via = u;
			}
			p = p->prox;
		}
	}

	// Recuperar o caminho mais curto
    if (g[destino].dist == INT_MAX) {
        printf("Nao ha caminho entre a origem e o destino.\n");
        return NULL;
    }

	NO *resp =  NULL;
	int atual = destino;

	while (atual != origem) {
    	int via = g[atual].via;
		adicionaNoInicio(&resp, atual);
    	NO* p = g[via].inicio;
    	while (p) {
    	    if (p->adj == atual) {
    	        *pesoTotal += p->peso;
    	        break;
    	    }
    	    p = p->prox;
    	}
    	atual = via;
    }
	adicionaNoInicio(&resp, atual);
	return resp;
}


//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {



	// aqui vc pode incluir codigo de teste

	// exemplo de teste trivial

	// int N=4; // grafo de 3 vÈrtices numerados de 1..3
	// int aberto[] = {1,1,1,1}; // todos abertos
	// int inicio=1;
	// int fim=4;
	// int chave=2;
    // int A = 5;
	// int ijpeso[]={1,2,10, 2,3,20, 3,1,10, 3,4,1, 1,4,3};

    int N = 6;
    int A = 8;
    int aberto[] = {1, 1, 1, 1, 1, 0};
    int inicio = 1;
    int fim = 5;
    int chave = 2;
    int ijpeso[] = {
        1, 2, 14,
        1, 6, 3,
        1, 4, 5,
        2, 3, 6,
        2, 6, 5,
        3, 4, 8,
        4, 5, 10,
        5, 6, 8};

	// o EP sera testado com uma serie de chamadas como esta
	//NO* teste = NULL;
	NO *teste;
	teste = caminho(N, A, ijpeso, aberto, inicio, fim, chave);

	// NO* ini = teste;
	// while (ini) {
	// 	printf("%d\n", ini->adj);
	// 	ini = ini->prox;
	// }
	// for (int i = 0; i < N; i++) {
	// 	printf("%d ", teste[i]);
	// }
	// printf("\n");
	return 0;

}

// por favor nao inclua nenhum cÛdigo abaixo da funÁ„o main()