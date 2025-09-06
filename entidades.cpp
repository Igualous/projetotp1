#include <iostream>
#include "entidades.hpp"

using namespace std;
int main () {
    Projeto projeto;

    Codigo codigo;

    Prioridade prioridade;

    codigo.setValor(10);
    prioridade.setValor(20);

    projeto.setCodigo(codigo);
    projeto.setPrioridade(prioridade);

    cout << projeto.getCodigo().getValor() << endl;
    cout << projeto.getPrioridade().getValor() << endl;

    return 0;
}
