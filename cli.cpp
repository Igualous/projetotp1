#include <iostream>
#include <stdexcept>
#include "interfaces.hpp"
#include "servicos_mem.hpp"     
#include "controladoras.hpp"

using namespace std;

void executarMenuGerente(CtrlApresentacaoHotel* ctrlHotel);

int main() {
    ServicoAutenticacaoMem sAuth;
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
    CtrlApresentacaoHotel ctrlHotel(&sHotel);

    cout << "Bem-vindo ao Sistema de Gestao de Hoteis!" << endl;
    
    while (true) {
        cout << "\nMenu Principal:" << endl;
        cout << "1. Login" << endl;
        cout << "2. Cadastrar-se como Hospede" << endl;
        cout << "3. Sair" << endl;
        cout << "Escolha uma opcao: ";

        int opcao;
        cin >> opcao;

        switch (opcao) {
            case 1:
                if (ctrlAuth.executar()) { 
                    cout << "Login bem-sucedido!" << endl;
                }
                break;
            case 2:
                ctrlHosp.executarCadastro(); 
                break;
            case 3:
                cout << "Saindo... Obrigado!" << endl;
                return 0; 
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
                break;
        }
    }
    return 0;
}

void executarMenuGerente(CtrlApresentacaoHotel* ctrlHotel) {
    while (true) {
        cout << "\n--- Menu do Gerente ---" << endl;
        cout << "1. Meu Perfil" << endl;
        cout << "2. Meus Hoteis" << endl;
        cout << "3. Criar Hotel" << endl;
        cout << "4. Voltar ao Menu Principal" << endl;
        cout << "Escolha uma opcao: ";

        int opcao;
        cin >> opcao;
        
        switch (opcao) {
            case 1:
                cout << "Fluxo 'Meu Perfil' ainda nao implementado." << endl;
                // Aqui você chamaria: ctrlGerente->executarPerfil();
                break;
            case 2:
                cout << "Fluxo 'Meus Hoteis' ainda nao implementado." << endl;
                // Aqui você chamaria: ctrlHotel->executarListagem();
                break;
            case 3:
                // Chama a controladora que acabamos de implementar
                ctrlHotel->executarCadastroHotel();
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