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
    // // int hash = abs((int)hash<string>{}(v));
    // int codigo_hash = abs((int)hash<Chave>{}(c));
    // int posicao = codigo_hash % qtde_buckets;

    // Tupla<Chave, Valor>* prov = tabela[posicao];
    // Tupla<Chave, Valor> newTupla = Tupla<Chave, Valor>(c, v);

    // if (!prov)

    //   while (prov != NULL) {
    //     prov = prov->getProx
    //   }

    // prov = newTupla;
  }

  /**
   * Fun��o para aumentar o tamanho do array quando o
   * fator de carga for >= 1. O tamanho do array
   * (qtde_buckets) deve ser multiplicado por 8 para
   * que essa opera��o seja feita com pouca frequ�ncia.
   * Por fim, precisamos reposicionar as tuplas, considerando
   * que a posi��o nesse novo array com maior tamanho
   * ser� diferente.
   **/
  void aumentaArray() {
  }

 public:
  /**
   * Inicializar o array de tuplas com capacidade = qtde_buckets.
   * Lembrar de setar todas as posi��es do array inicializado
   * para NULL.
   **/
  TabelaHash() {
    qtde_buckets = 8;
    tamanho = 0;
    tabela = NULL;

    // Tupla<Chave, Valor>** tabela = (Tupla<Chave, Valor>**)calloc(qtde_buckets, sizeof(*Tupla<Chave, Valor>);

    // for (int i = 0; i < 8; i++) tabela[i] = (Tupla<Chave, Valor>*)calloc(1, sizeof(Tupla<Chave, Valor>);
  }

  /**
   * Essa � a fun��o p�blica que nos permite inserir
   * uma tupla <c,v> na tabela. Nessa fun��o n�s
   * verificamos se � preciso aumentar o array de acordo
   * com o load factor. Essa fun��o pode reusar sua vers�o
   * sobrecarregada para inserir a tupla na tabela.
   * Essa fun��o tamb�m incrementa a quantidade de elementos
   * na tabela (vari�vel tamanho).
   **/
  void inserir(Chave c, Valor v) {
    // IMPLEMENTAR
  }

  /**
   * Essa fun��o retorna o fator de carga da Tabela Hash.
   **/
  double load_factor() {
    // IMPLEMENTAR
  }

  /**
   * H� apenas um valor associado a uma chave.
   * Essa fun��o retorna esse valor, caso a chave exista.
   * Se a chave n�o existir a fun��o retorna NULL.
   * Lembre-se: em caso de colis�o, � preciso navegar
   * no bucket (lista ligada) para ter certeza se a chave
   * existe ou n�o.
   **/
  Valor getValor(Chave chave) {
    // IMPLEMENTAR
  }

  /**
   * Essa fun��o retorna true caso a chave exista,
   * false caso contr�rio.
   * Lembre-se: em caso de colis�o, � preciso navegar
   * no bucket (lista ligada) para ter certeza se a chave
   * existe ou n�o.
   **/
  bool contemChave(Chave chave) {
    // IMPLEMENTAR
  }

  /**
   * Essa fun��o retorna um vetor com todas as chaves
   * j� inseridas na tabela.
   **/
  vector<Chave> getChaves() {
    // IMPLEMENTAR
  }

  /**
   * Essa fun��o desaloca os n�s previamente alocados, e muda
   * o tamanho do array de tuplas para 8.
   **/
  void clear() {
    // IMPLEMENTAR
  }

  /**
   * H� apenas um n� associado com uma mesma chave.
   * Essa fun��o remove esse n� da tabela, caso a chave exista.
   * Se a chave n�o existir a fun��o n�o faz nada.
   * Lembre-se: em caso de colis�o, � preciso navegar
   * no bucket (lista ligada) para ter certeza se a chave
   * existe ou n�o.
   * Dica: olhar algoritmo de remo��o em lista ligada, pois
   * ap�s a remo��o de um n� a lista precisa permanecer �ntegra,
   * ou seja, naveg�vel.
   **/
  void remover(Chave chave) {
    // IMPLEMENTAR
  }

  /**
   * Essa fun��o retorna a quantidade de pares
   * que j� foram inseridos na Tabela Hash.
   **/
  int size() {
    return tamanho;
  }

  /**
   * Essa fun��o retorna o tamanho atual do
   * array usado para armazenar a Tabela Hash.
   **/
  int bucket_count() {
    return qtde_buckets;
  }
};