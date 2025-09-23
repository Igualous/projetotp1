#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <string>
#include <cctype>
#include <iostream>
using namespace std;


// ---------- Capacidade ----------
class Capacidade {
private:
    static const int MIN = 1;
    static const int MAX = 4;
    int valor;
    bool validar(int valor);
public:
    bool setValor(int valor);
    int getValor() const;
};
inline int Capacidade::getValor() const { return valor; }


// ---------- Cartao ----------
class Cartao {
private:
    static const int LIMITE = 16;
    string valor;
    bool validar(const string& numero); // Algoritmo de Luhn
public:
    bool setValor(const string& numero);
    string getValor() const;
};
inline string Cartao::getValor() const { return valor; }


// ---------- Codigo ----------
class Codigo {
private:
    static const int LIMITE = 10;
    string valor;
    bool validar(const string& codigo);
public:
    bool setValor(const string& codigo);
    string getValor() const;
};
inline string Codigo::getValor() const { return valor; }


// ---------- Data ----------
class Data {
private:
    string MES;
    int DIA;
    int ANO;
    string valor; // formato "dia-MES-ano", MES em {JAN..DEZ}
    static bool isBissexto(int ano);
    bool validar(int dia, const string& mes, int ano);
public:
    bool setValor(int dia, const string& mes, int ano);
    string getValor() const;
};
inline string Data::getValor() const { return valor; }


// ---------- Dinheiro ----------
class Dinheiro {
private:
    const int MAX = 100000000; // em centavos: R$ 1.000.000,00
    const int MIN = 1;         // em centavos: R$ 0,01
    int valor;                 // armazenado em centavos
    bool validar(int centavos);
public:
    bool setValor(int centavos);
    int getValor() const;      // retorna em centavos
};
inline int Dinheiro::getValor() const { return valor; }


// ---------- Email ----------
class Email {
private:
    static const int LIM_LOCAL = 64;    // limite da parte local (antes do '@')
    static const int LIM_DOMINIO = 255; // limite do domínio (depois do '@')
    string valor;
    bool validar(const string& email);
public:
    bool setValor(const string& email);
    string getValor() const;
};
inline string Email::getValor() const { return valor; }


// ---------- Endereco ----------
class Endereco {
private:
    const int MIN = 5;
    const int MAX = 30;
    string valor;
    bool validar(const string& endereco);
public:
    bool setValor(const string& endereco);
    string getValor() const;
};
inline string Endereco::getValor() const { return valor; }


// ---------- Nome ----------
class Nome {
private:
    const int MIN = 5;
    const int MAX = 20;
    string valor;
    bool validar(const string& nome);
public:
    bool setValor(const string& nome);
    string getValor() const;
};
inline string Nome::getValor() const { return valor; }


// ---------- Numero ----------
class Numero {
private:
    const int MIN = 1;
    const int MAX = 999;
    int valor;
    bool validar(int numero);
public:
    bool setValor(int numero);
    int getValor() const;
};
inline int Numero::getValor() const { return valor; }


// ---------- Ramal ----------
class Ramal {
private:
    const int MIN = 0;
    const int MAX = 50;
    int valor;
    bool validar(int ramal);
public:
    bool setValor(int ramal);
    int getValor() const;
};
inline int Ramal::getValor() const { return valor; }


// ---------- Senha ----------
class Senha {
private:
    const int TAMANHO = 5;
    string valor;
    bool validar(const string& senha);
public:
    bool setValor(const string& senha);
    string getValor() const;
};
inline string Senha::getValor() const { return valor; }


// ---------- Telefone ----------
class Telefone {
private:
    const int TAMANHO = 15;   // '+' + 14 dígitos
    string valor;
    bool validar(const string& telefone);
public:
    bool setValor(const string& telefone);
    string getValor() const;
};
inline string Telefone::getValor() const { return valor; }

#endif // DOMINIOS_HPP_INCLUDED