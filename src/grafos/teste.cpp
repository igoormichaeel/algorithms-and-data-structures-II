// #include <cstdlib>
#include <iostream>
#include <string>

#include "testando.h"

using namespace std;

int main() {
  string s = "Igor";

  Tupla<string, int> t = Tupla<string, int>(s, 23);

  return 0;
}