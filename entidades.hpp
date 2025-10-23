/**
 * @file entidades.hpp
 * @brief Declara as entidades do sistema (Pessoa, Gerente, Hospede, Reserva, Quarto, Hotel).
 *
 * Este arquivo contém apenas declarações (interfaces públicas das entidades).
 * As implementações dos métodos ficam em entidades.cpp.
 *
 * @see dominios.hpp
 */

#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED

#include "dominios.hpp"
/**
 * @brief Classe base que representa uma Pessoa.
 *
 * Contém atributos e operações comuns a Gerentes e Hóspedes.
 * Mantém objetos de domínio já validados (Nome, Email).
 */
class Pessoa {
private:
    Nome  nome;   /**< Nome validado do usuário. */
    Email email;  /**< Email validado do usuário. */

public:
    /**
     * @brief Define o nome da pessoa.
     * @param nome Objeto Nome já validado.
     * @throws ValidationError Se o domínio Nome lançar exceção ao validar (RNF 7).
     */
    void setNome(Nome nome);

    /**
     * @brief Retorna o nome da pessoa.
     * @return Objeto Nome atualmente armazenado.
     */
    Nome getNome() const;

    /**
     * @brief Define o email da pessoa.
     * @param email Objeto Email já validado.
     * @throws ValidationError Se o domínio Email lançar exceção ao validar (RNF 7).
     */
    void setEmail(Email email);

    /**
     * @brief Retorna o email da pessoa.
     * @return Objeto Email atualmente armazenado.
     */
    Email getEmail() const;
};
/**
 * @brief Classe entidade que representa um Gerente.
 *
 * Herda de Pessoa e adiciona credenciais de acesso e contato interno.
 * Mantém objetos de domínio já validados (Senha, Ramal).
 */
class Gerente : public Pessoa {
private:
    Senha senha;  /**< Senha de acesso do gerente (domínio validado). */
    Ramal ramal;  /**< Ramal telefônico interno do gerente. */

public:
    /**
     * @brief Define a senha do gerente.
     * @param senha Objeto Senha já validado.
     * @throws ValidationError Se o domínio Senha lançar exceção ao validar (RNF 7).
     */
    void setSenha(Senha senha);

    /**
     * @brief Retorna a senha do gerente.
     * @return Objeto Senha atualmente armazenado.
     */
    Senha getSenha() const;

    /**
     * @brief Define o ramal do gerente.
     * @param ramal Objeto Ramal já validado.
     * @throws ValidationError Se o domínio Ramal lançar exceção ao validar (RNF 7).
     */
    void setRamal(Ramal ramal);

    /**
     * @brief Retorna o ramal do gerente.
     * @return Objeto Ramal atualmente armazenado.
     */
    Ramal getRamal() const;
};


/**
 * @brief Classe entidade que representa um Hóspede.
 *
 * Herda de Pessoa e acrescenta credenciais e dados de pagamento/endereço.
 * Mantém objetos de domínio já validados (Senha, Cartao, Endereco).
 */
class Hospede : public Pessoa {
private:
    Senha    senha;    /**< Senha de acesso do hóspede (domínio validado). */
    Cartao   cartao;   /**< Cartão do hóspede para garantia/pagamento. */
    Endereco endereco; /**< Endereço residencial do hóspede. */

public:
    /**
     * @brief Define a senha do hóspede.
     * @param senha Objeto Senha já validado.
     * @throws ValidationError Se o domínio Senha lançar exceção ao validar (RNF 7).
     */
    void setSenha(Senha senha);

    /**
     * @brief Retorna a senha do hóspede.
     * @return Objeto Senha atualmente armazenado.
     */
    Senha getSenha() const;

    /**
     * @brief Define o cartão do hóspede.
     * @param cartao Objeto Cartao já validado.
     * @throws ValidationError Se o domínio Cartao lançar exceção ao validar (RNF 7).
     */
    void setCartao(Cartao cartao);

    /**
     * @brief Retorna o cartão do hóspede.
     * @return Objeto Cartao atualmente armazenado.
     */
    Cartao getCartao() const;

    /**
     * @brief Define o endereço do hóspede.
     * @param endereco Objeto Endereco já validado.
     * @throws ValidationError Se o domínio Endereco lançar exceção ao validar (RNF 7).
     */
    void setEndereco(Endereco endereco);

    /**
     * @brief Retorna o endereço do hóspede.
     * @return Objeto Endereco atualmente armazenado.
     */
    Endereco getEndereco() const;
};

/**
 * @brief Classe entidade que representa uma Reserva.
 *
 * Modela uma reserva com período (chegada/partida), valor e um código identificador.
 * Mantém objetos de domínio já validados (Data, Dinheiro, Codigo).
 */
class Reserva {
private:
    Data     chegada; /**< Data de check-in da reserva. */
    Data     partida; /**< Data de check-out da reserva. */
    Dinheiro valor;   /**< Valor total (em centavos) da reserva. */
    Codigo   codigo;  /**< Código identificador da reserva. */

public:
    /**
     * @brief Define a data de chegada (check-in).
     * @param chegada Objeto Data já validado.
     * @throws ValidationError Se o domínio Data lançar exceção ao validar (RNF 7).
     */
    void setChegada(Data chegada);

    /**
     * @brief Retorna a data de chegada (check-in).
     * @return Objeto Data atualmente armazenado.
     */
    Data getChegada() const;

    /**
     * @brief Define a data de partida (check-out).
     * @param partida Objeto Data já validado.
     * @throws ValidationError Se o domínio Data lançar exceção ao validar (RNF 7).
     */
    void setPartida(Data partida);

    /**
     * @brief Retorna a data de partida (check-out).
     * @return Objeto Data atualmente armazenado.
     */
    Data getPartida() const;

    /**
     * @brief Define o valor total da reserva.
     * @param valor Objeto Dinheiro já validado (centavos).
     * @throws ValidationError Se o domínio Dinheiro lançar exceção ao validar (RNF 7).
     */
    void setValor(Dinheiro valor);

    /**
     * @brief Retorna o valor total da reserva.
     * @return Objeto Dinheiro atualmente armazenado.
     */
    Dinheiro getValor() const;

    /**
     * @brief Define o código identificador da reserva.
     * @param codigo Objeto Codigo já validado.
     * @throws ValidationError Se o domínio Codigo lançar exceção ao validar (RNF 7).
     */
    void setCodigo(Codigo codigo);

    /**
     * @brief Retorna o código identificador da reserva.
     * @return Objeto Codigo atualmente armazenado.
     */
    Codigo getCodigo() const;
};

/**
 * @brief Classe entidade que representa um Quarto de hotel.
 *
 * Mantém atributos de identificação, capacidade, diária e contato interno.
 * Utiliza objetos de domínio já validados (Numero, Capacidade, Dinheiro, Ramal).
 */
class Quarto {
private:
    Numero     numero;     /**< Número identificador do quarto. */
    Capacidade capacidade; /**< Capacidade máxima de hóspedes. */
    Dinheiro   diaria;     /**< Valor da diária (em centavos). */
    Ramal      ramal;      /**< Ramal interno do quarto (se aplicável). */

public:
    /**
     * @brief Define o número do quarto.
     * @param numero Objeto Numero já validado.
     * @throws ValidationError Se o domínio Numero lançar exceção ao validar (RNF 7).
     */
    void setNumero(Numero numero);

    /**
     * @brief Retorna o número do quarto.
     * @return Objeto Numero atualmente armazenado.
     */
    Numero getNumero() const;

    /**
     * @brief Define a capacidade do quarto.
     * @param capacidade Objeto Capacidade já validado.
     * @throws ValidationError Se o domínio Capacidade lançar exceção ao validar (RNF 7).
     */
    void setCapacidade(Capacidade capacidade);

    /**
     * @brief Retorna a capacidade do quarto.
     * @return Objeto Capacidade atualmente armazenado.
     */
    Capacidade getCapacidade() const;

    /**
     * @brief Define o valor da diária.
     * @param diaria Objeto Dinheiro já validado (centavos).
     * @throws ValidationError Se o domínio Dinheiro lançar exceção ao validar (RNF 7).
     */
    void setDiaria(Dinheiro diaria);

    /**
     * @brief Retorna o valor da diária.
     * @return Objeto Dinheiro atualmente armazenado.
     */
    Dinheiro getDiaria() const;

    /**
     * @brief Define o ramal interno do quarto.
     * @param ramal Objeto Ramal já validado.
     * @throws ValidationError Se o domínio Ramal lançar exceção ao validar (RNF 7).
     */
    void setRamal(Ramal ramal);

    /**
     * @brief Retorna o ramal interno do quarto.
     * @return Objeto Ramal atualmente armazenado.
     */
    Ramal getRamal() const;
};

/**
 * @brief Classe entidade que representa um Hotel.
 *
 * Mantém identificação, endereço, telefone e um código único.
 * Utiliza objetos de domínio já validados (Nome, Endereco, Telefone, Codigo).
 */
class Hotel {
private:
    Nome     nome;     /**< Nome oficial do hotel. */
    Endereco endereco; /**< Endereço do hotel. */
    Telefone telefone; /**< Telefone de contato principal. */
    Codigo   codigo;   /**< Código identificador interno/externo do hotel. */

public:
    /**
     * @brief Define o nome do hotel.
     * @param nome Objeto Nome já validado.
     * @throws ValidationError Se o domínio Nome lançar exceção ao validar (RNF 7).
     */
    void setNome(Nome nome);

    /**
     * @brief Retorna o nome do hotel.
     * @return Objeto Nome atualmente armazenado.
     */
    Nome getNome() const;

    /**
     * @brief Define o endereço do hotel.
     * @param endereco Objeto Endereco já validado.
     * @throws ValidationError Se o domínio Endereco lançar exceção ao validar (RNF 7).
     */
    void setEndereco(Endereco endereco);

    /**
     * @brief Retorna o endereço do hotel.
     * @return Objeto Endereco atualmente armazenado.
     */
    Endereco getEndereco() const;

    /**
     * @brief Define o telefone do hotel.
     * @param telefone Objeto Telefone já validado.
     * @throws ValidationError Se o domínio Telefone lançar exceção ao validar (RNF 7).
     */
    void setTelefone(Telefone telefone);

    /**
     * @brief Retorna o telefone do hotel.
     * @return Objeto Telefone atualmente armazenado.
     */
    Telefone getTelefone() const;

    /**
     * @brief Define o código identificador do hotel.
     * @param codigo Objeto Codigo já validado.
     * @throws ValidationError Se o domínio Codigo lançar exceção ao validar (RNF 7).
     */
    void setCodigo(Codigo codigo);

    /**
     * @brief Retorna o código identificador do hotel.
     * @return Objeto Codigo atualmente armazenado.
     */
    Codigo getCodigo() const;
};

#endif // ENTIDADES_HPP_INCLUDED
