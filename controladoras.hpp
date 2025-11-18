/**
 * @file controladoras.hpp
 * @brief Declara as controladoras da camada de apresentacao (CLI).
 *
 * Cada controladora orquestra o dialogo com o usuario para um contexto
 * especifico (autenticacao, hotel, quarto, reserva etc.).
 */
#ifndef CONTROLADORAS_HPP_INCLUDED
#define CONTROLADORAS_HPP_INCLUDED

#include "interfaces.hpp"
#include <string>

class CtrlApresentacaoQuarto;
class CtrlApresentacaoReserva;

/**
 * @brief Controladora responsavel pelo fluxo de autenticacao.
 */
class CtrlApresentacaoAutenticacao {
private:
    IServicoAutenticacao* servicoAuth;

public:
    explicit CtrlApresentacaoAutenticacao(IServicoAutenticacao* servico);

    /**
     * @brief Solicita email e senha e tenta autenticar o usuario.
     * @param emailAutenticado Recebe o email validado em caso de sucesso.
     * @return true se o login for aceito.
     */
    bool executar(Email& emailAutenticado);
};

/**
 * @brief Controladora para fluxos relacionados a hospedes.
 */
class CtrlApresentacaoHospede {
private:
    IServicoHospede* servicoHospede;
    IServicoAutenticacao* servicoAuth;
    IServicoReserva* servicoReserva;

public:
    CtrlApresentacaoHospede(IServicoHospede* servicoHospede,
                            IServicoAutenticacao* servicoAuth,
                            IServicoReserva* servicoReserva);

    /**
     * @brief Dialogo de cadastro de um novo hospede.
     */
    void executarCadastro();

    /**
     * @brief Dialogo de editar um hospede.
     */
    void executarEditarHospede(const std::string& emailHospede);

    /**
    * @brief Dialogo de editar um hospede.
    */
    void executarExcluirHospede(const std::string& emailHospede);

    /**
     * @brief Listar hospedes com reserva em um hotel especifico
     */
    void executarListarHospedesComReservas(const std::string& codigoHotel);
};

/**
 * @brief Controladora para fluxos relacionados a hoteis.
 */
class CtrlApresentacaoHotel {
private:
    IServicoHotel* servicoHotel;
    CtrlApresentacaoQuarto* ctrlQuarto;
    CtrlApresentacaoHospede* ctrlHospede;

public:
    CtrlApresentacaoHotel(IServicoHotel* servico, CtrlApresentacaoQuarto* ctrlQuarto, CtrlApresentacaoHospede* ctrlHospede);

    void executarCadastroHotel(const Email& emailGerente);
    void executarListarHoteis(const Email& emailGerente);
    void executarEditarHotel(const std::string& codigoHotel);
    void executarExcluirHotel(const std::string& codigoHotel);
};

/**
 * @brief Controladora para fluxos relacionados ao gerente autenticado.
 */
class CtrlApresentacaoGerente {
private:
    IServicoGerente* servicoGerente;
    IServicoAutenticacao* servicoAuth;

public:
    CtrlApresentacaoGerente(IServicoGerente* servicoGerente,
                            IServicoAutenticacao* servicoAuth);

    void executarCadastro();
    void executarPerfil(const Email& emailGerente);
};

/**
 * @brief Controladora para gerenciamento dos quartos de um hotel.
 */
class CtrlApresentacaoQuarto {
private:
    IServicoQuarto* servicoQuarto;
    CtrlApresentacaoReserva* ctrlReserva = nullptr;

public:
    explicit CtrlApresentacaoQuarto(IServicoQuarto* servicoQuarto);
    CtrlApresentacaoQuarto(IServicoQuarto* servicoQuarto, CtrlApresentacaoReserva* ctrlReserva);

    void executar(const std::string& codigoHotel);
    void executarCadastroQuarto(const std::string& codigoHotel);
    void executarListarQuartos(const std::string& codigoHotel);
    void executarEditarQuarto(const std::string& codigoHotel, const int& numeroQuarto);
    void executarExcluirQuarto(const std::string& codigoHotel, const int& numeroQuarto);
};

/**
 * @brief Controladora para operacoes relacionadas a reservas.
 */
class CtrlApresentacaoReserva {
private:
    IServicoReserva* servicoReserva;

public:
    explicit CtrlApresentacaoReserva(IServicoReserva* servicoReserva);

    void executarGerenciar(const std::string& codigoHotel, const int& numeroQuarto);
    void executarCadastroReserva(const std::string& codigoHotel, const int& numeroQuarto);
    void executarListarReservasPorHotel(const std::string& codigoHotel);
    void executarListarReservasPorHospede(const std::string& emailHospedeStr);
    void executarEditarReserva(const std::string& codigoReserva);
    void executarExcluirReserva(const std::string& codigoReserva);
};

#endif // CONTROLADORAS_HPP_INCLUDED
