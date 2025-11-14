# Sistema de Gestão de Hotéis – TP1

Projeto desenvolvido para a disciplina **Técnicas de Programação 1 (CIC0197)** da Universidade de Brasília. O objetivo é aplicar orientação a objetos, arquitetura em camadas e boas práticas de desenvolvimento na construção de um sistema simples de gestão de hotéis com interface em linha de comando.

## Visão Geral

- Cadastro e autenticação de gerentes e hóspedes.
- Gestão de hotéis, quartos e reservas com validações de negócio (capacidade, datas, conflitos etc.).
- Camada de serviços desacoplada via interfaces (`interfaces.hpp`), com implementação em memória (`servicos_mem.*`), facilitando substituição futura por persistência real.
- Interface de apresentação (`controladoras.*` + `cli.cpp`) totalmente desacoplada dos serviços por meio de injeção de dependências.

## Estrutura em Camadas

1. **Domínios (`dominios.*`)**  
   Value objects responsáveis por validar todos os dados de entrada (Email, Senha, Data, Dinheiro, Código etc.).
2. **Entidades (`entidades.*`)**  
   Agregam domínios validados para representar Gerente, Hóspede, Hotel, Quarto e Reserva.
3. **Serviços (`interfaces.hpp` + `servicos_mem.*`)**  
   Regras de negócio e persistência em memória para autenticação, usuários, hotéis, quartos e reservas.
4. **Apresentação (`controladoras.*` + `cli.cpp`)**  
   Interface de linha de comando que orquestra os fluxos usando as interfaces de serviço.

## Requisitos

- Compilador C++17 ou superior (o projeto foi configurado usando MinGW no Code::Blocks/VS Code).
- Opcional: [Doxygen](https://www.doxygen.nl/) 1.9+ para gerar documentação.

## Como Compilar e Executar

### Via VS Code
1. Abra a pasta do projeto.
2. Use a task `build cli` (Ctrl+Shift+B) para gerar `output/cli.exe`.
3. Execute `output/cli.exe` no terminal para iniciar a interface.

### Via linha de comando (g++)
```bash
g++ -Wall -Wextra -std=c++17 -g3 ^
    cli.cpp dominios.cpp entidades.cpp servicos_mem.cpp controladoras.cpp ^
    -o output/cli.exe
output\cli.exe
```

### Testes
- `tests_dominios.cpp`: valida domínios, entidades e um smoke test básico dos serviços.
- `tests_smoke.cpp`: percorre todo o fluxo em memória (criação de gerente/hóspede/hotel/quarto/reservas).

Compilar:
```bash
g++ -Wall -Wextra -std=c++17 -g3 tests_dominios.cpp dominios.cpp entidades.cpp servicos_mem.cpp -o output/tests_dominios.exe
g++ -Wall -Wextra -std=c++17 -g3 tests_smoke.cpp dominios.cpp entidades.cpp servicos_mem.cpp controladoras.cpp -o output/tests_smoke.exe
```

## Documentação (Doxygen)

O arquivo `Doxyfile` já está configurado para percorrer todo o projeto e usar o `README.md` como página inicial. Para gerar a documentação HTML:

```bash
doxygen Doxyfile
```

Os arquivos ficarão em `docs/html/index.html`.

## Autores

- **Arthur Fernandes Vargas** – [github.com/aarthurv77](https://github.com/aarthurv77)
- **Igor Araújo Rodrigues** – [github.com/Igualous](https://github.com/Igualous)
- **Hendrick Henrique Moreno Quevedo** – [github.com/Hendrickhmq](https://github.com/Hendrickhmq)
