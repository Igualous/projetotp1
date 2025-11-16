/**
 * @file controladoras.cpp
 * @brief Implementa os fluxos da camada de apresentacao baseados em CLI.
 */
#include "controladoras.hpp"
#include "globals.hpp"
#include <iostream>
#include <string>
#include <stdexcept> 
#include <limits>
#include <cctype>
#include <sstream>

using namespace std;

namespace {

string lerLinha(const string& prompt) {
    cout << prompt;
    string valor;
    getline(cin, valor);
    return valor;
}

template<typename DomainType>
DomainType lerDominioString(const string& prompt) {
    DomainType dominio;
    while (true) {
        string entrada = lerLinha(prompt);
        try {
            dominio.setValor(entrada);
            return dominio;
        } catch (const invalid_argument& e) {
            cout << "Entrada invalida: " << e.what() << ". Tente novamente." << endl;
        }
    }
}

template<typename DomainType>
DomainType lerDominioInt(const string& prompt) {
    DomainType dominio;
    while (true) {
        string entrada = lerLinha(prompt);
        try {
            size_t pos = 0;
            int valor = stoi(entrada, &pos);
            if (pos != entrada.size()) {
                throw invalid_argument("Informe apenas numeros inteiros.");
            }
            dominio.setValor(valor);
            return dominio;
        } catch (const invalid_argument& e) {
            cout << "Entrada invalida: " << e.what() << ". Tente novamente." << endl;
        } catch (const out_of_range&) {
            cout << "Entrada invalida: numero fora do intervalo permitido. Tente novamente." << endl;
        }
    }
}

Data lerDataFormato(const string& prompt) {
    while (true) {
        string linha = lerLinha(prompt);
        if (linha.empty()) {
            cout << "Entrada invalida: use o formato 'DD MES AAAA'." << endl;
            continue;
        }
        istringstream iss(linha);
        int dia = 0;
        int ano = 0;
        string mes;
        if (!(iss >> dia >> mes >> ano)) {
            cout << "Entrada invalida: use o formato 'DD MES AAAA' (ex: 05 JAN 2026)." << endl;
            continue;
        }
        try {
            Data data;
            data.setValor(dia, mes, ano);
            return data;
        } catch (const invalid_argument& e) {
            cout << "Data invalida: " << e.what() << ". Tente novamente." << endl;
        }
    }
}

} // namespace

//-----------------------------------------------//
// Implementacao de CtrlApresentacaoAutenticacao //
//-----------------------------------------------//
CtrlApresentacaoAutenticacao::CtrlApresentacaoAutenticacao(IServicoAutenticacao* servico) {
    this->servicoAuth = servico;
}

bool CtrlApresentacaoAutenticacao::executar(Email& emailAutenticado) {
    limpa();
    header();
    cout << "\n--- Tela de Login ---" << endl;

    Email email = lerDominioString<Email>("Digite seu email: ");
    Senha senha = lerDominioString<Senha>("\nDigite sua senha: ");

    if (servicoAuth->autenticar(email, senha)) {
        emailAutenticado = email;
        return true;
    }

    cout << "Erro: Email ou senha incorretos." << endl;
    return false;
}


//------------------------------------------//
// Implementacao de CtrlApresentacaoHospede //
//------------------------------------------//

CtrlApresentacaoHospede::CtrlApresentacaoHospede(IServicoHospede* servicoHospede,
                                                 IServicoAutenticacao* servicoAuth) {
    this->servicoHospede = servicoHospede;
    this->servicoAuth = servicoAuth;
}

void CtrlApresentacaoHospede::executarCadastro() {
    limpa();
    header();
    cout << "\n--- Tela de Cadastro de Hospede ---" << endl;

    Nome nome       = lerDominioString<Nome>("Nome (Ex: Joao Silva): ");
    Email email     = lerDominioString<Email>("Email (ex: joao@email.com): ");
    Senha senha     = lerDominioString<Senha>("Senha (Ex: A1b$2): ");
    Cartao cartao   = lerDominioString<Cartao>("Cartao (16 digitos): ");
    Endereco end    = lerDominioString<Endereco>("Endereco (Ex: Rua 1): ");

    try {
        servicoHospede->cadastrar(nome, email, senha, cartao, end);
        if (servicoAuth) {
            servicoAuth->cadastrar(email, senha);
        }
        cout << "Cadastro realizado com sucesso!" << endl;
        espera();

    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}



//-----------------------------------------------//
// Implementacao de CtrlApresentacaoHotel        //
//-----------------------------------------------//

CtrlApresentacaoHotel::CtrlApresentacaoHotel(IServicoHotel* servico, CtrlApresentacaoQuarto* ctrlQuarto) {
    this->servicoHotel = servico;
    this->ctrlQuarto = ctrlQuarto;
}

void CtrlApresentacaoHotel::executarCadastroHotel(const Email& emailGerente) {
    limpa();
    header();
    cout << "\n--- Tela de Cadastro de Hotel ---" << endl;

    Codigo codigo = lerDominioString<Codigo>("Codigo (10 chars, ex: hotel12345): ");
    Nome nome     = lerDominioString<Nome>("Nome (Ex: Hotel Central): ");
    Endereco end  = lerDominioString<Endereco>("Endereco (Ex: Rua 1): ");
    Telefone tel  = lerDominioString<Telefone>("Telefone (Ex: +12345678901234): ");

    try {
        servicoHotel->criar(codigo, nome, end, tel, emailGerente);
        cout << "Hotel cadastrado com sucesso!" << endl;
        espera();

    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}


void CtrlApresentacaoHotel::executarListarHoteis(const Email& emailGerente) {
    limpa();
    header();
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
        
        const int totalHoteis = static_cast<int>(lista.size());
        if (indexEscolhido < 0 || indexEscolhido >= totalHoteis) {
            cout << "indice invalido. Voltando..." << endl;
            return;
        }
        const Hotel& hotelEscolhido = lista.at(indexEscolhido);
        string codigoHotelEscolhido = hotelEscolhido.getCodigo().getValor();
        string nomeHotelEscolhido = hotelEscolhido.getNome().getValor();
        
        limpa();
        header();
        cout << "Hotel selecionado: " << nomeHotelEscolhido << endl;


        cout << "\n1 - Editar hotel" << endl;
        cout << "2 - Excluir hotel" << endl;
        cout << "3 - Gerenciar quartos" << endl;
        cout << "4 - Criar quartos" << endl;
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
            if (ctrlQuarto) {
                ctrlQuarto->executarListarQuartos(codigoHotelEscolhido);
            } else {
                cout << "Erro: dependencia CtrlApresentacaoQuarto nula." << endl;
            }
            break;
            case 4:
            if (ctrlQuarto) {
                ctrlQuarto->executarCadastroQuarto(codigoHotelEscolhido);
            } else {
                cout << "Erro: dependencia CtrlApresentacaoQuarto nula." << endl;                
            }
            break;
            default:
                cout << "opcao invalida" << endl;
        }

    } catch (const runtime_error& e) {
        cout << "Erro ao listar hoteis: " << e.what() << endl;
    }
}

void CtrlApresentacaoHotel::executarEditarHotel(const string& codigoHotel) {
    limpa();
    header();
    cout << "\n--- Tela de Edicao de Hotel (" << codigoHotel << ") ---" << endl;

    Codigo codigo;
    try {
        codigo.setValor(codigoHotel);
    } catch (const invalid_argument& e) {
        cout << "Erro: Codigo do hotel invalido: " << e.what() << endl;
        return;
    }

    optional<Hotel> hotelAtualOpt;
    try {
        hotelAtualOpt = servicoHotel->ler(codigo);
    } catch (const runtime_error& e) {
        cout << "Erro ao buscar hotel: " << e.what() << endl;
        return;
    }

    if (!hotelAtualOpt) {
        cout << "Erro de negocio: Hotel com codigo " << codigoHotel << " nao encontrado." << endl;
        return;
    }
    const Hotel& hotelAtual = *hotelAtualOpt;

    string promptNome = "Digite o NOVO NOME (atual: ";
    promptNome += hotelAtual.getNome().getValor();
    promptNome += "): ";

    string promptEnd  = "Digite o NOVO ENDERECO (atual: ";
    promptEnd += hotelAtual.getEndereco().getValor();
    promptEnd += "): ";

    string promptTel  = "Digite o NOVO TELEFONE (atual: ";
    promptTel += hotelAtual.getTelefone().getValor();
    promptTel += "): ";

    Nome nome       = lerDominioString<Nome>(promptNome);
    Endereco end    = lerDominioString<Endereco>(promptEnd);
    Telefone tel    = lerDominioString<Telefone>(promptTel);

    try {
        servicoHotel->editar(codigo, nome, end, tel);
        cout << "\nHotel editado com sucesso!" << endl;
        espera();

    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}




void CtrlApresentacaoHotel::executarExcluirHotel(const string& codigoHotel) {
    limpa();
    header();
    cout << "\n--- Tela de Exclusao de Hotel (" << codigoHotel << ") ---" << endl;
    
    cout << "A exclusao de um hotel ira quartos e reservas vinculadas." << endl;
    cout << "Confirma a exclusao do hotel com codigo " << codigoHotel << "? (s/n): ";
    
    char resposta;
    cin >> resposta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (std::tolower(static_cast<unsigned char>(resposta)) != 's') {
        cout << "Exclusao cancelada." << endl;
        return;
    }

    try {
        // 1. Validacao de Formato
        Codigo codigo;
        codigo.setValor(codigoHotel); 
        
        // 2. Chamada de Servico
        servicoHotel->excluir(codigo);
        
        cout << "\nHotel excluAdo com sucesso!" << endl;
        espera();
    } catch (const invalid_argument& e) {
        cout << "Erro de formato no codigo: " << e.what() << endl;
    
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}

//-----------------------------------------------//
// Implementacao de CtrlApresentacaoGerente      //
//-----------------------------------------------//

CtrlApresentacaoGerente::CtrlApresentacaoGerente(IServicoGerente* servicoGerente,
                                                 IServicoAutenticacao* servicoAuth) {
    this->servicoGerente = servicoGerente;
    this->servicoAuth = servicoAuth;
}

void CtrlApresentacaoGerente::executarCadastro() {
    limpa();
    header();
    cout << "\n--- Tela de Cadastro de Gerente ---" << endl;

    Nome nome     = lerDominioString<Nome>("Nome (Ex: Ana Souza): ");
    Email email   = lerDominioString<Email>("Email (ex: ana@hotel.com): ");
    Senha senha   = lerDominioString<Senha>("Senha (Ex: A1b$2): ");
    Ramal ramal   = lerDominioString<Ramal>("Ramal (00-50, sempre dois digitos): ");

    try {
        servicoGerente->criar(nome, email, senha, ramal);
        servicoAuth->cadastrar(email, senha);
        cout << "Gerente cadastrado com sucesso!" << endl;
        espera();

    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}


void CtrlApresentacaoGerente::executarPerfil(const Email& emailGerente) {
    limpa();
    header();
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

    cout << "\n1 - Editar Perfil";
    cout << "\n2 - Remover Perfil";
    cout << "\n3 - Voltar";
    cout << "\n\nEscolha o que desejar fazer: ";

    int resposta;
    cin >> resposta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    if (resposta == 1) {
        string promptNome = "Novo nome (atual: " + gerente.getNome().getValor() + "): ";
        Nome novoNome     = lerDominioString<Nome>(promptNome);
        Senha novaSenha   = lerDominioString<Senha>("Nova senha (Ex: A1b$2): ");
        Ramal novoRamal   = lerDominioString<Ramal>("Novo ramal (00-50, dois digitos): ");
    
        try {
            servicoGerente->editar(emailGerente, novoNome, novaSenha, novoRamal);
            servicoAuth->cadastrar(emailGerente, novaSenha);
    
            cout << "Perfil atualizado com sucesso!" << endl;
            espera();
        } catch (const runtime_error& e) {
            cout << "Erro de negocio: " << e.what() << endl;
        }
    } else if (resposta == 2) {
        while (true) {
            cout << "Tem certeza que deseja excluir perfil? (S/N): ";
            char opcao;
            cin >> opcao;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
            if (opcao == 'S' || opcao == 's') {
                servicoGerente->excluir(emailGerente);
                cout << "Perfil excluido com sucesso!";
                espera();
                break;
            } else if (opcao == 'N' || opcao == 'n') {
                break;
            }
        }
    } else if (resposta == 3) {
        return;
    } else {
        cout << "Opcao invalida." << endl;
    }
}


//-----------------------------------------------//
// Implementacao de CtrlApresentacaoQuarto       //
//-----------------------------------------------//

CtrlApresentacaoQuarto::CtrlApresentacaoQuarto(IServicoQuarto* servico) {
    this->servicoQuarto = servico;
}

CtrlApresentacaoQuarto::CtrlApresentacaoQuarto(IServicoQuarto* servico, CtrlApresentacaoReserva* ctrlReserva) {
    this->servicoQuarto = servico;
    this->ctrlReserva = ctrlReserva;
}

void CtrlApresentacaoQuarto::executarCadastroQuarto(const string& codigoHotel) {
    limpa();
    header();
    cout << "\n--- Tela de Cadastro de Quarto ---" << endl;

    Numero numeroDom         = lerDominioInt<Numero>("Numero do quarto: ");
    Capacidade capacidadeDom = lerDominioInt<Capacidade>("Capacidade do quarto: ");
    Dinheiro diariaDom       = lerDominioInt<Dinheiro>("Diaria (em centavos): ");
    Ramal ramalDom           = lerDominioString<Ramal>("Ramal (00-50, dois digitos): ");

    try {
        Codigo codigoHotelDom;          codigoHotelDom.setValor(codigoHotel);
        servicoQuarto->criar(codigoHotelDom, numeroDom, capacidadeDom, diariaDom, ramalDom);
        cout << "Quarto cadastrado com sucesso!" << endl;
        espera();

    } catch (const invalid_argument& e) {
        cout << "Erro de formato nos dados: " << e.what() << endl;
    
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}


void CtrlApresentacaoQuarto::executarListarQuartos(const string& codigoHotel) {
    limpa();
    header();
    cout << "\n--- Meus Quartos ---" << endl;

    // validacao de parametro
    Codigo codigoHotelDom;
    try {
        codigoHotelDom.setValor(codigoHotel);
    } catch(const std::invalid_argument& e) {
        cout << "Codigo de hotel invAlido" << endl;
    } 

    try {
        auto lista = servicoQuarto->listar(codigoHotelDom);
        if (lista.empty()) {
            cout << "Voce ainda nao possui quartos cadastrados." << endl;
            return;
        }

        int index = 0;
        for (const auto& quarto : lista) {
            cout << "[" << index << "] " 
                 <<  "Numero:: " << quarto.getNumero().getValor()
                 << " | Capacidade: " << quarto.getCapacidade().getValor()
                 << " | Diaria: " << quarto.getDiaria().getValor()
                 << " | Ramal: " << quarto.getRamal().getValor()
                 << endl;
            index++;
        }

        cout << "\n1 - Gerenciar quartos" << endl;
        cout << "2 - Voltar" << endl;

        int opcaoAcao;
        cin >> opcaoAcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar buffer
        
        if (opcaoAcao != 1) {
            return;
        }

        cout << "\n\nSelecione o indice do quarto que deseja gerenciar: ";
        int indexEscolhido;
        cin >> indexEscolhido;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar buffer
        
        const int totalQuartos = static_cast<int>(lista.size());
        if (indexEscolhido < 0 || indexEscolhido >= totalQuartos) {
            cout << "indice invalido. Voltando..." << endl;
            return;
        }
        const Quarto& QuartoEscolhido = lista.at(indexEscolhido);
        int numeroQuartoEscolhido = QuartoEscolhido.getNumero().getValor();
        limpa();
        header();
        cout << "Quarto selecionado: " << numeroQuartoEscolhido << endl;


        cout << "\n1 - Editar quarto" << endl;
        cout << "2 - Excluir quarto" << endl;
        cout << "3 - Gerenciar reservas" << endl;
        cout << "\nO que deseja fazer?: ";
        
        int opcaoGerencia;
        cin >>  opcaoGerencia;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpar buffer 

        switch (opcaoGerencia) {
            case 1:
                executarEditarQuarto(codigoHotel, numeroQuartoEscolhido); 
            break;
            case 2:
                executarExcluirQuarto(codigoHotel, numeroQuartoEscolhido);
            break;
            case 3:
                if (ctrlReserva) {
                    ctrlReserva->executarGerenciar(codigoHotel, numeroQuartoEscolhido);
                } else {
                    cout << "Erro: dependencia CtrlApresentacaoReserva nula." << endl;
                }
            break;
            default:
                cout << "opcao invalida" << endl;
        }

    } catch (const runtime_error& e) {
        cout << "Erro ao listar quartos: " << e.what() << endl;
    }
}

// **ASSINATURA CORRIGIDA**: O segundo parAmetro deve ser string, assim como na chamada de listar
void CtrlApresentacaoQuarto::executarEditarQuarto(const string& codigoHotel, const int& numeroQuarto) { 
    limpa();
    header();
    cout << "\n--- Tela de Edicao de Quarto (" << numeroQuarto << ") ---" << endl;

    Numero numeroDom;
    Codigo codigoDom;
    try {
        codigoDom.setValor(codigoHotel);
        numeroDom.setValor(numeroQuarto);
    } catch (const invalid_argument& e) {
        cout << "Erro: Codigo/Numero de quarto invalido: " << e.what() << endl;
        return;
    }

    optional<Quarto> quartoAtualOpt;
    try {
        quartoAtualOpt = servicoQuarto->ler(codigoDom, numeroDom);
    } catch (const runtime_error& e) {
        cout << "Erro ao buscar quarto: " << e.what() << endl;
        return;
    }
    
    if (!quartoAtualOpt) {
        cout << "Erro de negocio: Quarto com numero " << numeroQuarto<< " nao encontrado." << endl;
        return;
    }
    const Quarto& quartoAtual = *quartoAtualOpt;

    string promptCap = "Digite a NOVA CAPACIDADE (atual: ";
    promptCap += to_string(quartoAtual.getCapacidade().getValor());
    promptCap += "): ";

    string promptDia = "Digite a NOVA DIARIA (atual: ";
    promptDia += to_string(quartoAtual.getDiaria().getValor());
    promptDia += "): ";

    string promptRam = "Digite o NOVO RAMAL (atual: ";
    promptRam += quartoAtual.getRamal().getValor();
    promptRam += "): ";

    Capacidade capacidadeDom = lerDominioInt<Capacidade>(promptCap);
    Dinheiro diariaDom       = lerDominioInt<Dinheiro>(promptDia);
    Ramal ramalDom           = lerDominioString<Ramal>(promptRam);

    try {
        servicoQuarto->editar(codigoDom, numeroDom, capacidadeDom, diariaDom, ramalDom);
        cout << "\nQuarto editado com sucesso! " << endl;

    } catch (const invalid_argument& e) {
        cout << "Erro de formato nos dados: " << e.what() << endl;
    
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}



// **ASSINATURA CORRIGIDA**: O segundo parAmetro deve ser string
void CtrlApresentacaoQuarto::executarExcluirQuarto(const string& codigoHotel, const int& numeroQuarto) {
    limpa();
    header();
    cout << "\n--- Tela de Exclusao de Quarto (" << numeroQuarto << ") ---" << endl;
    
    cout << "A exclusao de um quarto ira excluir todas reservas vinculadas a ele." << endl;
    cout << "Confirma a exclusao do quarto com numero " << numeroQuarto << "? (s/n): ";
    
    char resposta;
    cin >> resposta;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (std::tolower(static_cast<unsigned char>(resposta)) != 's') {
        cout << "Exclusao cancelada." << endl;
        return;
    }

    try {
        // 1. Validacao de Formato
        // Converte string para int para validar o DomAnio
        Numero numero;
        numero.setValor(numeroQuarto); 

        Codigo codigo;
        codigo.setValor(codigoHotel);
        
        // 2. Chamada de Servico
        servicoQuarto->excluir(codigo, numero);
        
        cout << "\nQuarto excluAdo com sucesso!" << endl;
        espera();

    } catch (const invalid_argument& e) {
        cout << "Erro de formato no codigo: " << e.what() << endl;
    
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}

//-----------------------------------------------//
// Implementacao de CtrlApresentacaoReserva      //
//-----------------------------------------------//

CtrlApresentacaoReserva::CtrlApresentacaoReserva(IServicoReserva* servico) {
    this->servicoReserva = servico;
}

void CtrlApresentacaoReserva::executarGerenciar(const string& codigoHotel, const int& numeroQuarto) {
    limpa();
    header();
    cout << "\n--- Reservas do Quarto " << numeroQuarto << " (Hotel: " << codigoHotel << ") ---" << endl;

    // Lista por hotel e filtra pelo quarto
    try {
        Codigo ch; ch.setValor(codigoHotel);
        auto lista = servicoReserva->listarPorHotel(ch);
        int count = 0;
        for (const auto& r : lista) {
            if (r.getNumero().getValor() == numeroQuarto) {
                cout << "[" << count << "] "
                     << "Reserva: " << r.getCodigo().getValor()
                     << " | Hospede: " << r.getHospede().getValor()
                     << " | Chegada: " << r.getChegada().getValor()
                     << " | Partida: " << r.getPartida().getValor()
                     << " | Valor: " << r.getValor().getValor()
                     << endl;
                count++;
            }
        }

        cout << "\n1 - Criar reserva" << endl;
        cout << "2 - Editar reserva" << endl;
        cout << "3 - Excluir reserva" << endl;
        cout << "4 - Voltar" << endl;
        cout << "Escolha uma opcao: ";

        int op; cin >> op; cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (op) {
            case 1:
                executarCadastroReserva(codigoHotel, numeroQuarto);
            break;
            case 2:
            case 3: {
                Codigo codReserva = lerDominioString<Codigo>("Informe o codigo da reserva: ");
                if (op == 2) {
                    executarEditarReserva(codReserva.getValor());
                } else {
                    executarExcluirReserva(codReserva.getValor());
                }
                break;
            }
            default:
                cout << "Opcao invalida." << endl;
                break;
        }
    } catch (const invalid_argument& e) {
        cout << "Erro de formato: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}

void CtrlApresentacaoReserva::executarCadastroReserva(const string& codigoHotel, const int& numeroQuarto) {
    limpa();
    header();
    cout << "\n--- Nova Reserva ---" << endl;
    Codigo codReserva = lerDominioString<Codigo>("Codigo da reserva (10 chars): ");
    Email hospede     = lerDominioString<Email>("Email do hospede: ");
    Data chegada      = lerDataFormato("Chegada (DIA MES AAAA, ex: 10 JAN 2025): ");
    Data partida      = lerDataFormato("Partida (DIA MES AAAA): ");
    Dinheiro valor    = lerDominioInt<Dinheiro>("Valor total (centavos): ");

    try {
        Codigo codHotel;   codHotel.setValor(codigoHotel);
        Numero num;        num.setValor(numeroQuarto);

        servicoReserva->criar(codReserva, codHotel, num, hospede, chegada, partida, valor);
        cout << "Reserva criada com sucesso!" << endl;
    } catch (const invalid_argument& e) {
        cout << "Erro de formato: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}

void CtrlApresentacaoReserva::executarListarReservasPorHotel(const string& codigoHotel) {
    limpa();
    header();
    cout << "\n--- Reservas do Hotel " << codigoHotel << " ---" << endl;
    try {
        Codigo ch; ch.setValor(codigoHotel);
        auto lista = servicoReserva->listarPorHotel(ch);
        int idx = 0;
        for (const auto& r : lista) {
            cout << "[" << idx++ << "] "
                 << r.getCodigo().getValor() << " | Qto " << r.getNumero().getValor()
                 << " | Hospede " << r.getHospede().getValor()
                 << " | " << r.getChegada().getValor() << " -> " << r.getPartida().getValor()
                 << " | " << r.getValor().getValor() << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "Erro de formato: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}

void CtrlApresentacaoReserva::executarListarReservasPorHospede(const string& emailHospedeStr) {
    limpa();
    header();
    cout << "\n--- Reservas do Hospede " << emailHospedeStr << " ---" << endl;
    try {
        Email eh; eh.setValor(emailHospedeStr);
        auto lista = servicoReserva->listarPorHospede(eh);
        int idx = 0;
        for (const auto& r : lista) {
            cout << "[" << idx++ << "] "
                 << r.getCodigo().getValor() << " | Hotel " << r.getHotel().getValor()
                 << " | Qto " << r.getNumero().getValor()
                 << " | " << r.getChegada().getValor() << " -> " << r.getPartida().getValor()
                 << " | " << r.getValor().getValor() << endl;
        }
    } catch (const invalid_argument& e) {
        cout << "Erro de formato: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}

void CtrlApresentacaoReserva::executarEditarReserva(const string& codigoReserva) {
    limpa();
    header();
    cout << "\n--- Editar Reserva (" << codigoReserva << ") ---" << endl;
    Data novaChegada = lerDataFormato("Nova Chegada (DIA MES AAAA): ");
    Data novaPartida = lerDataFormato("Nova Partida (DIA MES AAAA): ");
    Dinheiro valor   = lerDominioInt<Dinheiro>("Novo Valor (centavos): ");

    try {
        Codigo cod; cod.setValor(codigoReserva);
        servicoReserva->editar(cod, novaChegada, novaPartida, valor);
        cout << "Reserva editada com sucesso!" << endl;
        espera();
    } catch (const invalid_argument& e) {
        cout << "Erro de formato: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}

void CtrlApresentacaoReserva::executarExcluirReserva(const string& codigoReserva) {
    limpa();
    header();
    cout << "\n--- Excluir Reserva (" << codigoReserva << ") ---" << endl;
    cout << "Confirma a exclusao? (s/n): ";
    char r; cin >> r; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (std::tolower(static_cast<unsigned char>(r)) != 's') {
        cout << "Exclusao cancelada." << endl;
        return;
    }
    try {
        Codigo cod; cod.setValor(codigoReserva);
        servicoReserva->excluir(cod);
        cout << "Reserva excluida com sucesso!" << endl;
        espera();
    } catch (const invalid_argument& e) {
        cout << "Erro de formato: " << e.what() << endl;
    } catch (const runtime_error& e) {
        cout << "Erro de negocio: " << e.what() << endl;
    }
}
