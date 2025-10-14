#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED

#include "dominios.hpp"

using namespace std;

class Pessoa {
     private:
         Nome nome;
         Email email;
     public:
         void setNome(Nome);
         Nome getNome() const;        
         void setEmail(Email);
         Email getEmail() const; 
}
class Gerente: public Pessoa {
     private:
         Senha senha; 
     public: 
         Ramal ramal;
         void setSenha(Senha);
         Senha getSenha() const;         
         void setRamal(Ramal);
         Ramal getRamal() const;    
};

class Hospede: public Pessoa {
     private: 
         Cartao cartao;
         Endereco endereco;
     public:
         void setCartao(Cartao);
         Cartao getCartao() const;          
         void setEndereco(Endereco);
         Endereco getEndereco() const; 

};

class Reserva {
     private:
         Data chegada;
         Data partida;
         Dinheiro valor;
         Codigo codigo; 
     public:
         void setChegada(Data);
         Data getChegada() const;        
         void setPartida(Data);
         Data getPartida() const;        
         void setValor(Dinheiro);
         Dinheiro getValor() const;
         void setCodigo(Codigo);
         Codigo getCodigo() const; ;
}
class Quarto {
     private:
         Numero numero;
         Capacidade capacidade;
         Dinheiro diaria;
         Ramal ramal;
     public:
         void setNumero(Numero);
         Numero getNumero() const;

         void setCapacidade(Capacidade);
         Capacidade getCapacidade() const; 

         void setDiaria(Dinheiro);
         Dinheiro getDiaria() const; 

         void setRamal(Ramal);
         Ramal getRamal() const; 
}

class Hotel{
     private:
         Nome nome;
         Endereco endereco;
         Telefone telefone;
         Codigo codigo;
     public:
         void setNome(Nome);
         Nome getNome() const;        
         void setEndereco(Endereco);
         Endereco getEndereco() const; 

         void setTelefone(Telefone);
         Telefone getTelefone() const; 

         void setCodigo(Codigo);
         Codigo getCodigo() const; ;
}
#endif // ENTIDADES_HPP_INCLUDED
