/**
 * @file interfaces.hpp
 * @brief Define os contratos da camada de servicos (regras de negocio).
 *
 * A camada de apresentacao conhece apenas estas interfaces, permitindo
 * alternar implementacoes concretas (memoria, banco de dados etc.).
 */
#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include <vector>
#include <optional>
#include <stdexcept>
#include <map>

#include "dominios.hpp"
#include "entidades.hpp"

using std::optional;
using std::vector;

/**
 * @brief Interface de servico para autenticacao de usuarios.
 */
class IServicoAutenticacao {
public:
    /**
     * @brief Valida um par email/senha.
     */
    virtual bool autenticar(const Email& email, const Senha& senha) = 0;

    /**
     * @brief Registra credenciais para uso futuro.
     */
    virtual void cadastrar(const Email& email, const Senha& senha) = 0;

    virtual ~IServicoAutenticacao() = default;
};

/**
 * @brief Interface para manipulacao de gerentes.
 */
class IServicoGerente {
public:
    virtual void criar(const Nome&, const Email&, const Senha&, const Ramal&) = 0;
    virtual optional<Gerente> ler(const Email&) = 0;
    virtual void editar(const Email&, const Nome&, const Senha&, const Ramal&) = 0;
    virtual void excluir(const Email&) = 0;
    virtual vector<Gerente> listar() = 0;
    virtual ~IServicoGerente() = default;
};

/**
 * @brief Interface para manipulacao de hospedes.
 */
class IServicoHospede {
public:
    virtual void cadastrar(const Nome&, const Email&, const Senha&, const Cartao&, const Endereco&) = 0;
    virtual optional<Hospede> ler(const Email&) = 0;
    virtual void editar(const Email&, const Nome&, const Cartao&, const Endereco&) = 0;
    virtual void excluir(const Email&) = 0;
    virtual vector<Hospede> listar() = 0;
    virtual ~IServicoHospede() = default;
};

/**
 * @brief Interface para manipulacao de hoteis.
 */
class IServicoHotel {
public:
    virtual void criar(const Codigo&, const Nome&, const Endereco&, const Telefone&, const Email&) = 0;
    virtual optional<Hotel> ler(const Codigo&) = 0;
    virtual void editar(const Codigo&, const Nome&, const Endereco&, const Telefone&) = 0;
    virtual void excluir(const Codigo&) = 0;
    virtual vector<Hotel> listar() = 0;
    virtual vector<Hotel> listarPorGerente(const Email&) = 0;
    virtual ~IServicoHotel() = default;
};

/**
 * @brief Interface para manipulacao de quartos.
 */
class IServicoQuarto {
public:
    virtual void criar(const Codigo&, const Numero&, const Capacidade&, const Dinheiro&, const Ramal&) = 0;
    virtual optional<Quarto> ler(const Codigo&, const Numero&) = 0;
    virtual void editar(const Codigo&, const Numero&, const Capacidade&, const Dinheiro&, const Ramal&) = 0;
    virtual void excluir(const Codigo&, const Numero&) = 0;
    virtual vector<Quarto> listar(const Codigo&) = 0;
    virtual ~IServicoQuarto() = default;
};

/**
 * @brief Interface para manipulacao de reservas.
 */
class IServicoReserva {
public:
    virtual void criar(const Codigo&, const Codigo&, const Numero&, const Email&, const Data&, const Data&, const Dinheiro&) = 0;
    virtual optional<Reserva> ler(const Codigo&) = 0;
    virtual void editar(const Codigo&, const Data&, const Data&, const Dinheiro&) = 0;
    virtual void excluir(const Codigo&) = 0;
    virtual vector<Reserva> listarPorHotel(const Codigo&) = 0;
    virtual vector<Reserva> listarPorHospede(const Email&) = 0;
    virtual vector<Reserva> listar() = 0;
    virtual ~IServicoReserva() = default;
};

#endif // INTERFACES_HPP_INCLUDED
