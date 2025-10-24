#include <iostream>
#include "interfaces.hpp"
#include "servicos_mem.hpp"

int main() {
    // Instâncias concretas (em memória)
    ServicoAutenticacaoMem sAuth;
    ServicoHospedeMem      sHosp;
    ServicoHotelMem        sHotel;
    ServicoQuartoMem       sQuarto;
    ServicoReservaMem      sRes;

    // ===== Diagnóstico de domínios (temporário) =====
    try { Senha s;    s.setValor("A1a?2");                 std::cout << "Senha OK\n"; }
    catch (const std::exception& e){ std::cout << "Senha: "    << e.what() << "\n"; }

    try { Telefone t; t.setValor("+12345678901234");       std::cout << "Telefone OK\n"; }
    catch (const std::exception& e){ std::cout << "Telefone: " << e.what() << "\n"; }

    try { Cartao c;   c.setValor("4111111111111111");      std::cout << "Cartao OK\n"; }
    catch (const std::exception& e){ std::cout << "Cartao: "   << e.what() << "\n"; }

    try { Ramal r;    r.setValor(10);                      std::cout << "Ramal OK\n"; }
    catch (const std::exception& e){ std::cout << "Ramal: "    << e.what() << "\n"; }
    // ===== fim do diagnóstico =====

    // --------- Dados válidos para o smoke test ----------
    Nome nome;        nome.setValor("Ana Silva");
    Email email;      email.setValor("ana@exemplo.com");
    Senha senha;      senha.setValor("A1a?2");
    Cartao cartao;    cartao.setValor("4111111111111111");
    Endereco end;     end.setValor("Rua 1, Centro");

    // ATENÇÃO: Codigo precisa ter 10 caracteres (minúsculos/dígitos)
    Codigo codHotel;  codHotel.setValor("h001234567");      // 10 chars
    Nome nomeHotel;   nomeHotel.setValor("Hotel Bom");
    Endereco endHotel;endHotel.setValor("Av. X, 100");
    Telefone tel;     tel.setValor("+12345678901234");      // '+' + 14 dígitos (15 chars)

    Numero num;       num.setValor(101);
    Capacidade cap;   cap.setValor(2);
    Dinheiro diaria;  diaria.setValor(25000);
    Ramal ram;        ram.setValor(10);

    // Códigos de reserva com 10 chars
    Codigo codRes1;   codRes1.setValor("r000000001");
    Codigo codRes2;   codRes2.setValor("r000000002");

    Data ch1;         ch1.setValor(10, "OUT", 2025);
    Data p1;          p1.setValor(12, "OUT", 2025);
    Data ch2;         ch2.setValor(11, "OUT", 2025);        // conflita com [10..12)
    Data p2;          p2.setValor(13, "OUT", 2025);

    // --------- Autenticação (demo) ----------
    sAuth.cadastrar(email, senha);
    std::cout << "Auth: " << (sAuth.autenticar(email, senha) ? "OK" : "FALHA") << "\n";

    // --------- Hospede ----------
    sHosp.cadastrar(nome, email, senha, cartao, end);
    auto h = sHosp.ler(email);
    std::cout << "Hospede cadastrado? " << (h ? "sim" : "nao") << "\n";

    // --------- Hotel & Quarto ----------
    sHotel.criar(codHotel, nomeHotel, endHotel, tel);
    sQuarto.criar(codHotel, num, cap, diaria, ram);

    // --------- Reserva OK ----------
    Dinheiro valor; valor.setValor(50000);
    sRes.criar(codRes1, codHotel, num, email, ch1, p1, valor);
    std::cout << "Reserva r000000001 criada.\n";

    // --------- Reserva CONFLITANTE ----------
    try {
        sRes.criar(codRes2, codHotel, num, email, ch2, p2, valor);
        std::cout << "ERRO: conflito não detectado!\n";
    } catch (const std::exception& e) {
        std::cout << "Conflito detectado OK: " << e.what() << "\n";
    }

    // --------- Listagens ----------
    std::cout << "Reservas por hotel h001234567: " << sRes.listarPorHotel(codHotel).size() << "\n";
    std::cout << "Reservas por hospede ana@exemplo.com: " << sRes.listarPorHospede(email).size() << "\n";


    // === validações extras ===

// 1) ler reserva inexistente
{
    Codigo codResX; codResX.setValor("r000000999");
    std::cout << "Reserva r000000999 existe? " << (sRes.ler(codResX) ? "sim" : "nao") << "\n";
}

// 2) editar hotel (nome) e conferir
{
    Nome novoNomeHotel; novoNomeHotel.setValor("Hotel Melhor");
    sHotel.editar(codHotel, novoNomeHotel, endHotel, tel);
    auto htl = sHotel.ler(codHotel);
    std::cout << "Editar hotel: " 
              << (htl && htl->getNome().getValor() == "Hotel Melhor" ? "OK" : "FALHOU")
              << "\n";
}

// 3) criar hotel duplicado (deve falhar)
try {
    sHotel.criar(codHotel, nomeHotel, endHotel, tel);
    std::cout << "ERRO: hotel duplicado passou!\n";
} catch (const std::exception& e) {
    std::cout << "Hotel duplicado bloqueado: " << e.what() << "\n";
}

// 4) criar quarto duplicado no mesmo hotel (deve falhar)
try {
    sQuarto.criar(codHotel, num, cap, diaria, ram);
    std::cout << "ERRO: quarto duplicado passou!\n";
} catch (const std::exception& e) {
    std::cout << "Quarto duplicado bloqueado: " << e.what() << "\n";
}

// 5) criar outro quarto (102) e reservar nele (não conflita)
Numero num2; num2.setValor(102);
sQuarto.criar(codHotel, num2, cap, diaria, ram);
Codigo codRes3; codRes3.setValor("r000000003");
sRes.criar(codRes3, codHotel, num2, email, ch2, p2, valor);
std::cout << "Reserva r000000003 (quarto 102) criada.\n";

// 6) checar contagens após nova reserva
std::cout << "Reservas por hotel apos quarto 102: " 
          << sRes.listarPorHotel(codHotel).size() << "\n";
std::cout << "Reservas por hospede apos quarto 102: " 
          << sRes.listarPorHospede(email).size() << "\n";

// 7) excluir a primeira reserva e conferir se índice foi limpo
sRes.excluir(codRes1);
std::cout << "Reservas por hotel apos excluir r000000001: " 
          << sRes.listarPorHotel(codHotel).size() << "\n";
std::cout << "Reservas por hospede apos excluir r000000001: " 
          << sRes.listarPorHospede(email).size() << "\n";

// 8) listar quartos do hotel
std::cout << "Quartos do hotel: " << sQuarto.listar(codHotel).size() << "\n";

// 9) excluir de novo (idempotente — não deve quebrar)
sRes.excluir(codRes1);
std::cout << "Excluir reserva inexistente (idempotente) OK\n";

// === fim validações extras ===

    return 0;
}
