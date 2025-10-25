#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include <vector>
#include <optional>
#include <stdexcept>

#include "dominios.hpp"
#include "entidades.hpp"

// ---- Autenticação ----
class IServicoAutenticacao {
public:
    virtual bool autenticar(const Email& email, const Senha& senha) = 0;
    virtual ~IServicoAutenticacao() = default;
};

// ---- Hóspede ----
class IServicoHospede {
public:
    virtual void cadastrar(const Nome& nome, const Email& email, const Senha& senha,
                           const Cartao& cartao, const Endereco& endereco) = 0;
    virtual std::optional<Hospede> ler(const Email& email) = 0;
    virtual void editar(const Email& emailChave, const Nome& nome,
                        const Cartao& cartao, const Endereco& endereco) = 0;
    virtual void excluir(const Email& email) = 0;
    virtual std::vector<Hospede> listar() = 0;
    virtual ~IServicoHospede() = default;
};

// ---- Hotel ----
class IServicoHotel {
public:
    virtual void criar(const Codigo& codigo, const Nome& nome,
                       const Endereco& endereco, const Telefone& telefone) = 0;
    virtual std::optional<Hotel> ler(const Codigo& codigo) = 0;
    virtual void editar(const Codigo& codigo, const Nome& nome,
                        const Endereco& endereco, const Telefone& telefone) = 0;
    virtual void excluir(const Codigo& codigo) = 0;
    virtual std::vector<Hotel> listar() = 0;
    virtual ~IServicoHotel() = default;
};

// ---- Quarto ----
class IServicoQuarto {
public:
    virtual void criar(const Codigo& codHotel, const Numero& numero, const Capacidade& cap,
                       const Dinheiro& diaria, const Ramal& ramal) = 0;
    virtual std::optional<Quarto> ler(const Codigo& codHotel, const Numero& numero) = 0;
    virtual void editar(const Codigo& codHotel, const Numero& numero,
                        const Capacidade& cap, const Dinheiro& diaria,
                        const Ramal& ramal) = 0;
    virtual void excluir(const Codigo& codHotel, const Numero& numero) = 0;
    virtual std::vector<Quarto> listar(const Codigo& codHotel) = 0;
    virtual ~IServicoQuarto() = default;
};

// ---- Reserva ----
class IServicoReserva {
public:
    virtual void criar(const Codigo& codReserva, const Codigo& codHotel, const Numero& numQuarto,
                       const Email& emailHospede, const Data& chegada,
                       const Data& partida, const Dinheiro& valor) = 0;
    virtual std::optional<Reserva> ler(const Codigo& codReserva) = 0;
    virtual void excluir(const Codigo& codReserva) = 0;
    virtual std::vector<Reserva> listarPorHotel(const Codigo& codHotel) = 0;
    virtual std::vector<Reserva> listarPorHospede(const Email& email) = 0;
    virtual ~IServicoReserva() = default;
};

#endif // INTERFACES_HPP_INCLUDED
