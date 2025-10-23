#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include "dominios.hpp"

/**
 * @brief Interface (contrato) para os serviços de autenticação.
 */
class IServicoAutenticacao {
public:
    virtual bool autenticar(const Email& email, const Senha& senha) = 0;
    virtual ~IServicoAutenticacao() {}
};

/**
 * @brief Interface (contrato) para os serviços de gerenciamento de hóspedes.
 */
class IServicoHospede {
public:
    virtual bool cadastrar(Nome nome, Email email, Senha senha, Cartao cartao, Endereco endereco) = 0;
    virtual ~IServicoHospede() {}
};

/**
 * @brief Interface (contrato) para os serviços de gerenciamento de Hotéis e Quartos.
 */
class IServicoHotel {
public:
    /**
     * @brief Destrutor virtual padrão.
     * Necessário porque a classe tem métodos virtuais.
     */
    virtual ~IServicoHotel() {} // <-- O destrutor pertence à CLASSE, não aos métodos.

    /**
     * @brief Tenta cadastrar um novo hotel no sistema.
     * @param nome Objeto Nome validado do hotel.
     * @param endereco Objeto Endereco validado do hotel.
     * @param telefone Objeto Telefone validado do hotel.
     * @param codigo Objeto Codigo único validado para o hotel.
     * @return true se o cadastro for bem-sucedido.
     * @throw std::invalid_argument Se um hotel com esse código já existir.
     */
    virtual bool cadastrarHotel(Nome nome, Endereco endereco, Telefone telefone, Codigo codigo) = 0;

    /**
     * @brief Tenta cadastrar um novo quarto em um hotel existente.
     * @param codigoHotel Código do hotel onde o quarto será cadastrado. <-- CORRIGIDO
     * @param numero Número do quarto a ser cadastrado.
     * @param capacidade Capacidade do quarto.
     * @param diaria Valor da diária do quarto (em centavos). <-- CORRIGIDO
     * @param ramal Ramal telefônico do quarto.
     * @return true se o cadastro for bem-sucedido.
     * @throw std::invalid_argument Se o hotel com 'codigoHotel' não existir ou se já existir um quarto com esse 'numero' naquele hotel.
     */
    virtual bool cadastrarQuarto(Codigo codigoHotel, Numero numero, Capacidade capacidade, Dinheiro diaria, Ramal ramal) = 0; // <-- CORRIGIDO: É um método DENTRO da classe.
};


#endif //INTERFACES_HPP_INCLUDED