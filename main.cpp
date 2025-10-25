#include "dominios.hpp"
#include "entidades.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void testar(const string& nomeTeste, bool sucesso) {
    cout << "  " << (sucesso ? "[PASSOU]" : "[FALHOU]") << " : " << nomeTeste << endl;
}

int main() {
    cout << "--- Iniciando Testes de Dominio ---" << endl;

    // ---------- Capacidade ----------
    cout << "\n[Testando Dominio: Capacidade]" << endl;
    Capacidade cap;
    try {
        cap.setValor(3);
        testar("Atribuir valor valido (3)", cap.getValor() == 3);
    } catch (const invalid_argument& e) { testar("Atribuir valor valido (3)", false); }
    
    try {
        cap.setValor(7); // Deve lançar exceção
        testar("Atribuir valor invalido (7)", false);
    } catch (const invalid_argument& e) {
        testar("Atribuir valor invalido (7)", true);
        cout << "    -> Msg: " << e.what() << endl;
    }

    // ---------- Cartao ----------
    cout << "\n[Testando Dominio: Cartao]" << endl;
    Cartao cartao;
    try {
        cartao.setValor("4532015112830366");
        testar("Atribuir cartao valido (Luhn)", true);
    } catch (const invalid_argument& e) { 
        testar("Atribuir cartao valido (Luhn)", false); 
        cout << "    -> Msg: " << e.what() << endl;
    }
    
    try {
        cartao.setValor("1234567890123456"); // Luhn inválido
        testar("Atribuir cartao invalido (Luhn)", false);
    } catch (const invalid_argument& e) {
        testar("Atribuir cartao invalido (Luhn)", true);
        cout << "    -> Msg: " << e.what() << endl;
    }

    // ---------- Codigo ----------
    cout << "\n[Testando Dominio: Codigo]" << endl;
    Codigo cod;
    try {
        cod.setValor("abc123def4");
        testar("Atribuir codigo valido (abc123def4)", true);
    } catch (const invalid_argument& e) { testar("Atribuir codigo valido (abc123def4)", false); }
    
    try {
        cod.setValor("ABC123DEF4"); // Inválido (maiúsculas)
        testar("Atribuir codigo invalido (ABC123DEF4)", false);
    } catch (const invalid_argument& e) {
        testar("Atribuir codigo invalido (ABC123DEF4)", true);
        cout << "    -> Msg: " << e.what() << endl;
    }

    // ---------- Data ----------
    cout << "\n[Testando Dominio: Data]" << endl;
    Data data;
    try {
        data.setValor(29, "FEV", 2024);
        testar("Atribuir data valida (29/FEV/2024)", true);
    } catch (const invalid_argument& e) { testar("Atribuir data valida (29/FEV/2024)", false); }
    
    try {
        data.setValor(31, "FEV", 2023); // Dia inválido
        testar("Atribuir data invalida (31/FEV/2023)", false);
    } catch (const invalid_argument& e) {
        testar("Atribuir data invalida (31/FEV/2023)", true);
        cout << "    -> Msg: " << e.what() << endl;
    }

    // ---------- Dinheiro ----------
    cout << "\n[Testando Dominio: Dinheiro]" << endl;
    Dinheiro din;
    try {
        din.setValor(100); // R$ 1,00
        testar("Atribuir dinheiro valido (100)", true);
    } catch (const invalid_argument& e) { testar("Atribuir dinheiro valido (100)", false); }

    try {
        din.setValor(0); // Inválido (min é 1)
        testar("Atribuir dinheiro invalido (0)", false);
    } catch (const invalid_argument& e) {
        testar("Atribuir dinheiro invalido (0)", true);
        cout << "    -> Msg: " << e.what() << endl;
    }

    // ---------- Email ----------
    cout << "\n[Testando Dominio: Email]" << endl;
    Email email;
    try {
        email.setValor("joao.silva-23@dominio.com");
        testar("Atribuir email valido", true);
    } catch (const invalid_argument& e) { testar("Atribuir email valido", false); }

    try {
        email.setValor("joao..silva@dominio"); // Ponto duplo
        testar("Atribuir email invalido (..)", false);
    } catch (const invalid_argument& e) {
        testar("Atribuir email invalido (..)", true);
        cout << "    -> Msg: " << e.what() << endl;
    }

    // ---------- Endereco ----------
    cout << "\n[Testando Dominio: Endereco]" << endl;
    Endereco end;
    try {
        end.setValor("Rua 7 de Setembro, 123");
        testar("Atribuir endereco valido", true);
    } catch (const invalid_argument& e) { testar("Atribuir endereco valido", false); }

    try {
        end.setValor(" Rua"); // Começa com espaço e é curto
        testar("Atribuir endereco invalido ( Rua)", false);
    } catch (const invalid_argument& e) {
        testar("Atribuir endereco invalido ( Rua)", true);
        cout << "    -> Msg: " << e.what() << endl;
    }
    
    // ---------- Nome ----------
    cout << "\n[Testando Dominio: Nome]" << endl;
    Nome nome;
    try {
        nome.setValor("Joao Da Silva");
        testar("Atribuir nome valido (Joao Da Silva)", true);
    } catch (const invalid_argument& e) { testar("Atribuir nome valido (Joao Da Silva)", false); }

    try {
        nome.setValor("joao silva"); // minúsculas
        testar("Atribuir nome invalido (joao silva)", false);
    } catch (const invalid_argument& e) {
        testar("Atribuir nome invalido (joao silva)", true);
        cout << "    -> Msg: " << e.what() << endl;
    }
    
    // ---------- Numero ----------
    cout << "\n[Testando Dominio: Numero]" << endl;
    Numero num;
    try {
        num.setValor(999);
        testar("Atribuir numero valido (999)", true);
    } catch (const invalid_argument& e) { testar("Atribuir numero valido (999)", false); }

    try {
        num.setValor(1000); // Fora do limite
        testar("Atribuir numero invalido (1000)", false);
    } catch (const invalid_argument& e) {
        testar("Atribuir numero invalido (1000)", true);
        cout << "    -> Msg: " << e.what() << endl;
    }

    // ---------- Ramal ----------
    cout << "\n[Testando Dominio: Ramal]" << endl;
    Ramal ramal;
    try {
        ramal.setValor(0);
        testar("Atribuir ramal valido (0)", true);
    } catch (const invalid_argument& e) { testar("Atribuir ramal valido (0)", false); }

    try {
        ramal.setValor(51); // Fora do limite
        testar("Atribuir ramal invalido (51)", false);
    } catch (const invalid_argument& e) {
        testar("Atribuir ramal invalido (51)", true);
        cout << "    -> Msg: " << e.what() << endl;
    }
    
    // ---------- Senha ----------
    cout << "\n[Testando Dominio: Senha]" << endl;
    Senha senha;
    try {
        senha.setValor("A1b$?");
        testar("Atribuir senha valida (A1b$?)", true);
    } catch (const invalid_argument& e) { 
        testar("Atribuir senha valida (A1b$?)", false);
        cout << "    -> Msg: " << e.what() << endl;
    }

    try {
        senha.setValor("abc12"); // Faltando maiúscula e especial
        testar("Atribuir senha invalida (abc12)", false);
    } catch (const invalid_argument& e) {
        testar("Atribuir senha invalida (abc12)", true);
        cout << "    -> Msg: " << e.what() << endl;
    }

    // ---------- Telefone ----------
    cout << "\n[Testando Dominio: Telefone]" << endl;
    Telefone tel;
    try {
        tel.setValor("+12345678901234");
        testar("Atribuir telefone valido", true);
    } catch (const invalid_argument& e) { testar("Atribuir telefone valido", false); }

    try {
        tel.setValor("12345678901234"); // Faltando '+'
        testar("AtribuB ir telefone invalido (sem +)", false);
    } catch (const invalid_argument& e) {
        testar("Atribuir telefone invalido (sem +)", true);
        cout << "    -> Msg: " << e.what() << endl;
    }

    cout << "\n--- Testes de Dominio Concluidos ---" << endl;
    cout << "\n --- Testes de Relacionamentos --- " << endl;

    Gerente gerente1;
    gerente1.setNome(nome);

    Hotel hotel1;
    hotel1.setGerente(&gerente1);
    hotel1.setCodigo(cod);

    Quarto quarto1;
    quarto1.setHotel(hotel1.getCodigo());
    
    cout << "Codigo do hotel: " << hotel1.getCodigo().getValor() << endl;

    cout << "Codigo do hotel do quarto: " << quarto1.getHotel().getValor() << endl;

    cout << "Nome do gerente: " << gerente1.getNome().getValor() << endl;

    cout << "Nome do gerente do hotel: " << hotel1.getGerente()->getNome().getValor() << endl;

    cout << "\n --- Testes de Relacionamentos Concluídos --- " << endl;
    cout << " --- Testes de Entidades Iniciado ---- " << endl;

    // ------ Gerente --------
    cout << "\n[Testando Entidades: Gerente]" << endl;
    Gerente gerente;

    try {
        gerente.setNome(nome);
        testar("Atribuir nome valido ao gerente", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de nome ao gerente: " << e.what() << endl;
    }

    try {
        gerente.setEmail(email);
        testar("Atribuir email valido ao gerente", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de email ao gerente: " << e.what() << endl;
    }

    try {
        gerente.setSenha(senha);
        testar("Atribuir senha valido ao gerente", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de senha ao gerente: " << e.what() << endl;
    }

    try {
        gerente.setRamal(ramal);
        testar("Atribuir ramal valido ao gerente", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de ramal ao gerente: " << e.what() << endl;
    }

    // ------- Hospede --------
    cout << "\n[Testando Entidades: Hospede]" << endl;
    Hospede hospede;
    try {
        hospede.setCartao(cartao);
        testar("Atribuir cartao valido ao hospede", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de cartao ao hospede: " << e.what() << endl;
    }

    try {
        hospede.setEndereco(end);
        testar("Atribuir endereco valido ao hospede", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de endereco ao hospede: " << e.what() << endl;
    }

    try {
        hospede.setSenha(senha);
        testar("Atribuir senha valida ao hospede", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de senha ao hospede: " << e.what() << endl;
    }

    // ------- Reserva --------
    cout << "\n[Testando Entidades: Reserva]" << endl;

    Reserva reserva;
    Data chegada;
    chegada.setValor(22, "FEV", 2024);
    Data partida;
    partida.setValor(24, "FEV", 2024);
    try {
        reserva.setChegada(chegada);
        testar("Atribuir chegada valida a reserva", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de chegada a reserva: " << e.what() << endl;
    }

    try {
        reserva.setPartida(partida);
        testar("Atribuir partida valida a reserva", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de partida a reserva: " << e.what() << endl;
    }

    try {
        reserva.setValor(din);
        testar("Atribuir valor valido a reserva", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de valor a reserva: " << e.what() << endl;
    }

    try {
        reserva.setCodigo(cod);
        testar("Atribuir codigo valido a reserva", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de codigo a reserva: " << e.what() << endl;
    }

    // ------- Quarto --------
    cout << "\n[Testando Entidades: Quarto]" << endl;
    Quarto quarto;

    try {
        quarto.setNumero(num);
        testar("Atribuir numero valido ao quarto", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de numero ao quarto: " << e.what() << endl;
    }

    try {
        quarto.setCapacidade(cap);
        testar("Atribuir capacidade valida ao quarto", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de capacidade ao quarto: " << e.what() << endl;
    }

    try {
        quarto.setDiaria(din);
        testar("Atribuir diaria valida ao quarto", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de diaria ao quarto: " << e.what() << endl;
    }

    try {
        quarto.setRamal(ramal);
        testar("Atribuir ramal valido ao quarto", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de ramal ao quarto: " << e.what() << endl;
    }
    // ------- Hotel --------
    cout << "\n[Testando Entidades: Hotel]" << endl;
    Hotel hotel;

    try {
        hotel.setNome(nome);
        testar("Atribuir nome valido ao hotel", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de nome ao hotel: " << e.what() << endl;
    }

    try {
        hotel.setEndereco(end);
        testar("Atribuir endereco valido ao hotel", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de endereco ao hotel: " << e.what() << endl;
    }

    try {
        hotel.setTelefone(tel);
        testar("Atribuir telefone valido ao hotel", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de telefone ao hotel: " << e.what() << endl;
    }

    try {
        hotel.setCodigo(cod);
        testar("Atribuir codigo valido ao hotel", true);
    } catch (const invalid_argument& e) {
        cout << "Erro na atribuicao de codigo ao hotel: " << e.what() << endl;
    }

    cout << " --- Testes de Entidades Concluído ---- " << endl;

    return 0;
}