#include "dominios.hpp"

#include <algorithm>
#include <map>
#include <vector>
#include <cctype>
using namespace std;

// ---------- Capacidade ----------
bool Capacidade::validar(int valor) {
    return (valor >= MIN && valor <= MAX);
}

bool Capacidade::setValor(int valor) {
    if (!validar(valor)) return false;
    this->valor = valor;
    return true;
}


// ---------- Cartao ----------
bool Cartao::validar(const string& numero) {
    if (numero.size() != LIMITE) return false;

    int soma = 0;
    bool alternar = false;

    for (int i = static_cast<int>(numero.size()) - 1; i >= 0; --i) {
        unsigned char ch = static_cast<unsigned char>(numero[static_cast<size_t>(i)]);
        if (!isdigit(ch)) return false;

        int digito = ch - '0';
        if (alternar) {
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        soma += digito;
        alternar = !alternar;
    }
    return (soma % 10 == 0);
}

bool Cartao::setValor(const string& numero) {
    if (!validar(numero)) return false;
    this->valor = numero;
    return true;
}


// ---------- Codigo ----------
bool Codigo::validar(const string& codigo) {
    if (codigo.size() != LIMITE) return false;
    for (unsigned char c : codigo) {
        const bool letraMinuscula = (c >= 'a' && c <= 'z');
        if (!(letraMinuscula || isdigit(c))) return false;
    }
    return true;
}

bool Codigo::setValor(const string& codigo) {
    if (!validar(codigo)) return false;
    this->valor = codigo;
    return true;
}


// ---------- Data ----------
bool Data::isBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

bool Data::validar(int dia, const string& mes, int ano) {
    // Ano válido: 2000..2999
    if (ano < 2000 || ano > 2999) return false;

    // Mapa de meses válidos
    static const map<string, int> mesesValidos = {
        {"JAN",1},{"FEV",2},{"MAR",3},{"ABR",4},{"MAI",5},{"JUN",6},
        {"JUL",7},{"AGO",8},{"SET",9},{"OUT",10},{"NOV",11},{"DEZ",12}
    };

    string mesMaiusculo = mes;
    transform(mesMaiusculo.begin(), mesMaiusculo.end(), mesMaiusculo.begin(), ::toupper);

    auto it = mesesValidos.find(mesMaiusculo);
    if (it == mesesValidos.end()) return false;
    int mesNumerico = it->second;

    // Dias por mês
    vector<int> diasMes = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (mesNumerico == 2 && isBissexto(ano)) diasMes[2] = 29;

    if (dia < 1 || dia > diasMes[mesNumerico]) return false;

    return true;
}

bool Data::setValor(int dia, const string& mes, int ano) {
    if (!validar(dia, mes, ano)) return false;

    string mesMaiusculo = mes;
    transform(mesMaiusculo.begin(), mesMaiusculo.end(), mesMaiusculo.begin(), ::toupper);

    this->DIA   = dia;
    this->MES   = mesMaiusculo;
    this->ANO   = ano;
    this->valor = to_string(dia) + "-" + mesMaiusculo + "-" + to_string(ano); // "dia-MES-ano"
    return true;
}


// ---------- Dinheiro (centavos) ----------
bool Dinheiro::validar(int centavos) {
    // MIN = 1 (R$0,01) ; MAX = 100000000 (R$1.000.000,00)
    return centavos >= MIN && centavos <= MAX;
}

bool Dinheiro::setValor(int centavos) {
    if (!validar(centavos)) return false;
    this->valor = centavos;
    return true;
}


// ---------- Email ----------
// Helpers de validação do Email
static bool parteLocalOk(const string& parteLocal) {
    if (parteLocal.empty() || parteLocal.size() > 64) return false;

    auto ehPermitido = [](unsigned char c){
        return (c >= 'a' && c <= 'z') || isdigit(c) || c == '.' || c == '-';
    };

    // Não pode iniciar/terminar com '.' ou '-'
    if (parteLocal.front() == '.' || parteLocal.front() == '-') return false;
    if (parteLocal.back()  == '.' || parteLocal.back()  == '-') return false;

    for (size_t i = 0; i < parteLocal.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(parteLocal[i]);
        if (!ehPermitido(c)) return false;

        if (c == '.' || c == '-') {
            if (i + 1 >= parteLocal.size()) return false;
            unsigned char prox = static_cast<unsigned char>(parteLocal[i + 1]);
            if (!((prox >= 'a' && prox <= 'z') || isdigit(prox))) return false;
        }
    }
    return true;
}

static bool rotuloDominioOk(const string& rotulo) {
    if (rotulo.empty()) return false;
    if (rotulo.front() == '-' || rotulo.back() == '-') return false;

    for (unsigned char c : rotulo) {
        if (!((c >= 'a' && c <= 'z') || isdigit(c) || c == '-')) return false;
    }
    return true;
}

static bool dominioOk(const string& dominio) {
    if (dominio.empty() || dominio.size() > 255) return false;

    size_t inicio = 0;
    while (true) {
        size_t ponto = dominio.find('.', inicio);
        string rotulo = (ponto == string::npos)
                        ? dominio.substr(inicio)
                        : dominio.substr(inicio, ponto - inicio);

        if (!rotuloDominioOk(rotulo)) return false;

        if (ponto == string::npos) break;
        inicio = ponto + 1;
        if (inicio >= dominio.size()) return false; // não pode terminar com ponto
    }
    return true;
}

bool Email::validar(const string& email) {
    size_t arroba = email.find('@');
    if (arroba == string::npos) return false;

    string parteLocal = email.substr(0, arroba);
    string dominio    = email.substr(arroba + 1);

    // Especificação define letras 'a-z'. Não converteremos automaticamente.
    return parteLocalOk(parteLocal) && dominioOk(dominio);
}

bool Email::setValor(const string& email) {
    if (!validar(email)) return false;
    this->valor = email;
    return true;
}


// ---------- Endereco ----------
bool Endereco::validar(const string& endereco) {
    if (endereco.size() < static_cast<size_t>(MIN) || endereco.size() > static_cast<size_t>(MAX))
        return false;

    auto ehPermitido = [](unsigned char c){
        return isalpha(c) || isdigit(c) || c == ',' || c == '.' || c == ' ';
    };

    for (unsigned char c : endereco) if (!ehPermitido(c)) return false;

    auto pontuacaoOuEspaco = [](unsigned char c){ return c == ',' || c == '.' || c == ' '; };

    // Primeiro e último não podem ser vírgula, ponto ou espaço
    if (pontuacaoOuEspaco(endereco.front())) return false;
    if (pontuacaoOuEspaco(endereco.back()))  return false;

    for (size_t i = 0; i + 1 < endereco.size(); ++i) {
        unsigned char c  = static_cast<unsigned char>(endereco[i]);
        unsigned char nx = static_cast<unsigned char>(endereco[i + 1]);

        // vírgula/ponto não podem ser seguidos por vírgula/ponto
        if ((c == ',' || c == '.') && (nx == ',' || nx == '.')) return false;

        // espaço deve ser seguido por letra ou dígito
        if (c == ' ' && !(isalpha(nx) || isdigit(nx))) return false;
    }
    return true;
}

bool Endereco::setValor(const string& endereco) {
    if (!validar(endereco)) return false;
    this->valor = endereco;
    return true;
}


// ---------- Nome ----------
bool Nome::validar(const string& nome) {
    if (nome.size() < static_cast<size_t>(MIN) || nome.size() > static_cast<size_t>(MAX))
        return false;

    if (nome.front() == ' ' || nome.back() == ' ') return false;

    bool ultimoFoiEspaco = false;
    for (unsigned char c : nome) {
        if (!(isalpha(c) || c == ' ')) return false;
        if (c == ' ' && ultimoFoiEspaco) return false; // sem espaços duplos
        ultimoFoiEspaco = (c == ' ');
    }

    // Cada termo inicia com maiúscula
    bool inicioDePalavra = true;
    for (unsigned char c : nome) {
        if (inicioDePalavra) {
            if (!isupper(c)) return false;
            inicioDePalavra = false;
        } else if (c == ' ') {
            inicioDePalavra = true;
        }
    }
    return true;
}

bool Nome::setValor(const string& nome) {
    if (!validar(nome)) return false;
    this->valor = nome;
    return true;
}


// ---------- Numero ----------
bool Numero::validar(int numero) {
    return numero >= MIN && numero <= MAX; // 1..999
}

bool Numero::setValor(int numero) {
    if (!validar(numero)) return false;
    this->valor = numero;
    return true;
}


// ---------- Ramal ----------
bool Ramal::validar(int ramal) {
    return ramal >= MIN && ramal <= MAX; // 0..50
}

bool Ramal::setValor(int ramal) {
    if (!validar(ramal)) return false;
    this->valor = ramal;
    return true;
}


// ---------- Senha ----------
static bool ehEspecialSenha(unsigned char c) {
    return c=='!' || c=='"' || c=='#' || c=='$' || c=='%' || c=='&' || c=='?';
}

bool Senha::validar(const string& senha) {
    if (senha.size() != static_cast<size_t>(TAMANHO)) return false;

    bool temMinuscula = false, temMaiuscula = false, temDigito = false, temEspecial = false;

    for (size_t i = 0; i < senha.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(senha[i]);
        bool letra  = isalpha(c);
        bool digito = isdigit(c);
        bool espec  = ehEspecialSenha(c);

        // Alfabeto permitido
        if (!(letra || digito || espec)) return false;

        // Flags de composição
        temMinuscula |= islower(c);
        temMaiuscula |= isupper(c);
        temDigito    |= digito;
        temEspecial  |= espec;

        // Restrições de consecutivos
        if (i > 0) {
            unsigned char p = static_cast<unsigned char>(senha[i - 1]);
            if (isalpha(p) && letra)  return false; // duas letras seguidas
            if (isdigit(p) && digito) return false; // dois dígitos seguidos
        }
    }

    return temMinuscula && temMaiuscula && temDigito && temEspecial;
}

bool Senha::setValor(const string& senha) {
    if (!validar(senha)) return false;
    this->valor = senha;
    return true;
}


// ---------- Telefone ----------
bool Telefone::validar(const string& telefone) {
    if (telefone.size() != static_cast<size_t>(TAMANHO)) return false; // TAMANHO = 15
    if (telefone[0] != '+') return false;
    for (size_t i = 1; i < telefone.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(telefone[i]);
        if (!isdigit(c)) return false;
    }
    return true;
}

bool Telefone::setValor(const string& telefone) {
    if (!validar(telefone)) return false;
    this->valor = telefone;
    return true;
}
