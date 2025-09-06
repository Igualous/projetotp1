#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED

#include "dominios.hpp"

using namespace std;

class Projeto {
    private:
        Codigo codigo;
        Prioridade prioridade;
    public:
        void setCodigo(Codigo);
        Codigo getCodigo();
        void setPrioridade(Prioridade);
        Prioridade getPrioridade();
};

inline void Projeto::setCodigo(Codigo codigo) {
    this->codigo = codigo;
}

inline Codigo Projeto::getCodigo() {
    return codigo;
}

inline void Projeto::setPrioridade(Prioridade prioridade) {
    this->prioridade = prioridade;
    }


inline Prioridade Projeto::getPrioridade() {
     return prioridade;
}


#endif // ENTIDADES_HPP_INCLUDED
