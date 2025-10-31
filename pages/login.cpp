#include "./services/funcoes.hpp"
#include "../interfaces.hpp"
#include "../dominios.hpp"
#include <iostream>

using namespace std;

// TELA DE LOGIN DE USUARIO
Gerente telaLogin() {
    limpa();
    header();

    cout << "TELA DE LOGIN DE GERENTE" << endl;

    Gerente gerente;
    string email, senha;
    Email emailDom;
    Senha senhaDom;

    cout << "Email: ";
    cin >> email;
    emailDom.setValor(email);

    cout << "Senha: ";
    cin >> senha;
    senhaDom.setValor(email);

    return gerente;
}