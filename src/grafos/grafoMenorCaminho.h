#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define POS_INF 1000000000
#define NEG_INF -1000000000

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

  /**
   * O argumento indicesVerticesVisitados serve para controlar quais
   * vertices ja foram visitados.
   * Lembrando que DFS eh uma funcao recursiva.
   **/
  void dfs(string rotuloVOrigem, bool* indicesVerticesVisitados) {
    dfs(rotuloVOrigem, indicesVerticesVisitados, POS_INF);
  }
  void dfs(string rotuloVOrigem, bool* indicesVerticesVisitados, int cor) {
    int indiceRotuloOrigem = obterIndiceVertice(rotuloVOrigem);

    if (indiceRotuloOrigem == -1 || indicesVerticesVisitados[indiceRotuloOrigem]) return;

    indicesVerticesVisitados[indiceRotuloOrigem] = true;
    if (cor != POS_INF) vertices[indiceRotuloOrigem] = to_string(cor);

    vector<pair<int, int>> vizinhos = arestas[indiceRotuloOrigem];

    for (int i = 0; i < vizinhos.size(); i++) dfs(vertices[vizinhos[i].first], indicesVerticesVisitados, cor);
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

  /**
   * Verifica se vertice rotuloVOrigem e vertice rotuloVDestino sao
   * conectados (vizinhos).
   **/
  bool saoConectados(string rotuloVOrigem, string rotuloVDestino) {
    int origem = obterIndiceVertice(rotuloVOrigem);
    int destino = obterIndiceVertice(rotuloVDestino);

    if (origem == -1 || destino == -1) return false;

    for (int i = 0; i < arestas.size(); i++) {
      if (i == origem) {
        for (int j = 0; j < arestas[i].size(); j++) {
          if (arestas[i][j].first == destino) {
            return true;
          }
        }
      }
    }

    return false;
  }

  /**
   * Verifica se ha algum caminho entre vertice rotuloVOrigem e
   * vertice rotuloVDestino.
   * A melhor forma de fazer isto eh reusando a funcao dfs.
   **/
  bool haCaminho(string rotuloVOrigem, string rotuloVDestino) {
    bool* indicesVerticesVisitados = (bool*)malloc(sizeof(bool) * vertices.size());
    int indiceRotuloOrigem = obterIndiceVertice(rotuloVOrigem);
    int indiceRotuloDestino = obterIndiceVertice(rotuloVDestino);

    if (indiceRotuloOrigem == indiceRotuloDestino && !saoConectados(rotuloVOrigem, rotuloVDestino)) return false;

    for (int i = 0; i < vertices.size(); i++) indicesVerticesVisitados[i] = false;

    dfs(rotuloVOrigem, indicesVerticesVisitados);

    return indicesVerticesVisitados[indiceRotuloDestino];
  }

  /**
   * Muda os rotulos do vertices dos diferentes componentes para
   * nomes que representam cores.
   * Dica: procura componentes partindo do vertice v0 ou v1, em ordem
   * crescente (mas voce pode usar outra ordem se desejar).
   * Retorna a quantidade de componentes.
   * A melhor forma de fazer isto e reusando a funcao dfs.
   **/
  int colorir() {
    bool* indicesVerticesVisitados = (bool*)malloc(sizeof(bool) * vertices.size());
    int cores = 0;

    for (int i = 0; i < vertices.size(); i++) indicesVerticesVisitados[i] = false;

    for (int i = 0; i < vertices.size(); i++) {
      if (!indicesVerticesVisitados[i]) {
        cores++;
        dfs(vertices[i], indicesVerticesVisitados, cores);
      }
    }

    return cores;
  }

  /**
   * Usa a abordagem de navegacao BFS para listar as distancias
   * entre o vertice rotuloVOrigem e cada um dos demais vertices.
   * A funcao BFS consegue listar a menor distancia entre um vertice
   * e os demais se o grafo for NAO-PONDERADO.
   * Retorna um vetor de inteiros com a quantidade de arestas
   * (distancia) e o vertice rotuloVOrigem e cada um dos demais vertices.
   * Nao eh uma funcao recursiva.
   * EH necessario utilizar a ED fila.
   **/
  int* bfs(string rotuloVOrigem) {
    int indiceRotuloOrigem = obterIndiceVertice(rotuloVOrigem);
    int* distancias = (int*)malloc(sizeof(int) * vertices.size());
    bool* indicesVerticesVisitados = (bool*)malloc(sizeof(bool) * vertices.size());

    for (int i = 0; i < vertices.size(); i++) {
      indicesVerticesVisitados[i] = false;
      distancias[i] = 0;
    }

    indicesVerticesVisitados[indiceRotuloOrigem] = true;

    queue<int> fila;

    fila.push(indiceRotuloOrigem);

    while (!fila.empty()) {
      int indiceVerticeFrenteFila = fila.front();

      vector<pair<int, int>> vizinhos = arestas[indiceVerticeFrenteFila];

      for (int i = 0; i < vizinhos.size(); i++) {
        if (!indicesVerticesVisitados[vizinhos[i].first]) {
          fila.push(vizinhos[i].first);
          indicesVerticesVisitados[vizinhos[i].first] = true;
          distancias[vizinhos[i].first] = distancias[indiceVerticeFrenteFila] + 1;
        }
      }
      fila.pop();
    }

    return distancias;
  }

  /**
   * Usamos o BellmanFord para encontrar menor caminho
   * em grafos com arestas com pesos negativos.
   * O BellmanFord consegue detectar ciclos negativos
   * e atribuir o valor NEG_INF (constante definida nesse arquivo)
   * aos vértices que pertençam ao ciclo.
   * POS_INF deve ser atribuído aos vértices inalcançáveis.
   * O aspecto negativo é sua complexidade de tempo: O(V*E).
   * Isto acontece pois, como possui arestas negativas, cada vértice
   * do grafo precisa ser processado V vezes.
   * Pseudo-código: https://github.com/eduardolfalcao/edii/blob/master/conteudos/Grafos.md#bellman-ford
   **/
  int* bellmanFord(string rotuloVOrigem) {
    int indiceRotuloOrigem = obterIndiceVertice(rotuloVOrigem);
    int* distancias = (int*)malloc(sizeof(int) * vertices.size());

    for (int i = 0; i < vertices.size(); i++)
      distancias[i] = POS_INF;

    distancias[indiceRotuloOrigem] = 0;

    for (int i = 0; i < vertices.size(); i++) {
      bool mudou = false;

      for (int j = 0; j < arestas.size(); j++) {
        for (int k = 0; k < arestas[j].size(); k++) {
          int indiceVerticeReferencia = j;
          int indiceVerticeVizinho = arestas[j][k].first;
          int peso = arestas[j][k].second;
          int distanciaAntiga = distancias[indiceVerticeVizinho];

          distancias[indiceVerticeVizinho] =
              min(distancias[indiceVerticeVizinho], distancias[indiceVerticeReferencia] + peso);

          if (distancias[indiceVerticeVizinho] != distanciaAntiga)
            mudou = true;
        }
      }
      if (!mudou)
        break;
    }

    for (int j = 0; j < arestas.size(); j++) {
      for (int k = 0; k < arestas[j].size(); k++) {
        int indiceVerticeReferencia = j;
        int indiceVerticeVizinho = arestas[j][k].first;
        int peso = arestas[j][k].second;

        if (distancias[indiceVerticeReferencia] + peso < distancias[indiceVerticeVizinho])
          distancias[indiceVerticeVizinho] = NEG_INF;
      }
    }

    return distancias;
  }

  /**
   * Usamos o Dijkstra para encontrar menor caminho
   * em grafos sem arestas com pesos negativos.
   * O Dijkstra retorna respostas incorretas caso o grafo
   * possua arestas negativas, e portanto não consegue
   * detectar ciclos negativos. Este é o aspecto negativo.
   * POS_INF deve ser atribuído aos vértices inalcançáveis.
   * O aspecto positivo é sua complexidade de tempo: O(V+E).
   * Isto acontece pois, como o grafo não possui arestas negativas,
   * cada vértice do grafo precisa ser processado apenas 1 vez.
   * Pseudo-código: https://github.com/eduardolfalcao/edii/blob/master/conteudos/Grafos.md#dijkstra
   * Ilustração: https://docs.google.com/drawings/d/1NmkJPHpcg8uVcDZ24FQiYs3uHR5n-rdm1AZwD74WiMY/edit?usp=sharing
   **/
  int* dijkstra(string rotuloVOrigem) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> fila;
    vector<bool> indicesVerticesVisitados;

    int indiceRotuloOrigem = obterIndiceVertice(rotuloVOrigem);
    int* distancias = (int*)malloc(sizeof(int) * vertices.size());

    for (int i = 0; i < vertices.size(); i++) {
      distancias[i] = POS_INF;
      indicesVerticesVisitados.push_back(false);
    }

    distancias[indiceRotuloOrigem] = 0;
    fila.push({distancias[indiceRotuloOrigem], indiceRotuloOrigem});

    while (!fila.empty()) {
      int indiceVerticeFrenteFila = fila.top().second;

      fila.pop();

      if (indicesVerticesVisitados[indiceVerticeFrenteFila])
        continue;
      indicesVerticesVisitados[indiceVerticeFrenteFila] = true;

      vector<pair<int, int>> vizinhosVerticeFrente = arestas[indiceVerticeFrenteFila];

      for (int i = 0; i < vizinhosVerticeFrente.size(); i++) {
        int indiceVerticeVizinho = vizinhosVerticeFrente[i].first;
        int peso = vizinhosVerticeFrente[i].second;

        if (distancias[indiceVerticeFrenteFila] + peso < distancias[indiceVerticeVizinho]) {
          distancias[indiceVerticeVizinho] = distancias[indiceVerticeFrenteFila] + peso;
          fila.push({distancias[indiceVerticeVizinho], indiceVerticeVizinho});
        }
      }
    }

    return distancias;
  }

  vector<string> getVertices() {
    return vertices;
  }

  vector<vector<pair<int, int>>> getArestas() {
    return arestas;
  }
};