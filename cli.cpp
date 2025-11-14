/**
 * @file cli.cpp
 * @brief Ponto de entrada da interface de linha de comando do sistema.
 *
 * Responsavel por montar os servicos em memoria, injetar as controladoras
 * e disponibilizar menus para gerentes e hospedes.
 */
#include <iostream>
#include <stdexcept>
#include <limits>
#include "interfaces.hpp"
#include "servicos_mem.hpp"
#include "controladoras.hpp"

using namespace std;

/**
 * @brief Limpa a tela de acordo com o sistema operacional.
 */
void limpa() {
    #ifdef _WIN32
        // Comando para limpar o terminal no Windows
        std::system("cls");
    #else
        // Comando para limpar o terminal em sistemas Unix-like (Linux, macOS, etc.)
        std::system("clear");
    #endif
}

/**
 * @brief Gera uma pequena espera para que o usuario leia as mensagens.
 */
void espera() {
    double cont = 0;
    while (cont < 99999) {
        cont += 0.001;
    }
}
/**
 * @brief Menu principal exibido apos o login do gerente.
 */
void executarMenuGerente(CtrlApresentacaoHotel* ctrlHotel,
                         CtrlApresentacaoGerente* ctrlGerente,
                         CtrlApresentacaoReserva* ctrlReserva,
                         const Email& emailGerente);

/**
 * @brief Instancia os servicos e inicia o loop principal da CLI.
 */
int main() {
    ServicoAutenticacaoMem sAuth;
    ServicoGerenteMem      sGerente;
    ServicoHospedeMem      sHosp;
    ServicoHotelMem        sHotel;
    ServicoQuartoMem       sQuarto;
    ServicoReservaMem      sRes;
    
    sHosp.setServicoReserva(&sRes);
    sHotel.setServicosRelacionados(&sQuarto, &sRes);
    sQuarto.setServicoReserva(&sRes);
    sRes.setServicosRelacionados(&sHotel, &sQuarto, &sHosp);

    CtrlApresentacaoAutenticacao ctrlAuth(&sAuth);
    CtrlApresentacaoHospede ctrlHosp(&sHosp);
    CtrlApresentacaoReserva ctrlReserva(&sRes);
    CtrlApresentacaoQuarto ctrlQuarto(&sQuarto, &ctrlReserva);
    CtrlApresentacaoHotel ctrlHotel(&sHotel, &ctrlQuarto);
    CtrlApresentacaoGerente ctrlGerente(&sGerente, &sAuth);

    cout << "Bem-vindo ao Sistema de Gestao de Hoteis!" << endl;
    
    while (true) {
        cout << "\nMenu Principal:" << endl;
        cout << "1. Login" << endl;
        cout << "2. Cadastrar-se como Hospede" << endl;
        cout << "3. Cadastrar-se como Gerente" << endl;
        cout << "4. Sair" << endl;
        cout << "Escolha uma opcao: ";

        int opcao;
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        limpa();

        switch (opcao) {
            case 1: {
                Email emailAutenticado;
                if (ctrlAuth.executar(emailAutenticado)) {
                    cout << "Login bem-sucedido!" << endl;
                    espera();
                    executarMenuGerente(&ctrlHotel, &ctrlGerente, &ctrlReserva, emailAutenticado);
                }
                break;
            }
            case 2:
                ctrlHosp.executarCadastro(); 
                break;
            case 3:
                ctrlGerente.executarCadastro();
                break;
            case 4:
                cout << "Saindo... Obrigado!" << endl;
                espera();

                return 0; 
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }
    }
    return 0;
}

void executarMenuGerente(CtrlApresentacaoHotel* ctrlHotel,
                         CtrlApresentacaoGerente* ctrlGerente,
                         CtrlApresentacaoReserva* ctrlReserva,
                         const Email& emailGerente) {
    while (true) {
        cout << "\n--- Menu do Gerente ---" << endl;
        cout << "1. Meu Perfil" << endl;
        cout << "2. Meus Hoteis" << endl;
        cout << "3. Criar Hotel" << endl;
        cout << "4. Reservas" << endl;
        cout << "5. Voltar ao Menu Principal" << endl;
        cout << "Escolha uma opcao: ";

        int opcao;
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcao) {
            case 1:
                ctrlGerente->executarPerfil(emailGerente);
                break;
            case 2:
                ctrlHotel->executarListarHoteis(emailGerente);
                break;
            case 3:
                ctrlHotel->executarCadastroHotel(emailGerente);
                break;
            case 4:
                if (!ctrlReserva) {
                    cout << "Funcionalidade de reservas indisponivel." << endl;
                    break;
                }
                while (true) {
                    cout << "\n--- Reservas ---" << endl;
                    cout << "1. Listar reservas por hotel" << endl;
                    cout << "2. Listar reservas por hospede" << endl;
                    cout << "3. Voltar" << endl;
                    cout << "Escolha uma opcao: ";

                    int opReserva;
                    cin >> opReserva;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (opReserva == 1) {
                        cout << "Informe o codigo do hotel: ";
                        string codHotel;
                        cin >> codHotel;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        ctrlReserva->executarListarReservasPorHotel(codHotel);
                    } else if (opReserva == 2) {
                        cout << "Informe o email do hospede: ";
                        string emailHospede;
                        cin >> emailHospede;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        ctrlReserva->executarListarReservasPorHospede(emailHospede);
                    } else if (opReserva == 3) {
                        break;
                    } else {
                        cout << "Opcao invalida." << endl;
                    }
                }
                break;
            case 5:
                cout << "Retornando ao menu principal..." << endl;
                return; // Sai deste 'while(true)' e volta para o 'main'
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }
    }
}




