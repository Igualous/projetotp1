#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include <vector>
#include <optional>
#include <stdexcept>

#include "dominios.hpp"
#include "entidades.hpp"

/**
 * @brief Contrato para autenticação de usuários.
 * Regra: retorna true/false; credenciais inválidas podem lançar std::runtime_error com mensagem amigável.
 */
class IServicoAutenticacao {
public:
    virtual bool autenticar(const Email& email, const Senha& senha) = 0;
    virtual ~IServicoAutenticacao() = default;
};

/**
 * @brief Contrato para gestão de Hóspedes.
 * Chave primária: Email (não editável).
 */
class IServicoHospede {
public:
    /// Cadastra um novo hóspede. Lança se já existir o email.
    virtual void cadastrar(const Nome& nome,
                           const Email& email,
                           const Senha& senha,
                           const Cartao& cartao,
                           const Endereco& endereco) = 0;

    /// Lê um hóspede por email.
    virtual std::optional<Hospede> ler(const Email& email) = 0;

    /// Edita atributos não-chave de um hóspede (nome, cartão, endereço).
    virtual void editar(const Email& emailChave,
                        const Nome& nome,
                        const Cartao& cartao,
                        const Endereco& endereco) = 0;

    /// Exclui um hóspede por email.
    virtual void excluir(const Email& email) = 0;

    /// Lista todos os hóspedes.
    virtual std::vector<Hospede> listar() = 0;

    virtual ~IServicoHospede() = default;
};

/**
 * @brief Contrato para gestão de Hotéis.
 * Chave primária: Código (não editável).
 */
class IServicoHotel {
public:
    virtual void criar(const Codigo& codigo,
                       const Nome& nome,
                       const Endereco& endereco,
                       const Telefone& telefone) = 0;

    virtual std::optional<Hotel> ler(const Codigo& codigo) = 0;

    /// Edita atributos não-chave do hotel.
    virtual void editar(const Codigo& codigo,
                        const Nome& nome,
                        const Endereco& endereco,
                        const Telefone& telefone) = 0;

    virtual void excluir(const Codigo& codigo) = 0;

    virtual std::vector<Hotel> listar() = 0;

    virtual ~IServicoHotel() = default;
};

/**
 * @brief Contrato para gestão de Quartos.
 * Chave composta: (Código do Hotel, Número do Quarto) — não editável.
 */
class IServicoQuarto {
public:
    virtual void criar(const Codigo& codHotel,
                       const Numero& numero,
                       const Capacidade& capacidade,
                       const Dinheiro& diaria,
                       const Ramal& ramal) = 0;

    virtual std::optional<Quarto> ler(const Codigo& codHotel,
                                      const Numero& numero) = 0;

    /// Edita atributos não-chave do quarto.
    virtual void editar(const Codigo& codHotel,
                        const Numero& numero,
                        const Capacidade& capacidade,
                        const Dinheiro& diaria,
                        const Ramal& ramal) = 0;

    virtual void excluir(const Codigo& codHotel,
                         const Numero& numero) = 0;

    /// Lista quartos de um hotel.
    virtual std::vector<Quarto> listar(const Codigo& codHotel) = 0;

    virtual ~IServicoQuarto() = default;
};

/**
 * @brief Contrato para gestão de Reservas.
 * Chave primária: Código da Reserva (não editável).
 * Regra de negócio: impedir sobreposição de períodos no mesmo (hotel, quarto).
 */
class IServicoReserva {
public:
    /// Cria reserva; lança se houver conflito de datas ou entidades inexistentes.
    virtual void criar(const Codigo& codReserva,
                       const Codigo& codHotel,
                       const Numero& numQuarto,
                       const Email& emailHospede,
                       const Data& chegada,
                       const Data& partida,
                       const Dinheiro& valor) = 0;

    virtual std::optional<Reserva> ler(const Codigo& codReserva) = 0;

    virtual void excluir(const Codigo& codReserva) = 0;

    /// Relatórios/consultas úteis:
    virtual std::vector<Reserva> listarPorHotel(const Codigo& codHotel) = 0;
    virtual std::vector<Reserva> listarPorHospede(const Email& email) = 0;

    virtual ~IServicoReserva() = default;
};

#endif // INTERFACES_HPP_INCLUDED
