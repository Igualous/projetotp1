#include <cstdlib>
#include <iostream>
#include "funcoes.hpp"

using namespace std;

// FUNCAO DE LIMPAR TERMINAL INDEPENDENTE DO SO
void limpa() {
    #ifdef _WIN32
        // Comando para limpar o terminal no Windows
        std::system("cls");
    #else
        // Comando para limpar o terminal em sistemas Unix-like (Linux, macOS, etc.)
        std::system("clear");
    #endif
}

void header() {
    cout << "================================================" << endl;
    cout << "          SISTEMA DE GESTÃO DE HOTÉIS           " << endl;
    cout << "                  TP1 - CIC0197                 " << endl;
    cout << "================================================" << endl;
}

int menuInicial() {
    limpa();
    header();

    cout << "SELECIONE O QUE DESEJA FAZER:" << endl;
    cout << "1 - CADASTRO" << endl;
    cout << "2 - LOGIN" << endl;
    cout << "3 - SAIR" << endl;

    int acao;
    cin >> acao;

    return acao;
} 

int menuPrincipal() {
    limpa();
    header();
    
    cout << "SELECIONE O QUE DESEJA FAZER:" << endl;
    cout << "1 - MEU PERFIL" << endl;
    cout << "2 - RESERVAS" << endl;
    cout << "3 - SAIR" << endl;

    int acao;
    cin >> acao;

    return acao;
} 