//--------------------------------------------------------------
// NOMES DOS RESPONSÁVEIS: Mycaelli Cerqueira de Lima E Ellen Leal dos Santos
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int grupo() {
  return 4;
}

int nroUSP1() {
    return 10723562;
}

int nroUSP2() {
    return 13719902;
}

// elemento das listas de adjacência e de resposta
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

VERTICE *criaVetices(int N, int *estaAberto) {
	VERTICE *g = (VERTICE*) malloc(sizeof(VERTICE) * (N + 1));
	for (int i = 1; i <= N; i++) {
		g[i].flag = 0;
		g[i].via = -1;
		g[i].dist = INT_MAX;
		g[i].inicio = NULL;
		g[i].aberto = estaAberto[i-1];
	}
	return g;
}

void insereArestas(VERTICE *g, int atual, int *ijpeso) {
	int origem = ijpeso[atual*3];
	int destino = ijpeso[atual*3+1];
	int peso = ijpeso[atual*3+2];

	NO* novoNoOrigemDestino = (NO*)malloc(sizeof(NO));
    if (!novoNoOrigemDestino) {
        return;
    }
    novoNoOrigemDestino->adj = destino;
    novoNoOrigemDestino->peso = peso;
    novoNoOrigemDestino->prox = g[origem].inicio;
    g[origem].inicio = novoNoOrigemDestino;
	    NO* novoNoDestinoOrigem = (NO*)malloc(sizeof(NO));
    if (!novoNoDestinoOrigem) {
        return;
    }
    novoNoDestinoOrigem->adj = origem;
    novoNoDestinoOrigem->peso = peso;
    novoNoDestinoOrigem->prox = g[destino].inicio;
    g[destino].inicio = novoNoDestinoOrigem;
}

void freeGrafo(VERTICE *g, int N) {
	for(int i = 1; i <= N; i++)
	{
		NO *p = g[i].inicio;
		while(p) {
			NO *temp = p;
			p = p->prox;
			free(temp);
		}
	}
	free(g);
}

void freeCaminho(NO* p) {
	while(p) {
		NO *temp = p;
		p = p->prox;
		free(temp);
	}
}

// funcao principal
NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave);
int encontraMenorDistancia(VERTICE *g, int N);
NO* dijkstra(VERTICE *g, int origem, int destino,  int N, int *pesoTotal, bool *temChave, int chave);
void adicionaNosResposta(NO *resp, int adj);;
void reinicializaEAbreVertices(VERTICE *g, int N);


NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave)
{		
	NO* caminhoSemChave = NULL;
	NO* caminhoComChave = NULL;
	int pesoSemChave = 0;
	int pesoComChave = 0;
	bool temChave = false;

	VERTICE* g = criaVetices(N, aberto);
	for (int i = 0; i < A; i++) {
		insereArestas(g, i, ijpeso);
	}
	caminhoSemChave = dijkstra(g, inicio, fim, N, &pesoSemChave, &temChave, chave);
	NO *atual = caminhoSemChave;
	if (temChave) {
		reinicializaEAbreVertices(g, N);
		caminhoComChave = dijkstra(g, inicio, fim, N, &pesoComChave, &temChave, chave);
	}
	freeGrafo(g, N);

	atual = caminhoComChave;
	if (pesoComChave <= pesoSemChave && pesoComChave > 0)
	{
		freeCaminho(caminhoSemChave);
		return caminhoComChave;
	}
	else if (pesoSemChave > 0)
	{
		freeCaminho(caminhoComChave);
		return caminhoSemChave;
	}
	return NULL;
}

void reinicializaEAbreVertices(VERTICE *g, int N) {
	for (int i = 1; i <= N; i++) {
		g[i].flag = 0;
		g[i].via = -1;
		g[i].aberto = 1;
		g[i].dist = INT_MAX;
	}
}

void adicionaNoInicio(NO** resp, int adj) {
	NO *novoNo = (NO *)malloc(sizeof(NO));
    novoNo->adj = adj;
    novoNo->prox = *resp;
    *resp = novoNo;
}

int encontraMenorDistancia(VERTICE *g, int N) {
	int min = INT_MAX;
	int min_idx = -1;
	for (int i = 1; i <= N; i++) {
		if (!g[i].flag && g[i].dist <= min && g[i].aberto) {
			min = g[i].dist;
			min_idx = i;
		}
	}
	return min_idx;
}

NO* dijkstra(VERTICE *g, int origem, int destino,  int N, int *pesoTotal, bool *temChave, int chave) {
	g[origem].dist = 0;
	g[origem].via = origem;

	for (int i = 1; i <= N; i++) {
		if (!g[i].aberto) 
			continue;

		int u = encontraMenorDistancia(g, N);
		g[u].flag = 1;
		NO* p = g[u].inicio;
		while (p) {
			int adj = p->adj;
			if (p->adj == chave) {
				*temChave = true;
			}
			int peso = p->peso;
			if (!g[adj].flag && g[u].dist != INT_MAX && g[u].dist + peso < g[adj].dist) {
				g[adj].dist = g[u].dist + peso;
				g[adj].via = u;
			}
			p = p->prox;
		}
	}

    if (g[destino].dist == INT_MAX) {
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

int main() {

  
    int N = 8;
    int A = 12;
    int aberto[] = {1, 1, 0, 1, 1, 1, 0, 1};
    int inicio = 5;
    int fim = 4;
    int chave = 6;
    int ijpeso[] = {
        1, 2, 8,
        1, 3, 6,
        1, 5, 9,
        2, 3, 8,
        2, 6, 11,
        2, 7, 7,
        2, 8, 14,
        3, 6, 13,
        3, 8, 2,
        6, 7, 10,
        7, 8, 9,
        8, 4, 8};
	NO *teste;
	teste = caminho(N, A, ijpeso, aberto, inicio, fim, chave);

	NO* ini = teste;
	while (ini) {
		printf("%d->", ini->adj);
		ini = ini->prox;
	}
	printf("\n");
	return teste;

}
