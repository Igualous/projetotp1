#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <string>
#include <cctype>
#include <iostream>
#include <stdexcept>


// ---------- Capacidade ----------
class Capacidade {
    private:
        static const int MIN = 1;
        static const int MAX = 4;
        int valor;
        void validar(int valor);
    public:
        void setValor(int valor);
        int getValor() const;
};
inline int Capacidade::getValor() const { return valor; }


// ---------- Cartao ----------
class Cartao {
    private:
        static const int LIMITE = 16;
        std::string valor;
        void validar(const std::string& numero); // Algoritmo de Luhn
    public:
        void setValor(const std::string& numero);
        std::string getValor() const;
};
inline std::string Cartao::getValor() const { return valor; }


// ---------- Codigo ----------
class Codigo {
    private:
        static const int LIMITE = 10;
        std::string valor;
        void validar(const std::string& codigo);
    public:
        void setValor(const std::string& codigo);
        std::string getValor() const;
};
inline std::string Codigo::getValor() const { return valor; }


// ---------- Data ----------
class Data {
    private:
        std::string MES;
        int DIA;
        int ANO;
        std::string valor; // formato "dia-MES-ano", MES em {JAN..DEZ}
        static bool isBissexto(int ano);
        void validar(int dia, const std::string& mes, int ano);
    public:
        void setValor(int dia, const std::string& mes, int ano);
        std::string getValor() const;
};
inline std::string Data::getValor() const { return valor; }


// ---------- Dinheiro ----------
class Dinheiro {
    private:
        static const int MAX = 100000000; // em centavos: R$ 1.000.000,00
        static const int MIN = 1;         // em centavos: R$ 0,01
        int valor;                 // armazenado em centavos
        void validar(int centavos);
    public:
        void setValor(int centavos);
        int getValor() const;      // retorna em centavos
};
inline int Dinheiro::getValor() const { return valor; }


// ---------- Email ----------
class Email {
    private:
        static const int LIM_LOCAL = 64;    // limite da parte local (antes do '@')
        static const int LIM_DOMINIO = 255; // limite do domínio (depois do '@')
        std::string valor;
        void validar(const std::string& email);
    public:
        void setValor(const std::string& email);
        std::string getValor() const;
};
inline std::string Email::getValor() const { return valor; }


// ---------- Endereco ----------
class Endereco {
    private:
        static const int MIN = 5;
        static const int MAX = 30;
        std::string valor;
        void validar(const std::string& endereco);
    public:
        void setValor(const std::string& endereco);
        std::string getValor() const;
};
inline std::string Endereco::getValor() const { return valor; }


// ---------- Nome ----------
class Nome {
    private:
        static const int MIN = 5;
        static const int MAX = 20;
        std::string valor;
        void validar(const std::string& nome);
    public:
        void setValor(const std::string& nome);
        std::string getValor() const;
};
inline std::string Nome::getValor() const { return valor; }


// ---------- Numero ----------
class Numero {
    private:
        static const int MIN = 1;
        static const int MAX = 999;
        int valor;
        void validar(int numero);
    public:
        void setValor(int numero);
        int getValor() const;
};
inline int Numero::getValor() const { return valor; }


// ---------- Ramal ----------
class Ramal {
    private:
        static const int MIN = 0;
        static const int MAX = 50;
        int valor;
        void validar(int ramal);
    public:
        void setValor(int ramal);
        int getValor() const;
};
inline int Ramal::getValor() const { return valor; }


// ---------- Senha ----------
class Senha {
    private:
        static const int TAMANHO = 5;
        std::string valor;
        void validar(const std::string& senha);
    public:
        void setValor(const std::string& senha);
        std::string getValor() const;
};
inline std::string Senha::getValor() const { return valor; }


// ---------- Telefone ----------
class Telefone {
    private:
        static const int TAMANHO = 15;
        std::string valor;
        void validar(const std::string& telefone);
    public:
        void setValor(const std::string& telefone);
        std::string getValor() const;
};
inline std::string Telefone::getValor() const { return valor; }

#endif // DOMINIOS_HPP_INCLUDED
