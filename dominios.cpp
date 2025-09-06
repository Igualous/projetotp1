#include <iostream>
#include "dominios.hpp"
using namespace std;

// **** DEFINICAO DAS FUNCOES ****

bool Capacidade::validar(int valor) {
    if (valor >= MIN && valor <= MAX) {
        return true;
    } else {
        return false;
    }
}

bool Cartao::validar(int valor) {
    // A FAZER: ALGORITMO DE LUHN


}

bool Codigo::validar(string valor) {
    if (length(valor) > LIMITE) {
        return false;
    } else {
      // A FAZER
    }
}


