//--------------------------------------------------------------
// NOMES DOS RESPONS¡VEIS: blablabla E blablabla
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <limits.h> /*pode incluir?*/

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
	VERTICE *g = (VERTICE*) malloc(sizeof(VERTICE) * N);
	for (int i = 0; i < N; i++) {
		g[i].flag = 0;
		g[i].via = 0;
		g[i].dist = INT_MAX;
		g[i].inicio = NULL;
		aberto[i] = estaAberto[i];
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
	novoNo->adj = destino;
	novoNo->peso = peso;
	novoNo->prox = g[origem].inicio;
	g[origem].inicio = novoNo;
}

/*
	N = Grafo de N vertices
	A = Grafo de A arestas
	*ijpeso = Representa as arestas (tamanho 3 * A)
		ex: A = 2, ijpeso={1,2,3,4,5,6}
			grafo g possui uma aresta entre os vertices 1 e 2 com peso 3
			e possui uma aresta entre os vertices 4 e 5 com peso 6
	*aberto = indica se os vertices estao abertos ou fechados
		- contem apenas valores 0 ou 1
	inicio, fim = busca
	chave = vertice chave
*/
// funcao principal
NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave);
int encontraMenorDistancia(VERTICE *g, int N);

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave)
{
	NO* resp;
	resp = NULL;
	bool temChave = false;

	// seu codigo AQUI

	/*
		inicializa grafo
	*/
	VERTICE* g = criaVetices(N, aberto);
	for (int i = 0; i < A; i++) {
		insereArestas(g, i, ijpeso)
	}
	//...

	/*dist da origem pra ela mesma*/
	g[inicio].dist = 0;

	for (int i = 0; i < N; i++) {
		/*encontra o vertice nao visitado com menor dist*/
		int u = encontraMenorDistancia(g, N);

		/*
			se o vertice onde vai fazer a busca nao estiver aberto, pula ele
		*/
		if (g[u].aberto && temChave == false) {
			temChave = true;
		} else if (!g[u].aberto && temChave == false){
			continue;
		} 
		/* marca o vertice atual como visitado */
		g[u].flag = 1;
		
		NO* p = grafo[u].inicio;
		while(p) {
			int adj = p->adj;
			int peso = p->peso;

			/*
				se
					vertice atual nao foi visitado
					dist do vertice atual nao é infinito -> evita erro de overflow
					dist do vertice atual é menor que dist do vertice adj

						dist do vertice adj é a dist do vertice atual + peso do vertice adj
			*/
			if (!g[adj].flag && (g[u].dist != INT_MAX) && (g[u].dist + peso < g[adj].dist)) {
				g[adj].dist = g[u].dist + peso;
				/* vai salvando em uma lista pra depois retornar? */
			}
			p = p->prox;
		}
	}
	return resp;
}

/*
	encontra o vertice nao visitado com menor dist 
*/
int encontraMenorDistancia(VERTICE *g, int N) {
	int min = INT_MAX;
	int min_idx;

	for (int i = 0; i < N; i++) {
		if (g[i].flag == 0 && g[i].dist <= min) {
			min = g[i].dist;
			min_idx = i;
		}
	}
	return min_idx;
}


//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {


	// aqui vc pode incluir codigo de teste

	// exemplo de teste trivial

	int N=3; // grafo de 3 vÈrtices numerados de 1..3
	int aberto[] = {1,1,1}; // todos abertos
	int inicio=1;
	int fim=3;
	int chave=2;
	int ijpeso[]={1,2,10, 2,3,20, 3,1,10};

	// o EP sera testado com uma serie de chamadas como esta
	NO* teste = null;
	teste = caminho(N, ijpeso, aberto, inicio, fim, chave);
	return teste;

}

// por favor nao inclua nenhum cÛdigo abaixo da funÁ„o main()