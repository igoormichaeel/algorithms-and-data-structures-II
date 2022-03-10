#include <iostream>
#include <vector>
using namespace std;

template <typename K, typename V>
class Tupla {
 private:
  K chave;
  V valor;
  Tupla* prox;

 public:
  Tupla(K c, V v) {
    chave = c;
    valor = v;
    prox = NULL;
  }

  K getChave() {
    return chave;
  }

  V getValor() {
    return valor;
  }

  Tupla* getProx() {
    return prox;
  }

  void setProx(Tupla* prox) {
    Tupla::prox = prox;
  }
};

template <typename Chave, typename Valor>
class TabelaHash {
 private:
  Tupla<Chave, Valor>** tabela;

  // tamanho atual do array
  int qtde_buckets;

  // qtdade de elementos ja inseridos na tabela hash
  int tamanho;

  /**
   * Funcao para inserir a tupla <c,v> na tabela.
   * eh preciso calcular o codigo hash a partir da chave c.
   * Em seguida, usamos qtde_buckets para descobrir o indice
   * dessa tupla. Prestar atencao na alocacao de tupla quando
   * ha colisoes. A funcao hash as vezes retorna valores
   * negativos: use abs() para evitar indices negativos.
   **/
  void inserir(Chave c, Valor v, Tupla<Chave, Valor>** tabela) {
    // int hash = abs((int)hash<string>{}(v));
    int codigoHash = abs((int)hash<Chave>{}(c));
    int posicao = codigoHash % qtde_buckets;

    Tupla<Chave, Valor>* aux = tabela[posicao];
    Tupla<Chave, Valor>* newTupla = (Tupla<Chave, Valor>*)calloc(1, sizeof(Tupla<Chave, Valor>));

    *newTupla = Tupla<Chave, Valor>(c, v);

    if (!aux) {
      tabela[posicao] = newTupla;

      return;
    }

    while (aux->getProx()) {
      aux = aux->getProx();
    }

    aux->setProx(newTupla);
  }

  /**
   * Funcao para aumentar o tamanho do array quando o
   * fator de carga for >= 1. O tamanho do array
   * (qtde_buckets) deve ser multiplicado por 8 para
   * que essa operacao seja feita com pouca frequencia.
   * Por fim, precisamos reposicionar as tuplas, considerando
   * que a posicao nesse novo array com maior tamanho
   * sera diferente.
   **/
  void aumentaArray() {
    if (load_factor() < 1) return;

    Tupla<Chave, Valor>** newTupla = (Tupla<Chave, Valor>**)calloc(qtde_buckets * 8, sizeof(Tupla<Chave, Valor>*));

    for (int i = 0; i < qtde_buckets; i++) {
      Tupla<Chave, Valor>* aux = tabela[i];

      if (!aux) continue;

      Tupla<Chave, Valor>* prox = aux->getProx();

      while (prox) {
        inserir(aux->getChave(), aux->getValor(), newTupla);

        free(aux);

        aux = prox;
        prox = aux->getProx();
      }

      inserir(aux->getChave(), aux->getValor(), newTupla);
    }

    free(tabela);

    tabela = newTupla;

    qtde_buckets *= 8;
  }

 public:
  /**
   * Inicializar o array de tuplas com capacidade = qtde_buckets.
   * Lembrar de setar todas as posicoes do array inicializado
   * para NULL.
   **/
  TabelaHash() {
    qtde_buckets = 8;
    tamanho = 0;

    Tupla<Chave, Valor>** newTupla = (Tupla<Chave, Valor>**)calloc(qtde_buckets, sizeof(Tupla<Chave, Valor>*));

    tabela = newTupla;
  }

  /**
   * Essa eh a funcao publica que nos permite inserir
   * uma tupla <c,v> na tabela. Nessa funcao nos
   * verificamos se eh preciso aumentar o array de acordo
   * com o load factor. Essa funcao pode reusar sua versao
   * sobrecarregada para inserir a tupla na tabela.
   * Essa funcao tambem incrementa a quantidade de elementos
   * na tabela (variavel tamanho).
   **/
  void inserir(Chave c, Valor v) {
    if (load_factor() >= 1) aumentaArray();

    inserir(c, v, this->tabela);

    tamanho++;
  }

  /**
   * Essa funcao retorna o fator de carga da Tabela Hash.
   **/
  double load_factor() {
    return (float)tamanho / qtde_buckets;
  }

  /**
   * Ha apenas um valor associado a uma chave.
   * Essa funcao retorna esse valor, caso a chave exista.
   * Se a chave nao existir a funcao retorna NULL.
   * Lembre-se: em caso de colisao, e preciso navegar
   * no bucket (lista ligada) para ter certeza se a chave
   * existe ou nao.
   **/
  Valor getValor(Chave chave) {
    for (int i = 0; i < qtde_buckets; i++) {
      Tupla<Chave, Valor>* aux = tabela[i];

      if (!aux) continue;

      while (aux->getProx()) {
        if (aux->getChave() == chave) return aux->getValor();

        aux = aux->getProx();
      }

      if (aux->getChave() == chave) return aux->getValor();
    }
    return NULL;
  }

  /**
   * Essa funcao retorna true caso a chave exista,
   * false caso contrario.
   * Lembre-se: em caso de colisao, eh preciso navegar
   * no bucket (lista ligada) para ter certeza se a chave
   * existe ou nao.
   **/
  bool contemChave(Chave chave) {
    for (int i = 0; i < qtde_buckets; i++) {
      Tupla<Chave, Valor>* aux = tabela[i];

      if (!aux) continue;

      while (aux->getProx()) {
        if (aux->getChave() == chave) return true;

        aux = aux->getProx();
      }
      if (aux->getChave() == chave) return true;
    }
    return false;
  }

  /**
   * Essa funcao retorna um vetor com todas as chaves
   * ja inseridas na tabela.
   **/
  vector<Chave> getChaves() {
    vector<Chave> chaves;

    for (int i = 0; i < qtde_buckets; i++) {
      Tupla<Chave, Valor>* aux = tabela[i];

      if (!aux) continue;

      while (aux->getProx()) {
        chaves.push_back(aux->getChave());

        aux = aux->getProx();
      }
      chaves.push_back(aux->getChave());
    }

    return chaves;
  }

  /**
   * Essa funcao desaloca os nos previamente alocados, e muda
   * o tamanho do array de tuplas para 8.
   **/
  void clear() {
    for (int i = 0; i < qtde_buckets; i++) {
      Tupla<Chave, Valor>* aux = tabela[i];

      if (!aux) continue;

      Tupla<Chave, Valor>* prox = aux->getProx();

      while (prox) {
        free(aux);

        aux = prox;
        prox = aux->getProx();
      }

      free(aux);
    }
    free(tabela);

    qtde_buckets = 8;
    tamanho = 0;

    Tupla<Chave, Valor>** newTupla = (Tupla<Chave, Valor>**)calloc(qtde_buckets, sizeof(Tupla<Chave, Valor>*));

    tabela = newTupla;
  }

  /**
   * Ha apenas um no associado com uma mesma chave.
   * Essa funcao remove esse no da tabela, caso a chave exista.
   * Se a chave nao existir a funcao nao faz nada.
   * Lembre-se: em caso de colisao, eh preciso navegar
   * no bucket (lista ligada) para ter certeza se a chave
   * existe ou nao.
   * Dica: olhar algoritmo de remocao em lista ligada, pois
   * apos a remocao de um no a lista precisa permanecer integra,
   * ou seja, navegavel.
   **/
  void remover(Chave chave) {
    for (int i = 0; i < qtde_buckets; i++) {
      Tupla<Chave, Valor>* aux = tabela[i];

      if (!aux) continue;

      Tupla<Chave, Valor>* prox = aux->getProx();

      if (aux->getChave() == chave) {
        free(aux);

        tabela[i] = prox;

        tamanho--;

        return;
      }

      while (prox) {
        if (prox->getChave() == chave) {
          aux->setProx(prox->getProx());

          free(prox);

          tamanho--;

          return;
        }
        aux = prox;
        prox = aux->getProx();
      }
    }
  }

  /**
   * Essa funcao retorna a quantidade de pares
   * que ja foram inseridos na Tabela Hash.
   **/
  int size() {
    return tamanho;
  }

  /**
   * Essa funcao retorna o tamanho atual do
   * array usado para armazenar a Tabela Hash.
   **/
  int bucket_count() {
    return qtde_buckets;
  }
};