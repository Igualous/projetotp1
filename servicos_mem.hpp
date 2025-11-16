/**
 * @file servicos_mem.hpp
 * @brief Implementacoes em memoria dos servicos de aplicacao.
 *
 * Utiliza contenedores da STL para armazenar dados durante a execucao da CLI
 * e serve como referencia para testar as regras de negocio.
 */
#ifndef SERVICOS_MEM_HPP_INCLUDED
#define SERVICOS_MEM_HPP_INCLUDED

#include <map>
#include <vector>
#include <optional>
#include <utility>
#include <string>

#include "interfaces.hpp"
#include "entidades.hpp"

class ServicoReservaMem;
class ServicoQuartoMem;
class ServicoHospedeMem;
class ServicoHotelMem;

using std::optional;
using std::vector;
using std::string;
using std::map;
using std::multimap;
using std::pair;

/**
 * @brief Implementacao simples do servico de autenticacao baseada em memoria.
 */
class ServicoAutenticacaoMem : public IServicoAutenticacao {
    map<string, string> credenciais; ///< email -> senha

public:
    bool autenticar(const Email& email, const Senha& senha) override;
    void cadastrar(const Email& email, const Senha& senha) override;
};

/**
 * @brief Implementacao em memoria do servico de gerentes.
 */
class ServicoGerenteMem : public IServicoGerente {
    map<string, Gerente> gerentes; ///< chaveada pelo email

public:
    void criar(const Nome&, const Email&, const Senha&, const Ramal&) override;
    optional<Gerente> ler(const Email&) override;
    void editar(const Email&, const Nome&, const Senha&, const Ramal&) override;
    void excluir(const Email&) override;
    vector<Gerente> listar() override;
};

/**
 * @brief Implementacao em memoria do servico de hospedes.
 */
class ServicoHospedeMem : public IServicoHospede {
    map<string, Hospede> hospedes;
    ServicoReservaMem* servicoReserva = nullptr;

public:
    void setServicoReserva(ServicoReservaMem*);
    bool existe(const Email&) const;

    void cadastrar(const Nome&, const Email&, const Senha&, const Cartao&, const Endereco&) override;
    optional<Hospede> ler(const Email&) override;
    void editar(const Email&, const Nome&, const Cartao&, const Endereco&) override;
    void excluir(const Email&) override;
    vector<Hospede> listar() override;
};

/**
 * @brief Implementacao em memoria do servico de hoteis.
 */
class ServicoHotelMem : public IServicoHotel {
    map<string, Hotel> hoteis;
    map<string, string> proprietarios; ///< codigo -> email do gerente
    ServicoQuartoMem* servicoQuarto = nullptr;
    ServicoReservaMem* servicoReserva = nullptr;

public:
    ~ServicoHotelMem() override;

    void setServicosRelacionados(ServicoQuartoMem*, ServicoReservaMem*);
    bool existe(const Codigo&) const;

    void criar(const Codigo&, const Nome&, const Endereco&, const Telefone&, const Email&) override;
    optional<Hotel> ler(const Codigo&) override;
    void editar(const Codigo&, const Nome&, const Endereco&, const Telefone&) override;
    void excluir(const Codigo&) override;
    vector<Hotel> listar() override;
    vector<Hotel> listarPorGerente(const Email&) override;
};

/**
 * @brief Implementacao em memoria do servico de quartos.
 */
class ServicoQuartoMem : public IServicoQuarto {
    using ChaveQuarto = pair<string, int>;

    map<ChaveQuarto, Quarto> quartos;
    ServicoReservaMem* servicoReserva = nullptr;

public:
    ~ServicoQuartoMem() override;

    void setServicoReserva(ServicoReservaMem*);
    bool existe(const Codigo&, const Numero&) const;
    bool possuiQuartos(const Codigo&) const;

    void criar(const Codigo&, const Numero&, const Capacidade&, const Dinheiro&, const Ramal&) override;
    optional<Quarto> ler(const Codigo&, const Numero&) override;
    void editar(const Codigo&, const Numero&, const Capacidade&, const Dinheiro&, const Ramal&) override;
    void excluir(const Codigo&, const Numero&) override;
    vector<Quarto> listar(const Codigo&) override;
};

/**
 * @brief Implementacao em memoria do servico de reservas, com indices auxiliares.
 */
class ServicoReservaMem : public IServicoReserva {
    using ChaveQuarto = pair<string, int>;

    map<string, Reserva> reservas;
    multimap<ChaveQuarto, string> idxResPorQuarto;
    multimap<string, string> idxResPorHospede;
    ServicoHotelMem* servicoHotel = nullptr;
    ServicoQuartoMem* servicoQuarto = nullptr;
    ServicoHospedeMem* servicoHospede = nullptr;

    static int mesToNum(const string& mes3);
    static int toOrdinal(const Data& d);
    static bool sobrepoe(const Data& c1, const Data& p1, const Data& c2, const Data& p2);

public:
    void setServicosRelacionados(ServicoHotelMem*, ServicoQuartoMem*, ServicoHospedeMem*);
    bool possuiReservasParaHotel(const Codigo&) const;
    bool possuiReservasParaHospede(const Email&) const;
    bool possuiReservasParaQuarto(const Codigo&, const Numero&) const;

    void criar(const Codigo&, const Codigo&, const Numero&, const Email&, const Data&, const Data&, const Dinheiro&) override;
    optional<Reserva> ler(const Codigo&) override;
    void editar(const Codigo&, const Data&, const Data&, const Dinheiro&) override;
    void excluir(const Codigo&) override;
    vector<Reserva> listarPorHotel(const Codigo&) override;
    vector<Reserva> listarPorHospede(const Email&) override;
    vector<Reserva> listar() override;
};

#endif
