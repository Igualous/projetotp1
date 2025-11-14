/**
 * @file dominios.hpp
 * @brief Declara os dominios (value objects) utilizados pelo sistema.
 *
 * Cada classe encapsula regras de validacao especificas, garantindo que os
 * dados avancem para camadas superiores sempre consistentes.
 */
#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

#include <string>
#include <cctype>
#include <iostream>
#include <stdexcept>

/**
 * @brief Dominio que representa a capacidade de um quarto (1 a 4 hospedes).
 */
class Capacidade {
private:
    static const int MIN = 1;
    static const int MAX = 4;
    int valor{};

    void validar(int valor);

public:
    void setValor(int valor);
    int getValor() const;
};
inline int Capacidade::getValor() const { return valor; }

/**
 * @brief Dominio que representa um cartao de credito valido pelo algoritmo de Luhn.
 */
class Cartao {
private:
    static const int LIMITE = 16;
    std::string valor;

    void validar(const std::string& numero);

public:
    void setValor(const std::string& numero);
    std::string getValor() const;
};
inline std::string Cartao::getValor() const { return valor; }

/**
 * @brief Dominio para codigos alfanumericos de 10 caracteres (minusculos/digitos).
 */
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

/**
 * @brief Dominio que representa datas no formato "DD-MES-AAAA".
 */
class Data {
private:
    std::string MES;
    int DIA = 1;
    int ANO = 2000;
    std::string valor;

    static bool isBissexto(int ano);
    void validar(int dia, const std::string& mes, int ano);

public:
    void setValor(int dia, const std::string& mes, int ano);
    std::string getValor() const;
};
inline std::string Data::getValor() const { return valor; }

/**
 * @brief Dominio para valores monetarios armazenados em centavos.
 */
class Dinheiro {
private:
    static const int MAX = 100000000;
    static const int MIN = 1;
    int valor = MIN;

    void validar(int centavos);

public:
    void setValor(int centavos);
    int getValor() const;
};
inline int Dinheiro::getValor() const { return valor; }

/**
 * @brief Dominio que representa enderecos de e-mail.
 */
class Email {
private:
    static const int LIM_LOCAL = 64;
    static const int LIM_DOMINIO = 255;
    std::string valor;

    void validar(const std::string& email);

public:
    void setValor(const std::string& email);
    std::string getValor() const;
};
inline std::string Email::getValor() const { return valor; }

/**
 * @brief Dominio que representa um endereco textual (rua, numero etc.).
 */
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

/**
 * @brief Dominio para nomes proprios entre 5 e 20 caracteres.
 */
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

/**
 * @brief Dominio numerico generico (intervalo 1..999) usado para numeros de quarto.
 */
class Numero {
private:
    static const int MIN = 1;
    static const int MAX = 999;
    int valor = MIN;

    void validar(int numero);

public:
    void setValor(int numero);
    int getValor() const;
};
inline int Numero::getValor() const { return valor; }

/**
 * @brief Dominio para ramais internos (0..50).
 */
class Ramal {
private:
    static const int MIN = 0;
    static const int MAX = 50;
    int valor = MIN;

    void validar(int ramal);

public:
    void setValor(int ramal);
    int getValor() const;
};
inline int Ramal::getValor() const { return valor; }

/**
 * @brief Dominio que representa senhas com regras rigidas de composicao.
 */
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

/**
 * @brief Dominio que representa telefones no formato internacional +DD... (15 chars).
 */
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
