#include <iostream>
#include <stdexcept>
#include <limits>
#include "interfaces.hpp"
#include "servicos_mem.hpp"     
#include "controladoras.hpp"

using namespace std;

void limpa() {
    #ifdef _WIN32
        // Comando para limpar o terminal no Windows
        std::system("cls");
    #else
        // Comando para limpar o terminal em sistemas Unix-like (Linux, macOS, etc.)
        std::system("clear");
    #endif
}

void espera() {
    double cont = 0;
    while (cont < 99999) {
        cont += 0.001;
    }
}
void executarMenuGerente(CtrlApresentacaoHotel* ctrlHotel,
                         CtrlApresentacaoGerente* ctrlGerente,
                         const Email& emailGerente);

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
    CtrlApresentacaoQuarto ctrlQuarto(&sQuarto);
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
                    executarMenuGerente(&ctrlHotel, &ctrlGerente, emailAutenticado);
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
                         const Email& emailGerente) {
    while (true) {
        cout << "\n--- Menu do Gerente ---" << endl;
        cout << "1. Meu Perfil" << endl;
        cout << "2. Meus Hoteis" << endl;
        cout << "3. Criar Hotel" << endl;
        cout << "4. Voltar ao Menu Principal" << endl;
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
                cout << "Retornando ao menu principal..." << endl;
                return; // Sai deste 'while(true)' e volta para o 'main'
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }
    }
}




