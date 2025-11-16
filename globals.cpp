/**
 * @file globals.cpp
 * @brief Implementa as funcoes globalmente inseridas nas telas do sistema.
 *
 */
#include <cstdlib>
#include <iostream>
#include "globals.hpp"

using namespace std;

/**
 * @brief Limpa a tela de acordo com o sistema operacional.
 */
void limpa() {
    #ifdef _WIN32
        // Comando para limpar o terminal no Windows
        std::system("cls");
    #else
        // Comando para limpar o terminal em sistemas Unix-like (Linux, macOS, etc.)
        std::system("clear");
    #endif
}
/**
 * @brief Cria um cabeçalho padrão para o sistema.
 */
void header() {
    cout << "================================================" << endl;
    cout << "          SISTEMA DE GESTÃO DE HOTÉIS           " << endl;
    cout << "                  TP1 - CIC0197                 " << endl;
    cout << "================================================" << endl;
}

/**
 * @brief Gera uma pequena espera para que o usuario leia as mensagens.
 */
void espera() {
    double cont = 0;
    while (cont < 99999) {
        cont += 0.001;
    }
}