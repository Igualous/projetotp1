#include <iostream>
#include "dominios.hpp"
using namespace std;

bool Codigo::validar(int codigo) {
    if (codigo > LIMITE)
    {
            return false;
    } else {
        return true;
    }
}

bool Codigo::setValor(int valor) {
    if (!validar(valor)) {
        return false;
    } else {
        this->valor = valor;
        return true;
            }
}

bool Prioridade::validar(int valor) {
    if (valor == INVALIDO) {
        return false;
    } else {
        return true;
        }
}

bool Prioridade::setValor(int valor) {
    if (!validar(valor)) {
        return false;
    } else {
        this->valor = valor;
        return true;
    }
}
