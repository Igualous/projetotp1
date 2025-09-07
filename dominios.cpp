#include "dominios.hpp"
#include <vector>
#include <map>
#include <algorithm>

// **** DEFINICAO DAS FUNCOES ****

bool Capacidade::validar(int valor) {
    if (valor >= MIN && valor <= MAX) {
        return true;
    } else {
        return false;
    }
}

bool Cartao::validar(string numero) {
    if(numero.size() != LIMITE) return false;

    int soma = 0;
    bool alternar = false;

    for(int i = numero.size() - 1; i >= 0; i--){
        if(!isdigit(numero[i])) return false;
        int digito = numero[i] - '0'; // convertendo para int

        if(alternar){
            digito *= 2;
            if(digito > 9){
                digito -= 9;
            }
        }

        soma += digito;
        alternar = !alternar;
    }

    return (soma % 10 == 0);
}

bool Codigo::validar(string valor) {
    if (valor.size() != LIMITE) return false;

    for(char c : valor){
        if(!isalnum(c)) return false;
    }

    return true;
}

bool isBisexto(int ANO){
    return (ANO % 4 == 0 && ANO % 100 != 0) || (ANO % 200 == 0);
}

bool Data::validar(int DIA, string MES, int ANO){
    if(ANO >= 2000 && ANO < 3000) return false;

    map<string, int> mesesValidos = {
        {"JAN", 1}, {"FEV", 2}, {"MAR", 3}, {"ABR", 4}, {"MAI", 5}, {"JUN", 6}, {"JUL", 7}, {"AGO", 8}, {"SET", 9}, {"OUT", 10}, {"NOV", 11}, {"DEZ", 12}
    };

    string mesMaiusculo = MES;
    transform(mesMaiusculo.begin(), mesMaiusculo.end(), mesMaiusculo.begin(), ::toupper);

    if(mesesValidos.find(mesMaiusculo) == mesesValidos.end()) return false;
    int mesNumerico = mesesValidos[mesMaiusculo];

    vector<int> diasMes = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if(isBisexto){
        diasMes[2] = 29;
    }

    int maxDias = diasMes[mesNumerico];
    if(DIA < 1 || DIA > maxDias) return false;

    return true;
}
