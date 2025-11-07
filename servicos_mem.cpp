#include "servicos_mem.hpp"
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <map>

// ---------- Âncoras de vtable ----------
ServicoHotelMem::~ServicoHotelMem() = default;
ServicoQuartoMem::~ServicoQuartoMem() = default;

// ---------- Autenticacao ----------
bool ServicoAutenticacaoMem::autenticar(const Email& email, const Senha& senha) {
    auto it = credenciais.find(email.getValor());
    return (it != credenciais.end() && it->second == senha.getValor());
}

// ---------- Gerente ----------
void ServicoGerenteMem::criar(const Nome& nome, const Email& email,
                              const Senha& senha, const Ramal& ramal) {
    auto key = email.getValor();
    if (gerentes.count(key)) throw std::runtime_error("Gerente j� cadastrado.");
    Gerente g;
    g.setNome(nome);
    g.setEmail(email);
    g.setSenha(senha);
    g.setRamal(ramal);
    gerentes[key] = g;
}

std::optional<Gerente> ServicoGerenteMem::ler(const Email& email) {
    auto it = gerentes.find(email.getValor());
    if (it != gerentes.end()) return it->second;
    return std::nullopt;
}

void ServicoGerenteMem::editar(const Email& emailChave, const Nome& nome,
                               const Senha& senha, const Ramal& ramal) {
    auto it = gerentes.find(emailChave.getValor());
    if (it == gerentes.end()) throw std::runtime_error("Gerente inexistente.");
    it->second.setNome(nome);
    it->second.setSenha(senha);
    it->second.setRamal(ramal);
}

void ServicoGerenteMem::excluir(const Email& email) {
    gerentes.erase(email.getValor());
}

std::vector<Gerente> ServicoGerenteMem::listar() {
    std::vector<Gerente> v;
    v.reserve(gerentes.size());
    for (auto& kv : gerentes) v.push_back(kv.second);
    return v;
}

// ---------- Hospede ----------
void ServicoHospedeMem::cadastrar(const Nome& nome, const Email& email,
                                  const Senha& senha, const Cartao& cartao,
                                  const Endereco& endereco) {
    auto key = email.getValor();
    if (hospedes.count(key)) throw std::runtime_error("Hóspede já cadastrado.");
    Hospede h;
    h.setNome(nome);
    h.setEmail(email);
    h.setSenha(senha);
    h.setCartao(cartao);
    h.setEndereco(endereco);
    hospedes[key] = h;
}

std::optional<Hospede> ServicoHospedeMem::ler(const Email& email) {
    auto it = hospedes.find(email.getValor());
    if (it != hospedes.end()) return it->second;
    return std::nullopt;
}

void ServicoHospedeMem::editar(const Email& emailChave, const Nome& nome,
                               const Cartao& cartao, const Endereco& endereco) {
    auto it = hospedes.find(emailChave.getValor());
    if (it == hospedes.end()) throw std::runtime_error("Hóspede inexistente.");
    it->second.setNome(nome);
    it->second.setCartao(cartao);
    it->second.setEndereco(endereco);
}

void ServicoHospedeMem::excluir(const Email& email) {
    hospedes.erase(email.getValor());
}

std::vector<Hospede> ServicoHospedeMem::listar() {
    std::vector<Hospede> v;
    v.reserve(hospedes.size());
    for (auto& kv : hospedes) v.push_back(kv.second);
    return v;
}

// ---------- Hotel ----------
void ServicoHotelMem::criar(const Codigo& codigo, const Nome& nome,
                            const Endereco& endereco, const Telefone& telefone) {
    auto key = codigo.getValor();
    if (hoteis.count(key)) throw std::runtime_error("Hotel já existe.");
    Hotel h;
    h.setCodigo(codigo);
    h.setNome(nome);
    h.setEndereco(endereco);
    h.setTelefone(telefone);
    hoteis[key] = h;
}

std::optional<Hotel> ServicoHotelMem::ler(const Codigo& codigo) {
    auto it = hoteis.find(codigo.getValor());
    if (it != hoteis.end()) return it->second;
    return std::nullopt;
}

void ServicoHotelMem::editar(const Codigo& codigo, const Nome& nome,
                             const Endereco& endereco, const Telefone& telefone) {
    auto it = hoteis.find(codigo.getValor());
    if (it == hoteis.end()) throw std::runtime_error("Hotel inexistente.");
    it->second.setNome(nome);
    it->second.setEndereco(endereco);
    it->second.setTelefone(telefone);
}

void ServicoHotelMem::excluir(const Codigo& codigo) {
    hoteis.erase(codigo.getValor());
}

std::vector<Hotel> ServicoHotelMem::listar() {
    std::vector<Hotel> v;
    v.reserve(hoteis.size());
    for (auto& kv : hoteis) v.push_back(kv.second);
    return v;
}

// ---------- Quarto ----------
void ServicoQuartoMem::criar(const Codigo& codHotel, const Numero& numero,
                             const Capacidade& cap, const Dinheiro& diaria,
                             const Ramal& ramal) {
    ChaveQuarto key{codHotel.getValor(), numero.getValor()};
    if (quartos.count(key)) throw std::runtime_error("Quarto já existe nesse hotel.");
    Quarto q;
    q.setNumero(numero);
    q.setHotel(codHotel);
    q.setCapacidade(cap);
    q.setDiaria(diaria);
    q.setRamal(ramal);
    quartos[key] = q;
}

std::optional<Quarto> ServicoQuartoMem::ler(const Codigo& codHotel, const Numero& numero) {
    ChaveQuarto key{codHotel.getValor(), numero.getValor()};
    auto it = quartos.find(key);
    if (it != quartos.end()) return it->second;
    return std::nullopt;
}

void ServicoQuartoMem::editar(const Codigo& codHotel, const Numero& numero,
                              const Capacidade& cap, const Dinheiro& diaria,
                              const Ramal& ramal) {
    ChaveQuarto key{codHotel.getValor(), numero.getValor()};
    auto it = quartos.find(key);
    if (it == quartos.end()) throw std::runtime_error("Quarto inexistente.");
    it->second.setCapacidade(cap);
    it->second.setDiaria(diaria);
    it->second.setRamal(ramal);
}

void ServicoQuartoMem::excluir(const Codigo& codHotel, const Numero& numero) {
    ChaveQuarto key{codHotel.getValor(), numero.getValor()};
    quartos.erase(key);
}

std::vector<Quarto> ServicoQuartoMem::listar(const Codigo& codHotel) {
    std::vector<Quarto> v;
    for (auto& kv : quartos) {
        if (kv.first.first == codHotel.getValor()) v.push_back(kv.second);
    }
    return v;
}

// ---------- Helpers de data (Reserva) ----------
int ServicoReservaMem::mesToNum(const std::string& mes3) {
    static const std::map<std::string,int> M = {
        {"JAN",1},{"FEV",2},{"MAR",3},{"ABR",4},{"MAI",5},{"JUN",6},
        {"JUL",7},{"AGO",8},{"SET",9},{"OUT",10},{"NOV",11},{"DEZ",12}
    };
    std::string up = mes3;
    std::transform(up.begin(), up.end(), up.begin(), ::toupper);
    auto it = M.find(up);
    if (it == M.end()) throw std::runtime_error("Mês inválido: " + mes3);
    return it->second;
}

int ServicoReservaMem::toOrdinal(const Data& d) {
    // Data::getValor() retorna "DD-MES-AAAA"
    std::string s = d.getValor();
    auto p1 = s.find('-');
    auto p2 = s.find('-', p1+1);
    int dia = std::stoi(s.substr(0, p1));
    std::string mes = s.substr(p1+1, p2-p1-1);
    int ano = std::stoi(s.substr(p2+1));
    int mm = mesToNum(mes);
    return ano*10000 + mm*100 + dia; // yyyymmdd
}

bool ServicoReservaMem::sobrepoe(const Data& c1, const Data& p1,
                                 const Data& c2, const Data& p2) {
    int a = toOrdinal(c1), b = toOrdinal(p1);
    int c = toOrdinal(c2), d = toOrdinal(p2);
    // intervalos [a,b) e [c,d) sobrepõem se:
    return (a < d) && (c < b);
}

// ---------- Reserva ----------
void ServicoReservaMem::criar(const Codigo& codReserva, const Codigo& codHotel,
                              const Numero& numQuarto, const Email& emailHospede,
                              const Data& chegada, const Data& partida,
                              const Dinheiro& valor) {
    auto key = codReserva.getValor();
    if (reservas.count(key)) throw std::runtime_error("Codigo de reserva ja existe.");

    if (toOrdinal(chegada) >= toOrdinal(partida)) {
        throw std::runtime_error("Periodo de reserva invalido.");
    }

    ChaveQuarto chaveQ{ codHotel.getValor(), numQuarto.getValor() };

    // checar conflitos no mesmo quarto
    auto range = idxResPorQuarto.equal_range(chaveQ);
    for (auto it = range.first; it != range.second; ++it) {
        const Reserva& r = reservas.at(it->second);
        if (sobrepoe(chegada, partida, r.getChegada(), r.getPartida())) {
            throw std::runtime_error("Conflito de reserva para o mesmo quarto.");
        }
    }

    Reserva r;
    r.setCodigo(codReserva);
    r.setHotel(codHotel);
    r.setNumero(numQuarto);
    r.setHospede(emailHospede);
    r.setChegada(chegada);
    r.setPartida(partida);
    r.setValor(valor);

    reservas[key] = r;
    idxResPorQuarto.emplace(chaveQ, key);
}

std::optional<Reserva> ServicoReservaMem::ler(const Codigo& cod) {
    auto it = reservas.find(cod.getValor());
    if (it != reservas.end()) return it->second;
    return std::nullopt;
}

void ServicoReservaMem::editar(const Codigo& cod, const Data& chegada,
                               const Data& partida, const Dinheiro& valor) {
    auto it = reservas.find(cod.getValor());
    if (it == reservas.end()) throw std::runtime_error("Reserva inexistente.");

    if (toOrdinal(chegada) >= toOrdinal(partida)) {
        throw std::runtime_error("Periodo de reserva invalido.");
    }

    ChaveQuarto chaveQ{ it->second.getHotel().getValor(), it->second.getNumero().getValor() };
    auto range = idxResPorQuarto.equal_range(chaveQ);
    for (auto cursor = range.first; cursor != range.second; ++cursor) {
        if (cursor->second == cod.getValor()) continue;
        const Reserva& outra = reservas.at(cursor->second);
        if (sobrepoe(chegada, partida, outra.getChegada(), outra.getPartida())) {
            throw std::runtime_error("Conflito de reserva para o mesmo quarto.");
        }
    }

    it->second.setChegada(chegada);
    it->second.setPartida(partida);
    it->second.setValor(valor);
}

void ServicoReservaMem::excluir(const Codigo& cod) {
    auto it = reservas.find(cod.getValor());
    if (it == reservas.end()) return;
    ChaveQuarto cq{ it->second.getHotel().getValor(), it->second.getNumero().getValor() };
    // remove do índice
    for (auto rng = idxResPorQuarto.equal_range(cq); rng.first != rng.second; ) {
        if (rng.first->second == cod.getValor()) rng.first = idxResPorQuarto.erase(rng.first);
        else ++rng.first;
    }
    reservas.erase(it);
}

std::vector<Reserva> ServicoReservaMem::listarPorHotel(const Codigo& codHotel) {
    std::vector<Reserva> v;
    for (auto& kv : reservas) {
        if (kv.second.getHotel().getValor() == codHotel.getValor()) v.push_back(kv.second);
    }
    return v;
}

std::vector<Reserva> ServicoReservaMem::listarPorHospede(const Email& email) {
    std::vector<Reserva> v;
    for (auto& kv : reservas) {
        if (kv.second.getHospede().getValor() == email.getValor()) v.push_back(kv.second);
    }
    return v;
}

std::vector<Reserva> ServicoReservaMem::listar() {
    std::vector<Reserva> v;
    v.reserve(reservas.size());
    for (auto& kv : reservas) {
        v.push_back(kv.second);
    }
    return v;
}
