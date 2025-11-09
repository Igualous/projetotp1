#include "controladoras.hpp"
#include <iostream>
#include <string>
#include <stdexcept> 
#include <limits>
#include <cctype>

using namespace std;

//-----------------------------------------------//
// Implementação de CtrlApresentacaoAutenticacao //
//-----------------------------------------------//
CtrlApresentacaoAutenticacao::CtrlApresentacaoAutenticacao(IServicoAutenticacao* servico) {
    this->servicoAuth = servico;
}

bool CtrlApresentacaoAutenticacao::executar(Email& emailAutenticado) {
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
            emailAutenticado = email;
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

void CtrlApresentacaoHotel::executarCadastroHotel(const Email& emailGerente) {
    string nomeStr, codStr, endStr, telStr;
    
    cout << "\n--- Tela de Cadastro de Hotel ---" << endl;
    cout << "Codigo (10 chars, ex: hotel12345): ";
    cin >> codStr;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nome (Ex: Hotel Central): ";
    getline(cin, nomeStr);
    cout << "Endereco (Ex: Rua 1): ";
    getline(cin, endStr);
    cout << "Telefone (Ex: +12345678901234): ";
    getline(cin, telStr);

    try {
        // 1. Validação de Formato (Domínios)
        Codigo codigo;   codigo.setValor(codStr);
        Nome nome;     nome.setValor(nomeStr);
        Endereco end;  end.setValor(endStr);
        Telefone tel;  tel.setValor(telStr);

        // 2. Chamada de Serviço (Lógica de Negócio)
        servicoHotel->criar(codigo, nome, end, tel, emailGerente);
        
        cout << "Hotel cadastrado com sucesso!" << endl;

    } catch (const invalid_argument& e) {
        cout << "Erro de formato nos dados: " << e.what() << endl;
    
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}

void CtrlApresentacaoHotel::executarListarHoteis(const Email& emailGerente) {
    cout << "\n--- Meus Hoteis ---" << endl;
    try {
        auto lista = servicoHotel->listarPorGerente(emailGerente);
        if (lista.empty()) {
            cout << "Voce ainda nao possui hoteis cadastrados." << endl;
            return;
        }

        int index = 0;
        for (const auto& hotel : lista) {
            cout << "[" << index << "] " 
                 <<  "Codigo: " << hotel.getCodigo().getValor()
                 << " | Nome: " << hotel.getNome().getValor()
                 << " | Endereco: " << hotel.getEndereco().getValor()
                 << " | Telefone: " << hotel.getTelefone().getValor()
                 << endl;
            index++;
        }

        cout << "\n1 - Gerenciar hoteis" << endl;
        cout << "2 - Voltar" << endl;

        int opcaoAcao;
        cin >> opcaoAcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar buffer
        
        if (opcaoAcao != 1) {
            return;
        }

        cout << "\n\nSelecione o indice do hotel que deseja gerenciar: ";
        int indexEscolhido;
        cin >> indexEscolhido;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar buffer
        
        if (indexEscolhido < 0 || indexEscolhido >= lista.size()) {
            cout << "indice invalido. Voltando..." << endl;
            return;
        }
        const Hotel& hotelEscolhido = lista.at(indexEscolhido);
        string codigoHotelEscolhido = hotelEscolhido.getCodigo().getValor();
        string nomeHotelEscolhido = hotelEscolhido.getNome().getValor();
        
        cout << "Hotel selecionado: " << nomeHotelEscolhido << endl;


        cout << "\n1 - Editar hotel" << endl;
        cout << "2 - Excluir hotel" << endl;
        cout << "3 - Gerenciar quartos" << endl;
        cout << "\nO que deseja fazer?: ";
        
        int opcaoGerencia;
        cin >>  opcaoGerencia;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar buffer 

        switch (opcaoGerencia) {
            case 1:
                executarEditarHotel(codigoHotelEscolhido); 
            break;
            case 2:
                executarExcluirHotel(codigoHotelEscolhido);
            break;
            case 3:
                cout << "gerenciar quartos escolhido (ainda nao implementado)" << endl;
            break;
            default:
                cout << "opcao invalida" << endl;
        }

    } catch (const runtime_error& e) {
        cout << "Erro ao listar hoteis: " << e.what() << endl;
    }
}

void CtrlApresentacaoHotel::executarEditarHotel(const string& codigoHotel) {
    cout << "\n--- Tela de Edição de Hotel (" << codigoHotel << ") ---" << endl;

    // 1. validacao de parametro
    Codigo codigo;
    try {
        codigo.setValor(codigoHotel);
    } catch (const std::invalid_argument& e) {
        cout << "Erro: Código do hotel inválido: " << e.what() << endl;
        return;
    }

    // 2. encontra o hotel pelo codigo
    std::optional<Hotel> hotelAtualOpt;
    try {
        hotelAtualOpt = servicoHotel->ler(codigo);
    } catch (const std::runtime_error& e) {
        cout << "Erro ao buscar hotel: " << e.what() << endl;
        return;
    }
    
    // 3. Verificar se o hotel existe
    if (!hotelAtualOpt) {
        cout << "Erro de negócio: Hotel com código " << codigoHotel << " não encontrado." << endl;
        return;
    }
    const Hotel& hotelAtual = *hotelAtualOpt;

    string nomeStr, endStr, telStr;
    
    cout << "Digite o NOVO NOME (atual: "<< hotelAtual.getNome().getValor() << "): ";
    getline(cin, nomeStr);
    cout << "Digite o NOVO ENDEREÇO (atual: " << hotelAtual.getEndereco().getValor() << "): ";
    getline(cin, endStr);
    cout << "Digite o NOVO TELEFONE (atual: " << hotelAtual.getTelefone().getValor() << "): ";
    getline(cin, telStr);

    try {
        // 1. Validação de Formato
        Codigo codigo;   codigo.setValor(codigoHotel); // Usamos o código existente
        Nome nome;       nome.setValor(nomeStr);
        Endereco end;    end.setValor(endStr);
        Telefone tel;    tel.setValor(telStr);

        // 2. Chamada de Servico
        servicoHotel->editar(codigo, nome, end, tel);
        
        cout << "\nHotel editado com sucesso!" << endl;

    } catch (const invalid_argument& e) {
        cout << "Erro de formato nos dados: " << e.what() << endl;
    
    } catch (const runtime_error& e) {
        cout << "Erro de negócio: " << e.what() << endl;
    }
}

void CtrlApresentacaoHotel::executarExcluirHotel(const string& codigoHotel) {
    cout << "\n--- Tela de Exclusão de Hotel (" << codigoHotel << ") ---" << endl;
    
    cout << "A exclusão de um hotel ira quartos e reservas vinculadas." << endl;
    cout << "Confirma a exclusão do hotel com código " << codigoHotel << "? (s/n): ";
    
    char resposta;
    cin >> resposta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (std::tolower(static_cast<unsigned char>(resposta)) != 's') {
        cout << "Exclusão cancelada." << endl;
        return;
    }

    try {
        // 1. Validação de Formato
        Codigo codigo;
        codigo.setValor(codigoHotel); 
        
        // 2. Chamada de Serviço
        servicoHotel->excluir(codigo);
        
        cout << "\nHotel excluído com sucesso!" << endl;

    } catch (const invalid_argument& e) {
        cout << "Erro de formato no código: " << e.what() << endl;
    
    } catch (const runtime_error& e) {
        cout << "Erro de negócio: " << e.what() << endl;
    }
}

//-----------------------------------------------//
// Implementação de CtrlApresentacaoGerente      //
//-----------------------------------------------//

CtrlApresentacaoGerente::CtrlApresentacaoGerente(IServicoGerente* servicoGerente,
                                                 IServicoAutenticacao* servicoAuth) {
    this->servicoGerente = servicoGerente;
    this->servicoAuth = servicoAuth;
}

void CtrlApresentacaoGerente::executarCadastro() {
    string nomeStr, emailStr, senhaStr;
    int ramalInt;

    cout << "\n--- Tela de Cadastro de Gerente ---" << endl;
    if (cin.rdbuf()->in_avail() > 0) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Nome (Ex: Ana Souza): ";
    getline(cin, nomeStr);
    cout << "Email (ex: ana@hotel.com): ";
    getline(cin, emailStr);
    cout << "Senha (Ex: A1b$2): ";
    getline(cin, senhaStr);
    cout << "Ramal (valor inteiro): ";          cin >> ramalInt;

    try {
        Nome nome;     nome.setValor(nomeStr);
        Email email;   email.setValor(emailStr);
        Senha senha;   senha.setValor(senhaStr);
        Ramal ramal;   ramal.setValor(ramalInt);

        servicoGerente->criar(nome, email, senha, ramal);
        servicoAuth->cadastrar(email, senha);

        cout << "Gerente cadastrado com sucesso!" << endl;

    } catch (const invalid_argument& e) {
        cout << "Erro de formato nos dados: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}

void CtrlApresentacaoGerente::executarPerfil(const Email& emailGerente) {
    cout << "\n--- Meu Perfil ---" << endl;
    auto gerenteOpt = servicoGerente->ler(emailGerente);
    if (!gerenteOpt) {
        cout << "Nao foi possivel carregar os dados do gerente." << endl;
        return;
    }

    const Gerente& gerente = *gerenteOpt;
    cout << "Nome: " << gerente.getNome().getValor() << endl;
    cout << "Email: " << gerente.getEmail().getValor() << endl;
    cout << "Ramal: " << gerente.getRamal().getValor() << endl;

    cout << "\nDeseja atualizar o perfil? (s/n): ";
    char resposta;
    cin >> resposta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (std::tolower(static_cast<unsigned char>(resposta)) != 's') {
        return;
    }

    string novoNome, novaSenha;
    int novoRamal;

    cout << "Novo nome (Ex: Ana Souza): ";
    getline(cin, novoNome);
    cout << "Nova senha (Ex: A1b$2): ";
    getline(cin, novaSenha);
    cout << "Novo ramal (valor inteiro): ";
    cin >> novoRamal;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    try {
        Nome nome;   nome.setValor(novoNome);
        Senha senha; senha.setValor(novaSenha);
        Ramal ramal; ramal.setValor(novoRamal);

        servicoGerente->editar(emailGerente, nome, senha, ramal);
        servicoAuth->cadastrar(emailGerente, senha);

        cout << "Perfil atualizado com sucesso!" << endl;
    } catch (const invalid_argument& e) {
        cout << "Erro de formato nos dados: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}
