#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include <vector>
#include <optional>
#include <stdexcept>

#include "dominios.hpp"
#include "entidades.hpp"

// ---- Autenticação ----
/**
 * @brief Interface de Serviço para a autenticação de Gerentes.
 */
class IServicoAutenticacao {
public:
    // Retorna um boolean se a autenticação for bem-sucedida.
    virtual bool autenticar(const Email& email, const Senha& senha) = 0; 
    
    virtual ~IServicoAutenticacao() = default;
};

// --- Gerente ---
/**
 * @brief Interface de Serviço para operações de CRUD em Gerentes.
 */
class IServicoPessoal{ 
    public:
        // CRUD Gerente
        virtual bool criar(const Gerente& gerente) = 0; 
        virtual std::optional<Gerente> ler(const Email& email) = 0; 
        virtual bool editar(const Gerente& gerente) = 0; 
        virtual bool excluir(const Email& email) = 0;
        virtual std::vector<Gerente> listarGerentes() = 0;
        
        virtual ~IServicoGerente() = default;
};       

// --- Hóspede, Hotel, Quarto e Reserva (Consolidado em uma única interface) ---
/**
 * @brief Interface de Serviço Única para as entidades Hospede, Hotel, Quarto e Reserva,
 */
class IServicoReserva {
    public:
        // --- HÓSPEDE (CRUD e Listagem) ---
        virtual bool cadastrarHospede(const Hospede& hospede) = 0;
        virtual std::optional<Hospede> lerHospede(const Email& email) = 0; // Leitura pelo PK (Email)
        virtual bool editarHospede(const Hospede& hospede) = 0;
        virtual bool excluirHospede(const Email& email) = 0;
        virtual std::vector<Hospede> listarHospedes() = 0;

        // ---- HOTEL (CRUD e Listagem) ----
        virtual bool criarHotel(const Hotel& hotel) = 0;
        virtual std::optional<Hotel> lerHotel(const Codigo& codigo) = 0;
        virtual bool editarHotel(const Hotel& hotel) = 0;
        virtual bool excluirHotel(const Codigo& codigo) = 0;
        virtual std::vector<Hotel> listarHoteis() = 0;

        // ---- QUARTO (CRUD e Listagem) ----
        // Criação e Edição usando a entidade Quarto completa (DTO)
        virtual bool criarQuarto(const Quarto& quarto) = 0;
        // Leitura pela chave composta
        virtual std::optional<Quarto> lerQuarto(const Codigo& codHotel, const Numero& numero) = 0;
        virtual bool editarQuarto(const Quarto& quarto) = 0;
        // Exclusão pela chave composta
        virtual bool excluirQuarto(const Codigo& codHotel, const Numero& numero) = 0;
        virtual std::vector<Quarto> listarQuartos(const Codigo& codHotel) = 0;

        // --- RESERVA (CRUD e Listagem) ---
        virtual bool criarReserva(const Reserva& reserva) = 0;
        virtual std::optional<Reserva> lerReserva(const Codigo& codReserva) = 0;
        virtual bool editarReserva(const Reserva& reserva) = 0;
        virtual bool excluirReserva(const Codigo& codReserva) = 0;
        virtual std::vector<Reserva> listarReservasPorHotel(const Codigo& codHotel) = 0;
        virtual std::vector<Reserva> listarReservasPorHospede(const Email& email) = 0;

        virtual ~IServicoReserva() = default;
};

#endif // INTERFACES_HPP_INCLUDED
