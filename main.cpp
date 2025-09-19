#include "dominios.hpp"
#include <iostream>
using namespace std;

int main() {
    // ---------- Capacidade ----------
    Capacidade cap;
    cout << "Capacidade 3: " << cap.setValor(3) << endl;    // ok
    cout << "Capacidade 7: " << cap.setValor(7) << endl;    // fail

    // ---------- Cartao ----------
    Cartao cartao;
    cout << "Cartao valido: " 
         << cartao.setValor("4532015112830366") << endl;    // ok (exemplo válido Luhn)
    cout << "Cartao invalido: " 
         << cartao.setValor("1234567890123456") << endl;    // fail

    // ---------- Codigo ----------
    Codigo cod;
    cout << "Codigo valido: " << cod.setValor("abc123def4") << endl;  // ok
    cout << "Codigo invalido: " << cod.setValor("ABC123DEF4") << endl; // fail

    // ---------- Data ----------
    Data data;
    cout << "Data valida: " << data.setValor(29, "FEV", 2024) << endl; // ok (ano bissexto)
    cout << "Data invalida: " << data.setValor(31, "FEV", 2023) << endl; // fail

    // ---------- Dinheiro ----------
    Dinheiro din;
    cout << "Dinheiro valido (100 centavos): " << din.setValor(100) << endl; // ok
    cout << "Dinheiro invalido (0): " << din.setValor(0) << endl;           // fail

    // ---------- Email ----------
    Email email;
    cout << "Email valido: " << email.setValor("joao.silva-23@dominio.com") << endl; // ok
    cout << "Email invalido: " << email.setValor("joao..silva@dominio") << endl;     // fail

    // ---------- Endereco ----------
    Endereco end;
    cout << "Endereco valido: " << end.setValor("Rua 7 de Setembro, 123") << endl; // ok
    cout << "Endereco invalido: " << end.setValor(" RuaInvalida") << endl;         // fail

    // ---------- Nome ----------
    Nome nome;
    cout << "Nome valido: " << nome.setValor("Joao Silva") << endl;  // ok
    cout << "Nome invalido: " << nome.setValor("joao silva") << endl; // fail

    // ---------- Numero ----------
    Numero numero;
    cout << "Numero valido: " << numero.setValor(123) << endl;  // ok
    cout << "Numero invalido: " << numero.setValor(1000) << endl; // fail

    // ---------- Ramal ----------
    Ramal ramal;
    cout << "Ramal valido: " << ramal.setValor(10) << endl;  // ok
    cout << "Ramal invalido: " << ramal.setValor(100) << endl; // fail

    // ---------- Senha ----------
    Senha senha;
    cout << "Senha valida: " << senha.setValor("A1b$?") << endl;  // ok (5 chars, mistura)
    cout << "Senha invalida: " << senha.setValor("abc12") << endl; // fail

    // ---------- Telefone ----------
    Telefone tel;
    cout << "Telefone valido: " << tel.setValor("+12345678901234") << endl;  // ok (15 chars)
    cout << "Telefone invalido: " << tel.setValor("12345678901234") << endl; // fail (sem '+')

    return 0;
}
