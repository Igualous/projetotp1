#ifndef SERVICOS_MEM_HPP_INCLUDED
#define SERVICOS_MEM_HPP_INCLUDED

#include <map>
#include <vector>
#include <optional>
#include <utility>
#include <string>
#include "interfaces.hpp"
#include "entidades.hpp"

// Usando std::
using std::optional;
using std::vector;
using std::string;
using std::map;
using std::multimap;
using std::pair;

class ServicoAutenticacaoMem : public IServicoAutenticacao {
    // demo simples: email -> senha
    map<string, string> credenciais;
public:
    bool autenticar(const Email& email, const Senha& senha) override;
    // helper para testes
    void cadastrar(const Email& e, const Senha& s) { credenciais[e.getValor()] = s.getValor(); }
};

class ServicoHospedeMem : public IServicoHospede {
    map<string, Hospede> hospedes; // chave: email
public:
    void cadastrar(const Nome&, const Email&, const Senha&, const Cartao&, const Endereco&) override;
    optional<Hospede> ler(const Email&) override;
    void editar(const Email&, const Nome&, const Cartao&, const Endereco&) override;
    void excluir(const Email&) override;
    vector<Hospede> listar() override;
};

class ServicoHotelMem : public IServicoHotel {
    map<string, Hotel> hoteis; // chave: codigo
public:
    ~ServicoHotelMem() override; // âncora de vtable
    void criar(const Codigo&, const Nome&, const Endereco&, const Telefone&) override;
    optional<Hotel> ler(const Codigo&) override;
    void editar(const Codigo&, const Nome&, const Endereco&, const Telefone&) override;
    void excluir(const Codigo&) override;
    vector<Hotel> listar() override;
};

class ServicoQuartoMem : public IServicoQuarto {
    using ChaveQuarto = pair<string,int>; // (codHotel, numero)
    map<ChaveQuarto, Quarto> quartos;
public:
    ~ServicoQuartoMem() override; // âncora de vtable
    void criar(const Codigo&, const Numero&, const Capacidade&, const Dinheiro&, const Ramal&) override;
    optional<Quarto> ler(const Codigo&, const Numero&) override;
    void editar(const Codigo&, const Numero&, const Capacidade&, const Dinheiro&, const Ramal&) override;
    void excluir(const Codigo&, const Numero&) override;
    vector<Quarto> listar(const Codigo&) override;
};

class ServicoReservaMem : public IServicoReserva {
    using ChaveQuarto = pair<string,int>;
    map<string, Reserva> reservas;                 // chave: codReserva
    multimap<ChaveQuarto, string> idxResPorQuarto; // (hotel,numero) -> codReserva

    // helpers de data
    static int mesToNum(const string& mes3); // "JAN" -> 1
    static int toOrdinal(const Data& d);          // yyyymmdd
    static bool sobrepoe(const Data& c1, const Data& p1, const Data& c2, const Data& p2);
public:
    void criar(const Codigo&, const Codigo&, const Numero&, const Email&, const Data&, const Data&, const Dinheiro&) override;
    optional<Reserva> ler(const Codigo&) override;
    void excluir(const Codigo&) override;
    vector<Reserva> listarPorHotel(const Codigo&) override;
    vector<Reserva> listarPorHospede(const Email&) override;
};

#endif