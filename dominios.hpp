#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <string>
#include <cctype>
#include <iostream>
using namespace std;

class Capacidade {
    private:
        static const int MIN = 1;
        static const int MAX = 4;
        int valor;
        bool validar(int);
    public:
        bool setValor(int);
        int getValor();
};


inline int Capacidade::getValor() {
    return valor;
}

class Cartao {
    private:
        static const int LIMITE = 16;
        string valor;
        bool validar(string); // algoritmo de Luhn
    public:
        bool setValor(string);
        string getValor();
};

inline string Cartao::getValor() {
    return valor;
}

class Codigo {
    private:
        static const int LIMITE = 10;
        string valor;
        bool validar(string);
    public:
        bool setValor(string);
        string getValor();
};

inline string Codigo::getValor() {
    return valor;
}

class Data {
    private:
        string MES;
        int DIA;
        int ANO;
        string valor;
        bool isBisexto(int);
        bool validar(int, string, int);
    public:
        bool setValor(int, string, int);
        string getValor();
};

inline string Data::getValor() {
    return valor;
}

class Dinheiro {
    private:
        const int MAX = 1000000;
        const int MIN = 1;
        int valor;
        bool validar(int);
    public:
        bool setValor(int);
        int getValor();
};

inline int Dinheiro::getValor() {
    return valor;
}

class Email {
    private:
        static const int LIM = 64;
        string valor;
        bool validar(string);
    public:
        bool setValor(string);
        string getValor();
};

inline string Email::getValor() {
    return valor;
}

class Endereco {
    private:
        const int MIN = 5;
        const int MAX = 30;
        string valor;
        bool validar(string);
    public:
        bool setValor(string);
        string getValor();
};

inline string Endereco::getValor() {
    return valor;
}

class Nome {
    private:
        const int MIN = 5;
        const int MAX = 20;
        string valor;
        bool validar(string); 
    public:
        bool setValor(string);
        string getValor();
};

inline string Nome::getValor() {
    return valor;
}

class Numero {
   private:
        const int MIN = 1;
        const int MAX = 999;
        int valor;
        bool validar(int);

   public:
        bool setValor(int);
        int getValor(int); 
};

inline int Numero::getValor() {
    return valor;
}

class Ramal {
    private:
        const int MIN = 0;
        const int MAX = 50;
        int valor;
        bool validar(int);
    public:
        bool setValor(int);
        int getValor();
};

inline int Ramal::getValor() {
    return valor;
}

class Senha {
    private:
        const int TAMANHO = 5;
        string valor;
        bool validar(string);
    public:
        bool setValor(string);
        string getValor();
};

inline string Senha::getValor() {
    return valor;
}

class Telefone {
    private:
        const int TAMANHO = 15;
        int valor;
        bool validar(int);
    public:
        bool setValor(int);
        int getValor();
};

inline int Telefone::getValor() {
    return valor;
}

#endif //DOMINIOS_HPP_INCLUDED