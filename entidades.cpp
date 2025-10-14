#include <iostream>
#include "entidades.hpp"
#include <string>

using namespace std;

// ---------  PESSOA  ------------

void Pessoa::setNome(Nome novoNome) {
     this->nome = novoNome;
}

Nome Pessoa::getNome() const {
     return this->nome;
}

void Pessoa::setEmail(Email novoEmail) {
     this->email = novoEmail;
}

Email Pessoa::getEmail() const {
     return this->email;
}

// ---------- GERENTE  ------------

void Gerente::setSenha(Senha novaSenha) {
     this->senha = novaSenha;
}

Senha Gerente::getSenha() const {
     return this->senha;
}

void Gerente::setRamal(Ramal novoRamal) {
     this->ramal = novoRamal;
}

Ramal Gerente::getRamal() const {
     return this->ramal;
}


// ---------- HOSPEDE ---------- 

void Hospede::setCartao(Cartao novoCartao) {
     this->cartao = novoCartao;
}

Cartao Hospede::getCartao() const {
     return this->cartao;
}

void Hospede::setEndereco(Endereco novoEndereco) {
     this->endereco = novoEndereco;
}

Endereco Hospede::getEndereco() const {
     return this->endereco;
}


// ----------  RESERVA  ---------- 

void Reserva::setChegada(Data novaChegada) {
     this->chegada = novaChegada;
}

Data Reserva::getChegada() const {
     return this->chegada;
}

void Reserva::setPartida(Data novaPartida) {
     this->partida = novaPartida;
}

Data Reserva::getPartida() const {
     return this->partida;
}

void Reserva::setValor(Dinheiro novoValor) {
     this->valor = novoValor;
}

Dinheiro Reserva::getValor() const {
     return this->valor;
}

void Reserva::setCodigo(Codigo novoCodigo) {
     this->codigo = novoCodigo;
}

Codigo Reserva::getCodigo() const {
     return this->codigo;
}


// ----------  QUARTO  ---------- 

void Quarto::setNumero(Numero novoNumero) {
     this->numero = novoNumero;
}

Numero Quarto::getNumero() const {
     return this->numero;
}

void Quarto::setCapacidade(Capacidade novaCapacidade) {
     this->capacidade = novaCapacidade;
}

Capacidade Quarto::getCapacidade() const {
     return this->capacidade;
}

void Quarto::setDiaria(Dinheiro novaDiaria) {
     this->diaria = novaDiaria;
}

Dinheiro Quarto::getDiaria() const {
     return this->diaria;
}

void Quarto::setRamal(Ramal novoRamal) {
     this->ramal = novoRamal;
}

Ramal Quarto::getRamal() const {
     return this->ramal;
}


// ----------  HOTEL ---------- 

void Hotel::setNome(Nome novoNome) {
     this->nome = novoNome;
}

Nome Hotel::getNome() const {
     return this->nome;
}

void Hotel::setEndereco(Endereco novoEndereco) {
     this->endereco = novoEndereco;
}

Endereco Hotel::getEndereco() const {
     return this->endereco;
}

void Hotel::setTelefone(Telefone novoTelefone) {
     this->telefone = novoTelefone;
}

Telefone Hotel::getTelefone() const {
     return this->telefone;
}

void Hotel::setCodigo(Codigo novoCodigo) {
     this->codigo = novoCodigo;
}

Codigo Hotel::getCodigo() const {
     return this->codigo;
}