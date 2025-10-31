#include "./services/funcoes.hpp"
#include "../entidades.hpp"
#include "../dominios.hpp"
#include <iostream>

using namespace std;


// TELA DE CADASTRO DE USUARIO
Gerente telaCadastro() {
    limpa();
    header();

    string nome, email, senha;
    int ramal;

    cout << "TELA DE CADASTRO DE GERENTE" << endl;
        
    // Recebe os valores como tipos
    Gerente gerente;

    // NOME
    cout << "Nome: ";
    cin >> nome;
    
    Nome nomeDom;
    nomeDom.setValor(nome);
    
    gerente.setNome(nomeDom);

    // EMAIL
    cout << "Email: ";
    cin >> email;


    Email emailDom;
    emailDom.setValor(email);
    
    gerente.setEmail(emailDom);

    // SENHA
    cout << "Senha: ";
    cin >> senha;

    Senha senhaDom;
    senhaDom.setValor(senha);

    gerente.setSenha(senhaDom);

    // RAMAL
    cout << "Ramal: ";
    cin >> ramal;

    Ramal ramalDom;
    ramalDom.setValor(ramal);

    gerente.setRamal(ramalDom);

    return gerente;
}
