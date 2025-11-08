#include "controladoras.hpp"
#include <iostream>
#include <string>
#include <stdexcept> 

using namespace std;

//-----------------------------------------------//
// Implementação de CtrlApresentacaoAutenticacao //
//-----------------------------------------------//
CtrlApresentacaoAutenticacao::CtrlApresentacaoAutenticacao(IServicoAutenticacao* servico) {
    this->servicoAuth = servico;
}

bool CtrlApresentacaoAutenticacao::executar() {
    string emailStr, senhaStr;

    cout << "\n--- Tela de Login ---" << endl;
    cout << "Digite seu email: ";
    cin >> emailStr;
    cout << "Digite sua senha: ";
    cin >> senhaStr;

    Email email;
    Senha senha;

    try {
        // 1. Validação de formato (Domínios)
        email.setValor(emailStr);
        senha.setValor(senhaStr);

        // 2. Chamada de Serviço (Lógica de Negócio)
        if (servicoAuth->autenticar(email, senha)) {
            return true; 
        } else {
            cout << "Erro: Email ou senha incorretos." << endl;
            return false;
        }

    } catch (const invalid_argument& e) {
        cout << "Erro de formato nos dados: " << e.what() << endl;
        return false;
    }
}


//------------------------------------------//
// Implementação de CtrlApresentacaoHospede //
//------------------------------------------//

CtrlApresentacaoHospede::CtrlApresentacaoHospede(IServicoHospede* servico) {
    this->servicoHospede = servico;
}

void CtrlApresentacaoHospede::executarCadastro() {
    string nomeStr, emailStr, senhaStr, cartaoStr, endStr;
    
    cout << "\n--- Tela de Cadastro de Hospede ---" << endl;
    cout << "Nome (Ex: Joao Silva): ";     cin >> nomeStr;
    cout << "Email (ex: joao@email.com): "; cin >> emailStr;
    cout << "Senha (Ex: A1b$2): ";          cin >> senhaStr;
    cout << "Cartao (16 digitos): ";        cin >> cartaoStr;
    cout << "Endereco (Ex: Rua 1): ";       cin >> endStr;

    try {
        // 1. Validação de Formato (Domínios)
        Nome nome;      nome.setValor(nomeStr);
        Email email;    email.setValor(emailStr);
        Senha senha;    senha.setValor(senhaStr);
        Cartao cartao;  cartao.setValor(cartaoStr);
        Endereco end;   end.setValor(endStr);

        // 2. Chamada de Serviço (Lógica de Negócio)
        servicoHospede->cadastrar(nome, email, senha, cartao, end);
        
        cout << "Cadastro realizado com sucesso!" << endl;

    } catch (const invalid_argument& e) {
        cout << "Erro de formato nos dados: " << e.what() << endl;
    
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}


//-----------------------------------------------//
// Implementação de CtrlApresentacaoHotel        //
//-----------------------------------------------//

CtrlApresentacaoHotel::CtrlApresentacaoHotel(IServicoHotel* servico) {
    this->servicoHotel = servico;
}

void CtrlApresentacaoHotel::executarCadastroHotel() {
    string nomeStr, emailStr, codStr, endStr, telStr;
    
    cout << "\n--- Tela de Cadastro de Hotel ---" << endl;
    cout << "Codigo (10 chars, ex: hotel12345): "; cin >> codStr;
    cout << "Nome (Ex: Hotel Central): ";          cin >> nomeStr;
    cout << "Endereco (Ex: Rua 1): ";             cin >> endStr;
    cout << "Telefone (Ex: +12345678901234): ";    cin >> telStr;

    try {
        // 1. Validação de Formato (Domínios)
        Codigo codigo;   codigo.setValor(codStr);
        Nome nome;     nome.setValor(nomeStr);
        Endereco end;  end.setValor(endStr);
        Telefone tel;  tel.setValor(telStr);

        // 2. Chamada de Serviço (Lógica de Negócio)
        servicoHotel->criar(codigo, nome, end, tel);
        
        cout << "Hotel cadastrado com sucesso!" << endl;

    } catch (const invalid_argument& e) {
        cout << "Erro de formato nos dados: " << e.what() << endl;
    
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}