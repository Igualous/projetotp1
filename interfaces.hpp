#ifndef INTERFACES_HPP_INCLUDED
#define INTERFACES_HPP_INCLUDED

#include "dominios.hpp"
#include "entidades.hpp"
#include <vector>

/**
 * @brief Interface (contrato) para os serviços de autenticação.
 */
class IServicoAutenticacao {
public:
    virtual bool autenticar(const Email& email, const Senha& senha)= 0;

    virtual ~IServicoAutenticacao() {}
};


/**
 * @brief Interface (contrato) para os serviços de gerenciamento de hóspedes.
 */
class IServicoHospede {
public:
    virtual bool cadastrar(Nome nome, Email email, Senha senha, Cartao cartao, Endereco endereco) = 0;

    virtual ~IServicoHospede() {}
};


/**
 * @brief Interface (contrato) para os serviços de gerenciamento de Hotéis e Quartos.
 */
class IServicoHotel {
public:
    /**
     * @brief Destrutor virtual padrão.
     * Necessário porque a classe tem métodos virtuais.
     */

    virtual ~IServicoHotel() {} 

    /**
     * @brief Tenta cadastrar um novo hotel no sistema.
     * @param nome Objeto Nome validado do hotel.
     * @param endereco Objeto Endereco validado do hotel.
     * @param telefone Objeto Telefone validado do hotel.
     * @param codigo Objeto Codigo único validado para o hotel.
     * @return true se o cadastro for bem-sucedido.
     * @throw std::invalid_argument Se um hotel com esse código já existir.
     */
    virtual bool cadastrarHotel(Nome nome, Endereco endereco, Telefone telefone, Codigo codigo) = 0;

    /**
     * @brief Tenta cadastrar um novo quarto em um hotel existente.
     * @param codigoHotel Código do hotel onde o quarto será cadastrado.
     * @param numero Número do quarto a ser cadastrado.
     * @param capacidade Capacidade do quarto.
     * @param diaria Valor da diária do quarto (em centavos).
     * @param ramal Ramal telefônico do quarto.
     * @return true se o cadastro for bem-sucedido.
     * @throw std::invalid_argument Se o hotel com 'codigoHotel' não existir ou se já existir um quarto com esse 'numero' naquele hotel.
     */
    virtual bool cadastrarQuarto(Codigo codigoHotel, Numero numero, Capacidade capacidade, Dinheiro diaria, Ramal ramal) = 0; 

};


/**
 * @brief Interface (contrato) para os serviços de gerenciamento de Reservas.
 */
class IServicoReserva {
public:
    /**
     * @brief Destrutor virtual padrão.
     */
    virtual ~IServicoReserva() {}

    /**
    * @brief Tenta criar uma nova reserva no sistema.
     * @param emailHospede Email do hóspede que está fazendo a reserva.
     * @param codigoHotel Código do hotel onde a reserva será feita.
     * @param numeroQuarto Número do quarto desejado.
     * @param dataChegada Data de início da reserva.
     * @param dataPartida Data de término da reserva.
     * @return O objeto Codigo da reserva criada com sucesso.
     * @throw std::invalid_argument Se o hóspede, hotel ou quarto não existirem,
     * se as datas forem inválidas (partida antes da chegada), ou se o quarto
     * já estiver reservado no período solicitado.
     */

    virtual Codigo criarReserva(const Email& emailHospede, const Codigo& codigoHotel, const Numero& numeroQuarto, const Data& dataChegada, const Data& dataPartida) = 0;

    /**
     * @brief Lista todas as reservas associadas a um determinado hóspede.
     * @param emailHospede Email do hóspede cujas reservas devem ser listadas.
     * @return Um vetor (std::vector) contendo os objetos Reserva do hóspede.
     * Retorna um vetor vazio se o hóspede não tiver reservas.
     * @throw std::invalid_argument Se o hóspede com o email fornecido não for encontrado.
     */

    virtual std::vector<Reserva> listarReservasHospede(const Email& emailHospede) = 0;

    /**
     * @brief Tenta cancelar uma reserva existente no sistema.
     * @param codigoReserva Código da reserva a ser cancelada.
     * @throw std::invalid_argument Se a reserva com o código fornecido não for encontrada
     * ou se não puder ser cancelada (ex: já iniciada - regra de negócio a definir).
     */

    virtual void cancelarReserva(const Codigo& codigoReserva) = 0;
};

// ---------- INTERFACES DE PERSISTÊNCIA (Serviço -> Persistência) ----------

/**
 * @brief Interface (contrato) para a persistência de Hóspedes.
 */
class IPersistenciaHospede {
public:
    virtual ~IPersistenciaHospede() {}
    virtual void salvar(const Hospede& hospede) = 0;
    virtual Hospede buscarPorEmail(const Email& email) = 0;
    virtual void atualizar(const Hospede& hospede) = 0;
    virtual void remover(const Email& email) = 0;
};

/**
 * @brief Interface (contrato) para a persistência de Gerentes.
 */
class IPersistenciaGerente {
public:
    virtual ~IPersistenciaGerente() {}
    virtual Gerente buscarPorEmail(const Email& email) = 0;
    // Métodos salvar/atualizar/remover podem ser adicionados se necessário.
};


/**
 * @brief Interface (contrato) para a persistência de Hotéis e Quartos.
 */
class IPersistenciaHotel {
public:
    virtual ~IPersistenciaHotel() {}
    // Métodos para Hotéis
    virtual void salvarHotel(const Hotel& hotel) = 0;
    virtual Hotel buscarHotelPorCodigo(const Codigo& codigo) = 0;
    virtual void atualizarHotel(const Hotel& hotel) = 0;
    virtual void removerHotel(const Codigo& codigo) = 0;
    // Métodos para Quartos (associados a um Hotel)
    virtual void salvarQuarto(const Codigo& codigoHotel, const Quarto& quarto) = 0;
    virtual Quarto buscarQuartoPorNumero(const Codigo& codigoHotel, const Numero& numero) = 0;
    virtual std::vector<Quarto> listarQuartosHotel(const Codigo& codigoHotel) = 0;
    virtual void atualizarQuarto(const Codigo& codigoHotel, const Quarto& quarto) = 0;
    virtual void removerQuarto(const Codigo& codigoHotel, const Numero& numero) = 0;
};


/**
 * @brief Interface (contrato) para a persistência de Reservas.
 */
class IPersistenciaReserva {
public:
    virtual ~IPersistenciaReserva() {}
    virtual void salvar(const Reserva& reserva) = 0;
    virtual Reserva buscarPorCodigo(const Codigo& codigo) = 0;
    virtual std::vector<Reserva> listarReservasHospede(const Email& emailHospede) = 0;
    virtual std::vector<Reserva> listarReservasQuartoPeriodo(const Codigo& codigoHotel, const Numero& numeroQuarto, const Data& dataChegada, const Data& dataPartida) = 0;
    virtual void remover(const Codigo& codigo) = 0;
};

#endif //INTERFACES_HPP_INCLUDED