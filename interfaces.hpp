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

// --- Gerente ---
class IServicoPessoal {
    public:
        virtual void criar(const Nome& nome, const Email& email, const Senha& senha, const Ramal& ramal) = 0;
        virtual std::optional<Gerente> ler(const Email& email) = 0;
        virtual void editar(const Nome& nome, const Senha& senha, const Ramal& ramal) = 0; // nao recebe email pois eh id
        virtual void excluir(const Email& email) = 0;

};       

// --- Reserva ---
class IServicoReserva {
    public:
        // --- Hóspede ---
        virtual void cadastrarHospede(const Nome& nome, const Email& email, const Senha& senha,
                           const Cartao& cartao, const Endereco& endereco) = 0;
        virtual std::optional<Hospede> lerHospede(const Email& email) = 0;
        virtual void editarHospede(const Email& emailChave, const Nome& nome,
                            const Cartao& cartao, const Endereco& endereco) = 0;
        virtual void excluirHospede(const Email& email) = 0;
        virtual std::vector<Hospede> listarHospedes() = 0;

        // ---- Hotel ----
        virtual void criarHotel(const Codigo& codigo, const Nome& nome,
                        const Endereco& endereco, const Telefone& telefone) = 0;
        virtual std::optional<Hotel> lerHotel(const Codigo& codigo) = 0;
        virtual void editarHotel(const Codigo& codigo, const Nome& nome,
                            const Endereco& endereco, const Telefone& telefone) = 0;
        virtual void excluir(const Codigo& codigo) = 0;
        virtual std::vector<Hotel> listarHoteis() = 0;

        // ---- Quarto ----
        virtual void criarQuarto(const Codigo& codHotel, const Numero& numero, const Capacidade& cap,
                        const Dinheiro& diaria, const Ramal& ramal) = 0;
        virtual std::optional<Quarto> lerQuarto(const Codigo& codHotel, const Numero& numero) = 0;
        virtual void editarQuarto(const Codigo& codHotel, const Numero& numero,
                            const Capacidade& cap, const Dinheiro& diaria,
                            const Ramal& ramal) = 0;
        virtual void excluirQuarto(const Codigo& codHotel, const Numero& numero) = 0;
        virtual std::vector<Quarto> listarQuarto(const Codigo& codHotel) = 0;

        // --- Reserva ---
        virtual void criarReserva(const Codigo& codReserva, const Codigo& codHotel, const Numero& numQuarto,
                       const Email& emailHospede, const Data& chegada,
                       const Data& partida, const Dinheiro& valor) = 0;
        virtual std::optional<Reserva> lerReserva(const Codigo& codReserva) = 0;
        virtual void excluirReserva(const Codigo& codReserva) = 0;
        virtual std::vector<Reserva> listarReservaPorHotel(const Codigo& codHotel) = 0;
        virtual std::vector<Reserva> listarReservaPorHospede(const Email& email) = 0;
};

#endif // INTERFACES_HPP_INCLUDED
