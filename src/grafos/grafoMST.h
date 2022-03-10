#include <iostream>
#include <queue>
#include <vector>

#include "stdbool.h"

using namespace std;

class GrafoListaAdj {
 private:
  vector<string> vertices;

  // first eh o indice do vertice, second eh o peso (caso o grafo seja ponderado)
  vector<vector<pair<int, int>>> arestas;

  /**
   * A principio nao temos nenhuma ordenacao usando os rotulos.
   * Portanto, usaremos busca linear.
   **/
  int obterIndiceVertice(string rotuloVertice) {
    for (int i = 0; i < vertices.size(); i++) {
      if (vertices[i] == rotuloVertice) return i;
    }
    return -1;
  }

 public:
  /**
   * Lembrem-se:
   *       1) nao podemos inserir vertices com mesmo rotulo
   *       2) toda vez que inserirmos um novo vertice, precisaremos
   *          inserir um vetor para representar as conexoes daquele
   *          vertice na lista de adjacencias
   **/
  void inserirVertice(string rotuloVertice) {
    int existeRotulo = obterIndiceVertice(rotuloVertice);

    if (existeRotulo == -1) {
      vertices.push_back(rotuloVertice);
      vector<pair<int, int>> v;
      arestas.push_back(v);
    }
  }

  /**
   * Sempre que o grafo for nao ponderado, adicionaremos o peso 1,
   * por conveniencia.
   **/
  void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino) {
    inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
  }

  void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino) {
    inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, 1);
    inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, 1);
  }

  void inserirArestaNaoDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso) {
    inserirArestaDirecionada(rotuloVOrigem, rotuloVDestino, peso);
    inserirArestaDirecionada(rotuloVDestino, rotuloVOrigem, peso);
  }

  /**
   * Inserir uma aresta entre rotuloVOrigem e rotuloVDestino com o peso
   * especificado.
   **/
  void inserirArestaDirecionada(string rotuloVOrigem, string rotuloVDestino, int peso) {
    int origem = obterIndiceVertice(rotuloVOrigem);
    int destino = obterIndiceVertice(rotuloVDestino);

    if (origem != -1 && destino != -1) {
      pair<int, int> par;

      par.first = destino;
      par.second = peso;

      arestas[origem].push_back(par);
    }
  }

  // Grupo do union-find
  class Grupo {
   public:
    int pai;
    int tamanho;
  };

  // encontrar raiz
  // pode ser com ou sem path compression
  int encontrarRaiz(Grupo* grupos, int i) {
    if (grupos[i].pai == i) return i;
    else return encontrarRaiz(grupos, grupos[i].pai);
  }

  bool mesmoGrupo(Grupo* grupos, int a, int b) {
    return encontrarRaiz(grupos, a) == encontrarRaiz(grupos, b);
  }

  int tamanhoGrupo(Grupo* grupos, int a) {
    return grupos[encontrarRaiz(grupos, a)].tamanho;
  }

  void unirGrupos(Grupo* grupos, int a, int b) {
    int raizA = encontrarRaiz(grupos, a);
    int raizB = encontrarRaiz(grupos, b);

    if (raizA == raizB) return;

    if (grupos[raizA].tamanho >= grupos[raizB].tamanho) {
      grupos[raizB].pai = raizA;
      grupos[raizA].tamanho += grupos[raizB].tamanho;
    } else {
      grupos[raizA].pai = raizB;
      grupos[raizB].tamanho += grupos[raizA].tamanho;
    }
  }

  // criei essa classe pra facilitar a ordenacao
  // das arestas com menor peso (que faz parte do
  // algoritmo de Kruskal)
  class Aresta {
   public:
    int origem;
    int destino;
    int peso;

    Aresta(int origem, int destino, int peso) : origem(origem), destino(destino), peso(peso) {}
  };

  // sobrescrever operator< para que a priority_queue
  // ordene como desejamos
  friend bool operator<(const Aresta& a1, const Aresta& a2) {
    return a1.peso < a2.peso;
  }

  friend bool operator>(const Aresta& a1, const Aresta& a2) {
    return a1.peso > a2.peso;
  }

  GrafoListaAdj* KruskalMST() {
    GrafoListaAdj* mst = new GrafoListaAdj();
    Grupo* grupos = (Grupo*)malloc(sizeof(Grupo) * vertices.size());

    for (int i = 0; i < vertices.size(); i++) {
      mst->inserirVertice(vertices[i]);

      grupos[i].pai = i;
      grupos[i].tamanho = 1;
    }

    priority_queue<Aresta, vector<Aresta>, greater<Aresta>> arestasMenorPeso;

    for (int i = 0; i < vertices.size(); i++) {
      for (int j = 0; j < arestas[i].size(); j++) {
        arestasMenorPeso.push(Aresta(i, arestas[i][j].first, arestas[i][j].second));
      }
    }

    while (!arestasMenorPeso.empty()) {
      Aresta prov = arestasMenorPeso.top();

      if (!mesmoGrupo(grupos, prov.origem, prov.destino)) {
        unirGrupos(grupos, prov.origem, prov.destino);

        mst->inserirArestaNaoDirecionada(vertices[prov.origem], vertices[prov.destino], prov.peso);
      }

      arestasMenorPeso.pop();
    }

    return mst;
  }

  vector<string> getVertices() {
    return vertices;
  }

  vector<vector<pair<int, int>>> getArestas() {
    return arestas;
  }
};