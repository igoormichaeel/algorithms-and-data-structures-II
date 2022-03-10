#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct GrafoMatrizAdj {
  int** arestas;
  char** rotuloVertices;
  int verticesInseridos;
  int maxNumVertices;
};

/**
 * Se o grafo for ponderado, inicializamos cada posicao da matriz com INT_MAX.
 * Se o grafo for não ponderado, inicializamos cada posicao da matriz com 0.
 **/
struct GrafoMatrizAdj* inicializar(int numVertices, bool ponderado) {
  struct GrafoMatrizAdj* grafo = (struct GrafoMatrizAdj*)malloc(sizeof(struct GrafoMatrizAdj));
  int** arestas = (int**)malloc(numVertices * sizeof(int*));
  char** vertices = (char**)malloc(numVertices * sizeof(char*));

  for (int i = 0; i < numVertices; i++) {
    arestas[i] = (int*)malloc(numVertices * sizeof(int));
    vertices[i] = NULL;
  }

  for (int i = 0; i < numVertices; i++) {
    for (int j = 0; j < numVertices; j++) {
      if (ponderado)
        arestas[i][j] = INT_MAX;
      else
        arestas[i][j] = 0;
    }
  }

  grafo->arestas = arestas;
  grafo->rotuloVertices = vertices;
  grafo->verticesInseridos = 0;
  grafo->maxNumVertices = numVertices;

  return grafo;
}

/**
 * A principio nao temos nenhuma ordenacao usando os rotulos.
 * Portanto, usaremos busca linear
 **/
int obterIndiceVertice(struct GrafoMatrizAdj* grafo, char* rotuloVertice) {
  for (int i = 0; i < grafo->verticesInseridos; i++) {
    if (strcmp(grafo->rotuloVertices[i], rotuloVertice) == 0) return i;
  }
  return -1;
}

/**
 * Se o grafo for ponderado, usamos a variavel peso para especificar o peso da
 *aresta. Se o grafo for não ponderado, passaremos o valor 1 para a variavel
 *peso, de modo que represente existência da aresta. Se um dos rotulos dos
 *vertices nao existir, simplesmente nao faremos nada.
 **/
void inserirAresta(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino, int peso) {
  int origem = obterIndiceVertice(grafo, rotuloVOrigem);
  int destino = obterIndiceVertice(grafo, rotuloVDestino);

  if (origem == -1 && destino == -1) grafo->arestas[origem][destino] = peso;
}

/**
 * Usamos a variavel grafo->verticesInseridos para controlar a quantidade de
 *vertices que ja foi inserido no grafo. Logo, ela pode/deve ser usada para
 *especificar em qual posicao o vertice a ser inserido sera alocado.
 **/
void inserirVertice(struct GrafoMatrizAdj* grafo, char* rotuloVertice) {
  int existeRotulo = obterIndiceVertice(grafo, rotuloVertice);
  if (grafo->verticesInseridos != grafo->maxNumVertices && existeRotulo == -1) {
    grafo->rotuloVertices[grafo->verticesInseridos] = rotuloVertice;
    grafo->verticesInseridos++;
  } else {
    return;
  }
}

/**
 * Tomar cuidado com as diferenças semânticas entre haver conexão entre dois
 *vertices em um grafo ponderado, e haver conexão entre dois vertices em um
 *grafo nao-ponderado.
 **/
bool saoConectados(struct GrafoMatrizAdj* grafo, char* rotuloVOrigem, char* rotuloVDestino) {
  int origem = obterIndiceVertice(grafo, rotuloVOrigem);
  int destino = obterIndiceVertice(grafo, rotuloVDestino);

  if (origem == -1 || destino == -1)
    return false;
  else {
    if (grafo->rotuloVertices[origem][destino] != 0 || grafo->rotuloVertices[origem][destino] != INT_MAX)
      return true;
    else
      return false;
  }
}