/**
 * @file dominios.cpp
 * @brief Implementa as regras de validacao dos dominios declarados em dominios.hpp.
 */
#include "dominios.hpp"

#include <algorithm>
#include <map>
#include <vector>
#include <cctype>
using namespace std;

// ---------- Capacidade ----------
void Capacidade::validar(int valor) {
    if(valor < MIN || valor > MAX){
        throw invalid_argument("A capacidade deve ser entre 1 e 4.");
    }
}

void Capacidade::setValor(int valor) {
    validar(valor);
    this->valor = valor;
}


// ---------- Cartao ----------
void Cartao::validar(const string& numero) {
    if (numero.size() != LIMITE){
        throw invalid_argument("Numero de cartao deve ter 16 digitos.");
    }

    int soma = 0;
    bool alternar = false;

    for (int i = static_cast<int>(numero.size()) - 1; i >= 0; --i) {
        unsigned char ch = static_cast<unsigned char>(numero[static_cast<size_t>(i)]);
        if (!isdigit(ch)){
            throw invalid_argument("Numero do cartao deve conter apenas digitos");
        }

        int digito = ch - '0';
        if (alternar) {
            digito *= 2;
            if (digito > 9) digito -= 9;
        }
        soma += digito;
        alternar = !alternar;
    }

    if(soma % 10 != 0){
        throw invalid_argument("Numero de cartao invalido (falha no algoritmo de Luhn)");
    }
}

void Cartao::setValor(const string& numero) {
    validar(numero);
    this->valor = numero;
}


// ---------- Codigo ----------
void Codigo::validar(const string& codigo) {
    if (codigo.size() != LIMITE){
        throw invalid_argument("Quantidade de digitos invalidos");
    }
    for (unsigned char c : codigo) {
        const bool letraMinuscula = (c >= 'a' && c <= 'z');
        if (!(letraMinuscula || isdigit(c))){
            throw invalid_argument("Digitos invalidos para o codigo.");
        }
    }
}

void Codigo::setValor(const string& codigo) {
    validar(codigo);
    this->valor = codigo;
}


// ---------- Data ----------
bool Data::isBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

void Data::validar(int dia, const string& mes, int ano) {
    // Ano válido: 2000..2999
    if (ano < 2000 || ano > 2999){
        throw invalid_argument("Ano inserido fora do limite.");
    }

    // Mapa de meses válidos
    static const map<string, int> mesesValidos = {
        {"JAN",1},{"FEV",2},{"MAR",3},{"ABR",4},{"MAI",5},{"JUN",6},
        {"JUL",7},{"AGO",8},{"SET",9},{"OUT",10},{"NOV",11},{"DEZ",12}
    };

    string mesMaiusculo = mes;
    transform(mesMaiusculo.begin(), mesMaiusculo.end(), mesMaiusculo.begin(), ::toupper);

    auto it = mesesValidos.find(mesMaiusculo);
    if (it == mesesValidos.end()){
        throw invalid_argument("Mes inserido invalido.");
    }
    int mesNumerico = it->second;

    // Dias por mês
    vector<int> diasMes = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if (mesNumerico == 2 && isBissexto(ano)) diasMes[2] = 29;

    if (dia < 1 || dia > diasMes[mesNumerico]){
        throw invalid_argument("Dia inserido fora do limite.");
    }

}

void Data::setValor(int dia, const string& mes, int ano) {
    validar(dia, mes, ano);

    string mesMaiusculo = mes;
    transform(mesMaiusculo.begin(), mesMaiusculo.end(), mesMaiusculo.begin(), ::toupper);

    this->DIA   = dia;
    this->MES   = mesMaiusculo;
    this->ANO   = ano;
    this->valor = to_string(dia) + "-" + mesMaiusculo + "-" + to_string(ano); // "dia-MES-ano"
}


// ---------- Dinheiro (centavos) ----------
void Dinheiro::validar(int centavos) {
    // MIN = 1 (R$0,01) ; MAX = 100000000 (R$1.000.000,00)
    if(centavos < MIN || centavos > MAX){
        throw invalid_argument("Valores inseridos fora do possivel");
    }   
}

void Dinheiro::setValor(int centavos) {
    validar(centavos);
    this->valor = centavos;
}


// ---------- Email ----------
// Helpers de validação do Email
static void parteLocalOk(const string& parteLocal) {
    if (parteLocal.empty()) {
        throw invalid_argument("Email: A parte local (antes do '@') nao pode ser vazia.");
    }
    if (parteLocal.size() > 64) {
        throw invalid_argument("Email: A parte local (antes do '@') excede 64 caracteres.");
    }

    auto ehPermitido = [](unsigned char c){
        return (c >= 'a' && c <= 'z') || isdigit(c) || c == '.' || c == '-';
    };

    // Não pode iniciar/terminar com '.' ou '-'
    if (parteLocal.front() == '.' || parteLocal.front() == '-') {
        throw invalid_argument("Email: A parte local nao pode comecar ou terminar com '.' ou '-'.");
    }
    if (parteLocal.back()  == '.' || parteLocal.back()  == '-') {
        throw invalid_argument("Email: A parte local nao pode comecar ou terminar com '.' ou '-'.");
    }

    for (size_t i = 0; i < parteLocal.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(parteLocal[i]);
        if (!ehPermitido(c)) {
            throw invalid_argument("Email: A parte local contem um caractere invalido.");
        }

        if (c == '.' || c == '-') {
            if (i + 1 >= parteLocal.size()) {
                throw invalid_argument("Email: A parte local nao pode terminar com '.' ou '-'.");
            }
            unsigned char prox = static_cast<unsigned char>(parteLocal[i + 1]);
            if (!((prox >= 'a' && prox <= 'z') || isdigit(prox))) {
                throw invalid_argument("Email: '.' ou '-' deve ser seguido por uma letra ou digito.");
            }
        }
    }
}

static void rotuloDominioOk(const string& rotulo) {
    if (rotulo.empty()) {
        throw invalid_argument("Email: O 'rotulo' (parte do dominio) nao pode ser vazio.");
    }
    if (rotulo.front() == '-') {
        throw invalid_argument("Email: O 'rotulo' do dominio nao pode comecar com '-'.");
    }
     if (rotulo.back() == '-') {
        throw invalid_argument("Email: O 'rotulo' do dominio nao pode terminar com '-'.");
    }

    for (unsigned char c : rotulo) {
        if (!((c >= 'a' && c <= 'z') || isdigit(c) || c == '-')) {
            throw invalid_argument("Email: O 'rotulo' do dominio contem caractere invalido.");
        }
    }
}

static void dominioOk(const string& dominio) {
    if (dominio.empty()) {
        throw invalid_argument("Email: O dominio (depois do '@') nao pode ser vazio.");
    }
    if (dominio.size() > 255) {
        throw invalid_argument("Email: O dominio excede 255 caracteres.");
    }

    size_t inicio = 0;
    while (true) {
        size_t ponto = dominio.find('.', inicio);
        string rotulo = (ponto == string::npos)
                        ? dominio.substr(inicio)
                        : dominio.substr(inicio, ponto - inicio);

        rotuloDominioOk(rotulo);

        if (ponto == string::npos) {
            break; 
        }
        
        inicio = ponto + 1;
        // Checa se o email termina com um ponto (ex: "dominio.com.")
        if (inicio >= dominio.size()) {
            throw invalid_argument("Email: O dominio nao pode terminar com '.'.");
        }
    }
}


void Email::validar(const string& email) {
    size_t arroba = email.find('@');
    
    if (arroba == string::npos) {
        throw invalid_argument("Email invalido: Faltando '@'.");
    }
    if (email.find('@', arroba + 1) != string::npos) {
        throw invalid_argument("Email invalido: Nao pode haver mais de um '@'.");
    }

    string parteLocal = email.substr(0, arroba);
    string dominio    = email.substr(arroba + 1);

    // Chama os helpers. Se algum deles falhar, a exceção será propagada.
    parteLocalOk(parteLocal);
    dominioOk(dominio);
}

void Email::setValor(const string& email) {
    validar(email);
    this->valor = email;
}


// ---------- Endereco ----------
void Endereco::validar(const string& endereco) {
    if (endereco.size() < static_cast<size_t>(MIN) || endereco.size() > static_cast<size_t>(MAX)) {
        throw invalid_argument("Endereco deve ter entre 5 e 30 caracteres.");
    }

    auto ehPermitido = [](unsigned char c){
        return isalpha(c) || isdigit(c) || c == ',' || c == '.' || c == ' ';
    };

    for (unsigned char c : endereco) {
        if (!ehPermitido(c)) {
            throw invalid_argument("Endereco contem caractere invalido.");
        }
    }

    auto pontuacaoOuEspaco = [](unsigned char c){ return c == ',' || c == '.' || c == ' '; };

    // Primeiro e último não podem ser vírgula, ponto ou espaço
    if (pontuacaoOuEspaco(endereco.front())) {
        throw invalid_argument("Endereco nao pode comecar com pontuacao ou espaco.");
    }
    if (pontuacaoOuEspaco(endereco.back())) {
        throw invalid_argument("Endereco nao pode terminar com pontuacao ou espaco.");
    }

    for (size_t i = 0; i + 1 < endereco.size(); ++i) {
        unsigned char c  = static_cast<unsigned char>(endereco[i]);
        unsigned char nx = static_cast<unsigned char>(endereco[i + 1]);

        // vírgula/ponto não podem ser seguidos por vírgula/ponto
        if ((c == ',' || c == '.') && (nx == ',' || nx == '.')) {
            throw invalid_argument("Endereco: pontuacao nao pode ser seguida por outra pontuacao.");
        }

        // espaço deve ser seguido por letra ou dígito
        if (c == ' ' && !(isalpha(nx) || isdigit(nx))) {
            throw invalid_argument("Endereco: espaco deve ser seguido por letra ou digito.");
        }
    }
}

void Endereco::setValor(const string& endereco) {
    validar(endereco);
    this->valor = endereco;
}


// ---------- Nome ----------
void Nome::validar(const string& nome) {
    if (nome.size() < static_cast<size_t>(MIN) || nome.size() > static_cast<size_t>(MAX)) {
        throw invalid_argument("Nome deve ter entre 5 e 20 caracteres.");
    }

    if (nome.front() == ' ') {
        throw invalid_argument("Nome nao pode comecar com espaco.");
    }
    if (nome.back() == ' ') {
        throw invalid_argument("Nome nao pode terminar com espaco.");
    }

    bool ultimoFoiEspaco = false;
    bool inicioDePalavra = true;

    for (unsigned char c : nome) {
        if (!(isalpha(c) || c == ' ')) {
            throw invalid_argument("Nome deve conter apenas letras e espacos.");
        }
        
        if (c == ' ' && ultimoFoiEspaco) {
            throw invalid_argument("Nome nao pode conter espacos duplos.");
        }
        ultimoFoiEspaco = (c == ' ');

        if (c == ' ') {
            inicioDePalavra = true;
        } else if (inicioDePalavra) {
            if (!isupper(c)) {
                throw invalid_argument("Nome: Cada termo deve comecar com letra maiuscula.");
            }
            inicioDePalavra = false;
        }
    }
}

void Nome::setValor(const string& nome) {
    validar(nome);
    this->valor = nome;
}


// ---------- Numero ----------
void Numero::validar(int numero) {
    if (numero < MIN || numero > MAX) { // 1..999
        throw invalid_argument("Numero deve estar entre 1 e 999.");
    }
}

void Numero::setValor(int numero) {
    validar(numero);
    this->valor = numero;
}


// ---------- Ramal ----------
void Ramal::validar(int ramal) {
    if (ramal < MIN || ramal > MAX) { // 0..50
        throw invalid_argument("Ramal deve estar entre 0 e 50.");
    }
}

void Ramal::setValor(int ramal) {
    validar(ramal);
    this->valor = ramal;
}


// ---------- Senha ----------
static bool ehEspecialSenha(unsigned char c) {
    return c=='!' || c=='"' || c=='#' || c=='$' || c=='%' || c=='&' || c=='?';
}

void Senha::validar(const string& senha) {
    if (senha.size() != static_cast<size_t>(TAMANHO)) {
        throw invalid_argument("Senha deve ter exatamente 5 caracteres.");
    }

    bool temMinuscula = false, temMaiuscula = false, temDigito = false, temEspecial = false;

    for (size_t i = 0; i < senha.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(senha[i]);
        bool letra  = isalpha(c);
        bool digito = isdigit(c);
        bool espec  = ehEspecialSenha(c);

        if (!(letra || digito || espec)) {
            throw invalid_argument("Senha contem caractere invalido.");
        }

        // Flags de composição
        temMinuscula |= islower(c);
        temMaiuscula |= isupper(c);
        temDigito    |= digito;
        temEspecial  |= espec;

        if (i > 0) {
            unsigned char p = static_cast<unsigned char>(senha[i - 1]);
            if (isalpha(p) && letra) {
                throw invalid_argument("Senha nao pode conter duas letras seguidas.");
            }
            if (isdigit(p) && digito) {
                throw invalid_argument("Senha nao pode conter dois digitos seguidos.");
            }
        }
    }
    
    if (!(temMinuscula && temMaiuscula && temDigito && temEspecial)) {
         throw invalid_argument("Senha deve conter ao menos 1 maiuscula, 1 minuscula, 1 digito e 1 especial.");
    }
}

void Senha::setValor(const string& senha) {
    validar(senha);
    this->valor = senha;
}


// ---------- Telefone ----------
void Telefone::validar(const string& telefone) {
    if (telefone.size() != static_cast<size_t>(TAMANHO)) { // TAMANHO = 15
        throw invalid_argument("Telefone deve ter 15 caracteres (ex: +12345678901234).");
    }
    if (telefone[0] != '+') {
        throw invalid_argument("Telefone deve comecar com o caractere '+'.");
    }
    for (size_t i = 1; i < telefone.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(telefone[i]);
        if (!isdigit(c)) {
            throw invalid_argument("Telefone deve conter apenas digitos apos o '+'.");
        }
    }
}

void Telefone::setValor(const string& telefone) {
    validar(telefone);
    this->valor = telefone;
}
