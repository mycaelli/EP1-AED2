//--------------------------------------------------------------
// NOMES DOS RESPONS¡VEIS: blablabla E blablabla
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#include "testes.h"

/*
	- preencher grupo e numero usp
	- ver se pode usar a lib limits e qualquer outra que foi adicionada
		- se nao puder tem que adaptar o codigo sem elas
	- testar todos os cenarios do grafosParaTestes e + o que der
	- confirmar se precisa ter o peso nos Nos da lista de resposas
		- se precisar tem que implementar isso
	- verificar se alguma coisa que o prof tinha colocado no arquivo foi apagada sem querer
	- dar free nas coisas que foram mallocadas 
		- depois que elas foram usadas
	- deixar o arquivo no formato certo 
		- acho que é .cpp
	- apagar funcoes nao necessarias 
		- imprimeGrafo
	- verificar se a condicao de retorno ta certa mesmo 
		- if (*pesoTotalSemChave > *pesoTotalComChave ...)
	- tratar o codigo pra entradas vazias
	- TESTAR EM UM WINDOWS!!! 
*/

int grupo() {
  return 0;
}

// ######### ESCREVA O NROUSP AQUI
int nroUSP1() {
    return 10723562;
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

// funcao principal
NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave);
int encontraMenorDistancia(VERTICE *g, int N);
NO* dijkstra(VERTICE *g, int origem, int destino,  int N, int *pesoTotal, bool *temChave, int chave);
void adicionaNosResposta(NO *resp, int adj);;
void reinicializaEAbreVertices(VERTICE *g, int N);


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
	atual = caminhoComChave;

	if (pesoComChave <= pesoSemChave && pesoComChave > 0)
		return caminhoComChave;
	else if (pesoSemChave > 0)
		return caminhoSemChave;

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


//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {

	// exemplo pdf
	int N = 9;
    int A = 10;
    int aberto[] = {0, 1, 1, 1, 1, 1, 1, 1, 1};
    int inicio = 7;
    int fim = 4;
    int chave = 6;
    int ijpeso[] = {
        1, 2, 30,
        1, 3, 20,
		2, 7, 30,
		2, 6, 20,
		3, 4, 20,
		3, 7, 80, 
		4, 9, 80,
		5, 8, 10,
		6, 7, 10, 
		7, 9, 80,};


	// se o vertice que tem a chave nao for adjacente do melhor caminho mas houver um peso min com os vertices abertos 
	NO *teste;
	teste = caminho(N, A, ijpeso, aberto, inicio, fim, chave);

	NO* ini = teste;
	while (ini) {
		printf("%d->", ini->adj);
		ini = ini->prox;
	}
	printf("\n");
	return 0;

}

// por favor nao inclua nenhum cÛdigo abaixo da funÁ„o main()