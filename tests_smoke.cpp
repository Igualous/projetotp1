#include <iostream>
#include "interfaces.hpp"
#include "servicos_mem.hpp"

int main() {
    // Instancias concretas (em memoria)
    ServicoAutenticacaoMem sAuth;
    ServicoGerenteMem      sGerente;
    ServicoHospedeMem      sHosp;
    ServicoHotelMem        sHotel;
    ServicoQuartoMem       sQuarto;
    ServicoReservaMem      sRes;

    // ligacoes para garantir integridade referencial
    sHosp.setServicoReserva(&sRes);
    sHotel.setServicosRelacionados(&sQuarto, &sRes);
    sQuarto.setServicoReserva(&sRes);
    sRes.setServicosRelacionados(&sHotel, &sQuarto, &sHosp);

    // ===== Diagnostico de dominios (temporario) =====
    try { Senha s;    s.setValor("A1a?2");                 std::cout << "Senha OK\n"; }
    catch (const std::exception& e){ std::cout << "Senha: "    << e.what() << "\n"; }

    try { Telefone t; t.setValor("+12345678901234");       std::cout << "Telefone OK\n"; }
    catch (const std::exception& e){ std::cout << "Telefone: " << e.what() << "\n"; }

    try { Cartao c;   c.setValor("4111111111111111");      std::cout << "Cartao OK\n"; }
    catch (const std::exception& e){ std::cout << "Cartao: "   << e.what() << "\n"; }

    try { Ramal r;    r.setValor(10);                      std::cout << "Ramal OK\n"; }
    catch (const std::exception& e){ std::cout << "Ramal: "    << e.what() << "\n"; }
    // ===== fim do diagnostico =====

    // --------- Dados validos para o smoke test ----------
    Nome nome;        nome.setValor("Ana Silva");
    Email email;      email.setValor("ana@exemplo.com");
    Senha senha;      senha.setValor("A1a?2");
    Cartao cartao;    cartao.setValor("4111111111111111");
    Endereco end;     end.setValor("Rua 1, Centro");

    // ATENCAO: Codigo precisa ter 10 caracteres (minusculos/digitos)
    Codigo codHotel;  codHotel.setValor("h001234567");      // 10 chars
    Nome nomeHotel;   nomeHotel.setValor("Hotel Bom");
    Endereco endHotel;endHotel.setValor("Av. X, 100");
    Telefone tel;     tel.setValor("+12345678901234");      // '+' + 14 digitos (15 chars)

    Numero num;       num.setValor(101);
    Capacidade cap;   cap.setValor(2);
    Dinheiro diaria;  diaria.setValor(25000);
    Ramal ram;        ram.setValor(10);

    // Codigos de reserva com 10 chars
    Codigo codRes1;   codRes1.setValor("r000000001");
    Codigo codRes2;   codRes2.setValor("r000000002");

    Data ch1;         ch1.setValor(10, "OUT", 2025);
    Data p1;          p1.setValor(12, "OUT", 2025);
    Data ch2;         ch2.setValor(11, "OUT", 2025);        // conflita com [10..12)
    Data p2;          p2.setValor(13, "OUT", 2025);

    // --------- Gerente ----------
    sGerente.criar(nome, email, senha, ram);
    auto gerenteLido = sGerente.ler(email);
    std::cout << "Gerente cadastrado? " << (gerenteLido ? "sim" : "nao") << "\n";

    Nome nomeAtualizado; nomeAtualizado.setValor("Ana Souza");
    Ramal novoRamal; novoRamal.setValor(11);
    sGerente.editar(email, nomeAtualizado, senha, novoRamal);
    auto gerenteEditado = sGerente.ler(email);
    std::cout << "Gerente editado? "
              << (gerenteEditado && gerenteEditado->getNome().getValor() == "Ana Souza" ? "sim" : "nao")
              << "\n";

    std::cout << "Total de gerentes: " << sGerente.listar().size() << "\n";

    // --------- Autenticacao (demo) ----------
    sAuth.cadastrar(email, senha);
    std::cout << "Auth: " << (sAuth.autenticar(email, senha) ? "OK" : "FALHA") << "\n";

    // --------- Hospede ----------
    sHosp.cadastrar(nome, email, senha, cartao, end);
    auto h = sHosp.ler(email);
    std::cout << "Hospede cadastrado? " << (h ? "sim" : "nao") << "\n";

    // --------- Hotel & Quarto ----------
    sHotel.criar(codHotel, nomeHotel, endHotel, tel, email);
    sQuarto.criar(codHotel, num, cap, diaria, ram);

    // --------- Reserva OK ----------
    Dinheiro valor; valor.setValor(50000);
    sRes.criar(codRes1, codHotel, num, email, ch1, p1, valor);
    std::cout << "Reserva r000000001 criada.\n";

    // --------- Reserva CONFLITANTE ----------
    try {
        sRes.criar(codRes2, codHotel, num, email, ch2, p2, valor);
        std::cout << "ERRO: conflito nao detectado!\n";
    } catch (const std::exception& e) {
        std::cout << "Conflito detectado OK: " << e.what() << "\n";
    }

    // --------- Listagens ----------
    std::cout << "Reservas por hotel h001234567: " << sRes.listarPorHotel(codHotel).size() << "\n";
    std::cout << "Reservas por hospede ana@exemplo.com: " << sRes.listarPorHospede(email).size() << "\n";


    // === validacoes extras ===

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
    sHotel.criar(codHotel, nomeHotel, endHotel, tel, email);
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

// 5) criar outro quarto (102) e reservar nele (nao conflita)
Numero num2; num2.setValor(102);
sQuarto.criar(codHotel, num2, cap, diaria, ram);
Codigo codRes3; codRes3.setValor("r000000003");
sRes.criar(codRes3, codHotel, num2, email, ch2, p2, valor);
std::cout << "Reserva r000000003 (quarto 102) criada.\n";

// 5.1) segunda reserva no mesmo quarto (102) em periodo diferente
Codigo codRes4; codRes4.setValor("r000000004");
Data ch4; ch4.setValor(20, "OUT", 2025);
Data p4;  p4.setValor(22, "OUT", 2025);
sRes.criar(codRes4, codHotel, num2, email, ch4, p4, valor);
std::cout << "Reserva r000000004 (quarto 102) criada.\n";

// 6) checar contagens apos nova reserva
std::cout << "Reservas por hotel apos quarto 102: "
         << sRes.listarPorHotel(codHotel).size() << "\n";
std::cout << "Reservas por hospede apos quarto 102: "
         << sRes.listarPorHospede(email).size() << "\n";

// 7.1) editar reserva existente (quarto 102) para novo periodo valido
Data ch3; ch3.setValor(15, "OUT", 2025);
Data p3;  p3.setValor(17, "OUT", 2025);
sRes.editar(codRes3, ch3, p3, valor);
auto reservaEditada = sRes.ler(codRes3);
std::cout << "Reserva r000000003 reagendada? "
          << (reservaEditada && reservaEditada->getChegada().getValor() == "15-OUT-2025" ? "sim" : "nao")
          << "\n";

// 7.2) tentativa de edicao conflitando com outra reserva do mesmo quarto (deve falhar)
Data chConflito; chConflito.setValor(21, "OUT", 2025);
Data pConflito;  pConflito.setValor(23, "OUT", 2025);
try {
    sRes.editar(codRes3, chConflito, pConflito, valor);
    std::cout << "ERRO: edicao conflitante permitida!\n";
} catch (const std::exception& e) {
    std::cout << "Edicao conflitante bloqueada: " << e.what() << "\n";
}

std::cout << "Total de reservas no sistema: " << sRes.listar().size() << "\n";

// 7.3) tentativas de exclusao com dependencias (devem falhar)
try {
    sHosp.excluir(email);
    std::cout << "ERRO: exclusao de hospede com reserva permitida!\n";
} catch (const std::exception& e) {
    std::cout << "Excluir hospede bloqueado: " << e.what() << "\n";
}

try {
    sQuarto.excluir(codHotel, num2);
    std::cout << "ERRO: exclusao de quarto com reserva permitida!\n";
} catch (const std::exception& e) {
    std::cout << "Excluir quarto bloqueado: " << e.what() << "\n";
}

try {
    sHotel.excluir(codHotel);
    std::cout << "ERRO: exclusao de hotel com dependencias permitida!\n";
} catch (const std::exception& e) {
    std::cout << "Excluir hotel bloqueado: " << e.what() << "\n";
}

// 7) excluir a primeira reserva e conferir se indice foi limpo
sRes.excluir(codRes1);
std::cout << "Reservas por hotel apos excluir r1: " 
          << sRes.listarPorHotel(codHotel).size() << "\n";
std::cout << "Reservas por hospede apos excluir r1: " 
          << sRes.listarPorHospede(email).size() << "\n";

// Remover demais reservas para liberar quartos
sRes.excluir(codRes3);
sRes.excluir(codRes4);
std::cout << "Reservas restantes apos liberar quartos: " << sRes.listar().size() << "\n";

// 8) listar quartos do hotel
std::cout << "Quartos do hotel: " << sQuarto.listar(codHotel).size() << "\n";

// 9) excluir de novo (idempotente - nao deve quebrar)
sRes.excluir(codRes1);
std::cout << "Excluir reserva inexistente (idempotente) OK\n";

// 10) agora exclusoes devem ocorrer
sQuarto.excluir(codHotel, num2);
sQuarto.excluir(codHotel, num);
std::cout << "Quartos restantes apos exclusao: " << sQuarto.listar(codHotel).size() << "\n";

sHotel.excluir(codHotel);
std::cout << "Hoteis restantes apos exclusao: " << sHotel.listar().size() << "\n";

sHosp.excluir(email);
std::cout << "Hospedes restantes apos exclusao: " << sHosp.listar().size() << "\n";

// === fim validacoes extras ===

    return 0;
}
