#ifndef CONTROLADORAS_HPP_INCLUDED
#define CONTROLADORAS_HPP_INCLUDED

#include "interfaces.hpp"

/**
 * @brief Controladora da Camada de Apresentação para Autenticação.
 */
class CtrlApresentacaoAutenticacao {
private:
    IServicoAutenticacao* servicoAuth; 
public:
    /**
     * @brief Construtor que recebe (injeta) o serviço de autenticação.
     * @param servicoAuth Ponteiro para a implementação de IServicoAutenticacao.
     */
    CtrlApresentacaoAutenticacao(IServicoAutenticacao* servico);
    
    /**
     * @brief Executa o fluxo de apresentação para autenticar um usuário.
     * @return true se o login for bem-sucedido, false caso contrário.
     */
    bool executar(Email& emailAutenticado);
};


/**
 * @brief Controladora da Camada de Apresentação para Hóspede.
 */
class CtrlApresentacaoHospede {
private:
    IServicoHospede* servicoHospede;
public:
    /**
     * @brief Construtor que recebe (injeta) o serviço de hóspede.
     * @param servico Ponteiro para a implementação de IServicoHospede.
     */
    CtrlApresentacaoHospede(IServicoHospede* servico);

    /**
     * @brief Executa o fluxo de apresentação para cadastrar um novo hóspede.
     */
    void executarCadastro();
    
    // Aqui poderiam entrar outros métodos:
    // void executarEdicao();
    // void executarExclusao();
};


/**
 * @brief Controladora da Camada de Apresentação para Hotel.
 */
class CtrlApresentacaoHotel {
private:
    IServicoHotel* servicoHotel; // Ponteiro para o "cardápio" de hotel
public:
    /**
     * @brief Construtor que injeta o serviço de hotel.
     */
    CtrlApresentacaoHotel(IServicoHotel* servico);

    /**
     * @brief Executa o fluxo de apresentação para cadastrar um novo hotel.
     * (Corresponde ao item "3 - CRIAR HOTEL" do diagrama).
     */
    void executarCadastroHotel(const Email& emailGerente);

    /**
     * @brief Lista os hotéis cadastrados.
     */
    void executarListarHoteis(const Email& emailGerente);
};


/**
 * @brief Controladora da Camada de Apresentacao para Gerente.
 */
class CtrlApresentacaoGerente {
private:
    IServicoGerente* servicoGerente;
    IServicoAutenticacao* servicoAuth;
public:
    CtrlApresentacaoGerente(IServicoGerente* servicoGerente,
                            IServicoAutenticacao* servicoAuth);
    
    /**
     * @brief Executa o fluxo de apresentacao para cadastrar um novo gerente.
     */
    void executarCadastro();

    /**
     * @brief Exibe e permite editar o perfil do gerente autenticado.
     */
    void executarPerfil(const Email& emailGerente);
};

#endif // CONTROLADORAS_HPP_INCLUDED
