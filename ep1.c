//--------------------------------------------------------------
// NOMES DOS RESPONS¡VEIS: blablabla E blablabla
//--------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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
	N = Grafo de N vertices
	A = Grafo de A arestas
	*ijpeso = Representa as arestas (tamanho 3 * A)
		- onde: 
			i = vertice origem
			j = vertice destino 
			peso
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


//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO *caminho(int N, int A, int *ijpeso, int *aberto, int inicio, int fim, int chave)
{
	NO* resp;
	resp = NULL;

	// seu codigo AQUI

	//...

	return resp;
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