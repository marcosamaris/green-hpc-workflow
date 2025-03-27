# Workflow Energy Consumption Simulator

Este repositório contém scripts e ferramentas para simular o consumo de energia durante a execução de workflows científicos utilizando o **WRENCH**. O objetivo é explorar e entender como diferentes configurações de workflows impactam o consumo de energia.

## Objetivo do Projeto

Proporcionar uma base para a simulação de consumo energético em workflows, permitindo estudos e análises que contribuam para o desenvolvimento de estratégias mais eficientes e sustentáveis.

## Funcionalidades

- Simulação de consumo de energia para diferentes workflows científicos.
- Geração de workflows sintéticos com ferramentas como o **Wfcommons**.
- Coleta e exportação de métricas de consumo energético em arquivo no formato **CSV**.

## Ferramentas Utilizadas

- **WRENCH**: Framework de simulação para sistemas de gerenciamento de workflows.
- **Wfcommons**: Ferramenta para modelagem e geração de workflows sintéticos.
- **Python**: Para a automação e análise dos resultados.
- **C++**: Para o desenvolvimento da simulação.
- **Docker**: Para configuração de ambientes reprodutíveis.

## Estrutura do Repositório

```bash
GreenWorkSim/
├── datas/                 # Dados obtidos através das simulações
├── include/               # Cabeçalhos de código
├── platforms/             # Arquivos e scripts relacionados a diferentes plataformas simuladas
├── src/                   # Código-fonte principal do projeto
├── workflows/             # Workflows utilizados para as simulações
├── docker-compose.yml     # Arquivo de configuração para ambientes Docker
└── start.sh               # Script para inicializar a simulação

```

## Pré-requisitos

Antes de começar, certifique-se de ter:

- Python 3.8 ou superior
- Docker
- Wfcommons CLI

## Como Usar

### 1. Configuração do Ambiente

Clone o repositório e instale as dependências:

```bash
git clone https://github.com/feliperafaelbarbosa/GreenWorkSim.git
cd GreenWorkSim
```

### 2. Geração de Workflows

Crie workflows sintéticos utilizando o script `wfgenrecipe.py` na pasta src e os arquivos serão gerados na pasta `workflows/`.

### 3. Compilação e Build do Projeto

Crie uma pasta com o nome `build` na raiz do projeto, entre na pasta, e execute `cmake ..` e depois `make`

### 4. Inicializando a Simulação

Navegue até a raiz do projeto, e execute o script nomeado de `start.sh`, e então o resultado das simulações serão geradas no diretório `/data`.

## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para:

- Abrir **issues** para reportar problemas ou sugerir melhorias.
- Enviar **pull requests** com novas funcionalidades ou correções.

## Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE).
