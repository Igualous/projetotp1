# Projeto Prático - Sistema de Gestão de Hotéis (Técnicas de Programação 1 - CIC0197)

## 📝 Sobre o Projeto

Sistema de software para gestão de pequenos hotéis, desenvolvido como avaliação para a disciplina de **Técnicas de Programação 1 (CIC0197)** da Universidade de Brasília (UnB), sob orientação do Prof. Fernando Albuquerque.

O objetivo do projeto é aplicar os conceitos de Programação Orientada a Objetos, arquitetura em camadas e boas práticas de desenvolvimento de software para criar um sistema robusto e bem estruturado.

## ✨ Funcionalidades

- [x] **Gestão de Hóspedes:** Cadastro, autenticação, visualização e edição de dados pessoais.
- [x] **Gestão de Hotéis:** Cadastro, edição e exclusão de hotéis e seus respectivos quartos.
- [x] **Sistema de Reservas:** Permite aos hóspedes criar, visualizar e gerenciar suas reservas, respeitando as regras de negócio.
- [x] **Validação de Dados:** Implementação de classes de domínio para garantir a integridade e o formato correto de todos os dados de entrada (Email, Senha, Data, Código, etc.), utilizando exceções para tratamento de erros.

## 🏛️ Arquitetura

O sistema segue uma **arquitetura em 3 camadas (3-Tier Architecture)** para garantir a separação de responsabilidades, modularidade e manutenibilidade do código.

1.  **Camada de Apresentação (Interface):**
    - Responsável pela interação com o usuário (através de uma interface de linha de comando - CLI).
    - Delega as solicitações do usuário para a camada de serviço.
    - Não contém nenhuma lógica de negócio.

2.  **Camada de Serviço (Lógica de Negócio):**
    - O "cérebro" do sistema. Implementa todas as regras de negócio (ex: "um hóspede não pode ter mais de 4 reservas").
    - Orquestra as operações, utilizando a camada de persistência para acessar os dados.
    - É completamente independente da interface de usuário.

3.  **Camada de Persistência (Dados):**
    - Responsável por armazenar e recuperar os objetos do sistema.
    - Abstrai o método de armazenamento, que pode ser em memória (usando contêineres da STL) ou em um banco de dados como o SQLite.

## 🛠️ Tecnologias e Ferramentas

- **Linguagem:** C++
- **Ambiente de Desenvolvimento (IDE):** Code::Blocks
- **Controle de Versão:** Git & GitHub
- **Documentação:** Doxygen (planejado)
- **Banco de Dados (Opcional):** SQLite (planejado)

## 🚀 Como Executar

**Pré-requisitos:**
- Um compilador C++ (g++)
- Code::Blocks IDE

**Passo a Passo:**

1.  Clone o repositório para a sua máquina local:
    ```bash
    git clone [https://github.com/](https://github.com/)[SEU-USUARIO-AQUI]/projetotp1.git
    ```
2.  Navegue até o diretório do projeto:
    ```bash
    cd projetotp1
    ```
3.  Abra o arquivo de projeto `lab1.cbp` com o Code::Blocks.
4.  Compile e execute o projeto (atalho padrão: `F9`).

## 👨‍💻 Autores

- **Arthur Fernandes Vargas** - github.com/aarthurv77 (https://github.com/aarthurv77)
- **Igor Araújo Rodrigues** - [github.com/[USUARIO_ALUNO_2]](https://github.com/[USUARIO_ALUNO_2])
- **Hendrick Henrique Moreno Quevedo** - [github.com/[USUARIO_ALUNO_3]](https://github.com/[USUARIO_ALUNO_3])
