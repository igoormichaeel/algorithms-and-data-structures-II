#include <iostream>
#include <vector>
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
    } else
      return;
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

      for (int i = 0; i < arestas.size(); i++) {
        if (i == origem) {
          arestas[i].push_back(par);
          return;
        }
      }
    }
  }

  /**
   * Verifica se vertice rotuloVOrigem e vertice rotuloVDestino sao
   * conectados (vizinhos).
   **/
  bool saoConectados(string rotuloVOrigem, string rotuloVDestino) {
    int origem = obterIndiceVertice(rotuloVOrigem);
    int destino = obterIndiceVertice(rotuloVDestino);

    if (origem == -1 || destino == -1)
      return false;
    else {
      for (int i = 0; i < arestas.size(); i++) {
        if (i == origem) {
          for (int j = 0; j < arestas[i].size(); j++) {
            if (arestas[i][j].first == destino) {
              return true;
            }
          }
          return false;
        }
      }
    }
  }

  vector<string> getVertices() { return vertices; }

  vector<vector<pair<int, int>>> getArestas() { return arestas; }
};