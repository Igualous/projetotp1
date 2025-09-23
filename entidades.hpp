#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED

#include "dominios.hpp"

using namespace std;

class Pessoa {
    public:
        Nome nome;
        Email email;
};

class Gerente: public Pessoa {
    private:
        Senha senha; 
    public: 
        Ramal ramal;
        Gerente(string, string);
}

void Gerente::Gerente(string email, string senha) {
    email::setValor(email);
    senha::setValor(senha);
    ramal::setValor(5678);
}

class Hospede: public Pessoa {
    private: 
        Cartao cartao;
    public:
        Endereco endereco;
}



#endif // ENTIDADES_HPP_INCLUDED
