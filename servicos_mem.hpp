#ifndef SERVICOS_MEM_HPP_INCLUDED
#define SERVICOS_MEM_HPP_INCLUDED

#include <map>
#include <vector>
#include <optional>
#include <utility>
#include <string>
#include "interfaces.hpp"

class ServicoAutenticacaoMem : public IServicoAutenticacao {
    // demo simples: email -> senha
    std::map<std::string, std::string> credenciais;
public:
    bool autenticar(const Email& email, const Senha& senha) override;
    // helper para testes
    void cadastrar(const Email& e, const Senha& s) { credenciais[e.getValor()] = s.getValor(); }
};

class ServicoHospedeMem : public IServicoHospede {
    std::map<std::string, Hospede> hospedes; // chave: email
public:
    void cadastrar(const Nome&, const Email&, const Senha&, const Cartao&, const Endereco&) override;
    std::optional<Hospede> ler(const Email&) override;
    void editar(const Email&, const Nome&, const Cartao&, const Endereco&) override;
    void excluir(const Email&) override;
    std::vector<Hospede> listar() override;
};

class ServicoHotelMem : public IServicoHotel {
    std::map<std::string, Hotel> hoteis; // chave: codigo
public:
    ~ServicoHotelMem() override; // âncora de vtable
    void criar(const Codigo&, const Nome&, const Endereco&, const Telefone&) override;
    std::optional<Hotel> ler(const Codigo&) override;
    void editar(const Codigo&, const Nome&, const Endereco&, const Telefone&) override;
    void excluir(const Codigo&) override;
    std::vector<Hotel> listar() override;
};

class ServicoQuartoMem : public IServicoQuarto {
    using ChaveQuarto = std::pair<std::string,int>; // (codHotel, numero)
    std::map<ChaveQuarto, Quarto> quartos;
public:
    ~ServicoQuartoMem() override; // âncora de vtable
    void criar(const Codigo&, const Numero&, const Capacidade&, const Dinheiro&, const Ramal&) override;
    std::optional<Quarto> ler(const Codigo&, const Numero&) override;
    void editar(const Codigo&, const Numero&, const Capacidade&, const Dinheiro&, const Ramal&) override;
    void excluir(const Codigo&, const Numero&) override;
    std::vector<Quarto> listar(const Codigo&) override;
};

class ServicoReservaMem : public IServicoReserva {
    using ChaveQuarto = std::pair<std::string,int>;
    std::map<std::string, Reserva> reservas;                 // chave: codReserva
    std::multimap<ChaveQuarto, std::string> idxResPorQuarto; // (hotel,numero) -> codReserva

    // helpers de data
    static int mesToNum(const std::string& mes3); // "JAN" -> 1
    static int toOrdinal(const Data& d);          // yyyymmdd
    static bool sobrepoe(const Data& c1, const Data& p1, const Data& c2, const Data& p2);
public:
    void criar(const Codigo&, const Codigo&, const Numero&, const Email&, const Data&, const Data&, const Dinheiro&) override;
    std::optional<Reserva> ler(const Codigo&) override;
    void excluir(const Codigo&) override;
    std::vector<Reserva> listarPorHotel(const Codigo&) override;
    std::vector<Reserva> listarPorHospede(const Email&) override;
};

#endif
